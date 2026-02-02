// Fill out your copyright notice in the Description page of Project Settings.


#include "STBTDecorator_InRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USTBTDecorator_InRange::USTBTDecorator_InRange()
{
	NodeName = "In Range Check";
}

bool USTBTDecorator_InRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();
	const TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();

	if (!Blackboard || !AIController || !AIController->GetPawn())
	{
		return false;
	}

	const TObjectPtr<AActor> TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (!TargetActor)
	{
		return false;
	}

	const float DistanceSq = FVector::DistSquared(AIController->GetPawn()->GetActorLocation(), TargetActor->GetActorLocation());

	// Range logic using squared values for performance
	const bool bIsAboveMin = DistanceSq >= FMath::Square(MinRange);
	const bool bIsBelowMax = DistanceSq <= FMath::Square(MaxRange);

	return bInversed ? (!bIsAboveMin || !bIsBelowMax) : bIsAboveMin && bIsBelowMax;
}

FString USTBTDecorator_InRange::GetStaticDescription() const
{
	return FString::Format(TEXT("Range [{0}, {1}]")	, {MinRange.ToString(), MaxRange.ToString()});
}
