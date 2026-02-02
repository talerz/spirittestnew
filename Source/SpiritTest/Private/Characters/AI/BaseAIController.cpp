// Copyright Epic Games, Inc. All Rights Reserved.


#include "Characters/AI/BaseAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/AI/BaseAICharacter.h"
#include "Characters/AI/Enviro/STPatrolPoint.h"
#include "Perception/AIPerceptionComponent.h"

ABaseAIController::ABaseAIController()
{
	AIBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	AIBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ABaseAIController::InitBBValues(const TObjectPtr<class APawn>& InPawn)
{
	if (OwnerCharacter)
	{
		Blackboard->SetValueAsObject("SelfActor", InPawn);

		const TObjectPtr<USTEnemySettings> EnemySettings = OwnerCharacter->GetEnemySettings();
		if (EnemySettings)
		{
			Blackboard->SetValueAsFloat(BBKey_SearchForLostTargetTime, EnemySettings->SearchForLostTargetTime);
			Blackboard->SetValueAsFloat(BBKey_SearchForLostTargetRange, EnemySettings->SearchForLostTargetRange);
			Blackboard->SetValueAsFloat(BBKey_AttackCooldown, EnemySettings->AttackCooldown);
		}
	}
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!AIBehaviorTreeComponent || !AIBlackboardComponent || !AIBehaviorTree)
	{
		return;
	}

	if ((OwnerCharacter = Cast<ABaseAICharacter>(InPawn)))
	{
		SetGenericTeamId(OwnerCharacter->GetGenericTeamId());
	}
	//Init base value in BB from settings
	InitBBValues(InPawn);
	AIBlackboardComponent->InitializeBlackboard(*AIBehaviorTree->BlackboardAsset);
	AIBehaviorTreeComponent->StartTree(*AIBehaviorTree);


	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::OnTargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.
	                       AddDynamic(this, &ABaseAIController::OnTargetPerceptionForgotten);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bSensedSuccessfully == true)
	{
		return;
	}
	if (CurrentClearTargetDelay <= 0.f)
	{
		// Clear the active target actor so the AI knows it's time to "search"
		UpdateTargetActor(nullptr);
	}
	CurrentClearTargetDelay -= DeltaSeconds;
}

void ABaseAIController::UpdatePatrolPoint(const TObjectPtr<class ASTPatrolPoint>& NewPatrolPoint) const
{
	if (NewPatrolPoint == nullptr)
	{
		return;
	}

	if (IsValid(Blackboard))
	{
		Blackboard->SetValueAsObject(BBKey_PatrolPoint, NewPatrolPoint);
	}
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const auto* TeamAgent = Cast<IGenericTeamAgentInterface>(&Other))
	{
		const FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

		//Checking Other pawn ID to define Attitude 
		// 255 = No Team, by default

		if (OtherTeamID.GetId() == 255)
		{
			return ETeamAttitude::Neutral;
		}
		if (OtherTeamID.GetId() == GetGenericTeamId())
		{
			return ETeamAttitude::Friendly;
		}
		if (OtherTeamID.GetId() != GetGenericTeamId())
		{
			return ETeamAttitude::Hostile;
		}
	}

	return ETeamAttitude::Neutral;
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeRelationship(const AActor* Other) const
{
	return GetTeamAttitudeTowards(*Other);
}

void ABaseAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
	if (!IsValid(Actor) || !Cast<APlayerCharacter>(Actor))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		// We see the target
		bSensedSuccessfully = true;

		//	SetActorTickEnabled(!bSensedSuccessfully);
		UpdateTargetActor(Actor);
		//DEBUG visual
		if (OwnerCharacter)
		{
			OwnerCharacter->ShowEnemyIntentions(true, false);
		}
	}
	else
	{
		bSensedSuccessfully = false;
		// lost sight of the target - save the location where we last saw them
		if (IsValid(Blackboard))
		{
			Blackboard->SetValueAsVector(BBKey_TargetLastKnownLoc, Stimulus.StimulusLocation);
			//DEBUG visual
			if (OwnerCharacter)
			{
				OwnerCharacter->ShowEnemyIntentions(false, true);
			}
		}
		//Small dealy needed for claring the target actor
		CurrentClearTargetDelay = ClearTargetDelay;
	}
}

void ABaseAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}
	if (Actor == CurrentTargetActor)
	{
		//clear target aggro
		UpdateTargetActor(nullptr);
		
		//DEBUG visual
		if (OwnerCharacter)
		{
			OwnerCharacter->ShowEnemyIntentions(false, false);
		}
	}
}

void ABaseAIController::UpdateTargetActor(const TObjectPtr<AActor>& NewTarget)
{
	if (!IsValid(NewTarget))
	{
		if (IsValid(Blackboard))
		{
			Blackboard->SetValueAsObject(BBTarget, nullptr);
		}
		return;
	}

	CurrentTargetActor = NewTarget;
	if (IsValid(Blackboard))
	{
		
		Blackboard->SetValueAsObject(BBTarget, NewTarget);
	}
}
