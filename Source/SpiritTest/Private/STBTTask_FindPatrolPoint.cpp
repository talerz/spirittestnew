// Fill out your copyright notice in the Description page of Project Settings.


#include "STBTTask_FindPatrolPoint.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "Characters/AI/Enviro/STPatrolPoint.h"
#include "Kismet/GameplayStatics.h"

class UBlackboardKeyType_Float;

USTBTTask_FindPatrolPoint::USTBTTask_FindPatrolPoint()
{
	NodeName = "FindPatrolPoint";
}

EBTNodeResult::Type USTBTTask_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> FoundPatrolPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASTPatrolPoint::StaticClass(), FoundPatrolPoints);

	if (FoundPatrolPoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	TObjectPtr<AActor> ClosestPatrolPoint = nullptr;
	if (FoundPatrolPoints.Num() == 1)
	{
		if (BlackboardKey.GetSelectedKeyID() == FBlackboard::InvalidKey)
		{
			return EBTNodeResult::Failed;
		}
		ClosestPatrolPoint = FoundPatrolPoints[0];
		Blackboard->SetValue<UBlackboardKeyType_Object>(PatrolPointKey.GetSelectedKeyID(), ClosestPatrolPoint.Get());
		return EBTNodeResult::Succeeded;
	}

	const TObjectPtr<AActor> OwnerCharacter = OwnerComp.GetOwner();
	if (!OwnerCharacter)
	{
		return EBTNodeResult::Failed;
	}

	//Look for closest patrol point
	const FVector OwnerLocation = OwnerCharacter->GetActorLocation();
	float MaxDistanceSq = FMath::Square(RadiusToLookForPatrolPointKey.GetValue(OwnerComp));
	for (const TObjectPtr<AActor> PatrolPoint : FoundPatrolPoints)
	{
		const float DistanceSq = FVector::DistSquared(OwnerLocation, PatrolPoint->GetActorLocation());
		if (DistanceSq < MaxDistanceSq)
		{
			MaxDistanceSq = DistanceSq;
			ClosestPatrolPoint = PatrolPoint;
		}
	}
	if (ClosestPatrolPoint->IsValidLowLevel())
	{
		
		Blackboard->SetValueAsObject(PatrolPointKey.SelectedKeyName, ClosestPatrolPoint.Get());
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

FString USTBTTask_FindPatrolPoint::GetStaticDescription() const
{
	return FString::Format(TEXT("Find Patrol point in radius {0} "), {RadiusToLookForPatrolPointKey.ToString()});
}
