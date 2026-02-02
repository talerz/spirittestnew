// Fill out your copyright notice in the Description page of Project Settings.


#include "STBTDecorator_TargetVisible.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USTBTDecorator_TargetVisible::USTBTDecorator_TargetVisible()
{
	NodeName = "Target Visible Check";
}

bool USTBTDecorator_TargetVisible::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();
	const TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();

	if (!Blackboard || !AIController)
	{
		return false;
	}
	const TObjectPtr<AActor> TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (!TargetActor)
	{
		return false;
	}
	return bInversed ? !AIController->LineOfSightTo(TargetActor) : AIController->LineOfSightTo(TargetActor);
}
