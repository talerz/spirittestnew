// Fill out your copyright notice in the Description page of Project Settings.


#include "STBTTask_Shoot.h"

#include "SpiritTest.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/AI/BaseAICharacter.h"

class APlayerCharacter;

USTBTTask_Shoot::USTBTTask_Shoot()
{
	
	NodeName = "Shoot";
}

EBTNodeResult::Type USTBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.GetSelectedKeyID() == FBlackboard::InvalidKey)
	{
		return EBTNodeResult::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}
	const TObjectPtr<APlayerCharacter> PlayerTarget = Cast<APlayerCharacter>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (PlayerTarget == nullptr)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: PlayerTarget is nullptr. Check Blackboard key '%s'."), *BlackboardKey.SelectedKeyName.ToString());
		return EBTNodeResult::Failed;
	}
	if (PlayerTarget->IsDead())
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: PlayerTarget is dead. Check Blackboard key '%s'."), *BlackboardKey.SelectedKeyName.ToString());
		return EBTNodeResult::Failed;
	}
	const TObjectPtr<AAIController> AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: AIController is nullptr."));
		return EBTNodeResult::Failed;
	}
	const TObjectPtr<ABaseAICharacter> OwnerCharacter = Cast<ABaseAICharacter> (AIController->GetPawn());
	if (!OwnerCharacter)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: OwnerCharacter is nullptr."));
		return EBTNodeResult::Failed;
	}
	
	OwnerCharacter->StartShooting(PlayerTarget);
	OwnerCharacter->StopShooting();
	return EBTNodeResult::Succeeded;
}

void USTBTTask_Shoot::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{

	const TObjectPtr<AAIController> AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: AIController is nullptr."));
	}
	const TObjectPtr<ABaseAICharacter> OwnerCharacter = Cast<ABaseAICharacter> (AIController->GetPawn());
	if (!OwnerCharacter)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("ExecuteTask: OwnerCharacter is nullptr."));
	}
	
	OwnerCharacter->StopShooting();
	
}

FString USTBTTask_Shoot::GetStaticDescription() const
{
	return FString::Format(TEXT("Shoot to Target: {0} "), {BlackboardKey.SelectedKeyName.ToString()});
}

