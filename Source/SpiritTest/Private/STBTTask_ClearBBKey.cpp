// Fill out your copyright notice in the Description page of Project Settings.


#include "STBTTask_ClearBBKey.h"

#include "BehaviorTree/BlackboardComponent.h"

USTBTTask_ClearBBKey::USTBTTask_ClearBBKey()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type USTBTTask_ClearBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	Blackboard->ClearValue(BlackboardKey.SelectedKeyName);

	return EBTNodeResult::Succeeded;
}

FString USTBTTask_ClearBBKey::GetStaticDescription() const
{
	return FString::Format(TEXT("Clear BB Key:  {0}"), {BlackboardKey.SelectedKeyName.ToString()});
}
