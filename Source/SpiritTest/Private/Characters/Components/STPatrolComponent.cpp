// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/STPatrolComponent.h"

#include "Characters/AI/BaseAICharacter.h"
#include "Characters/AI/BaseAIController.h"

// Sets default values for this component's properties
USTPatrolComponent::USTPatrolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTPatrolComponent::NewPatrolPointReached(const TObjectPtr<class ASTPatrolPoint>& NewPatrolPoint)
{
	if (NewPatrolPoint == nullptr)
	{
		return;
	}
	//No need to setup same patrol point twice
	if (CurrentPatrolPoint == NewPatrolPoint)
	{
		return;
	}
	CurrentPatrolPoint = NewPatrolPoint;

	if (EnemyOwnerController == nullptr)
	{
		return;
	}
	EnemyOwnerController->UpdatePatrolPoint(NewPatrolPoint);
}


// Called when the game starts
void USTPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
	EnemyOwner = Cast<ABaseAICharacter>(GetOwner());
	if(EnemyOwner != nullptr)
	{
		EnemyOwnerController = Cast<ABaseAIController>(EnemyOwner->GetController());
	}
	//Setup start PatrolPoint
	NewPatrolPointReached(FirstPatrolPoint.Get());
}