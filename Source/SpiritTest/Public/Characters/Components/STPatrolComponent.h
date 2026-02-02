// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPIRITTEST_API USTPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTPatrolComponent();

	void NewPatrolPointReached(const TObjectPtr<class ASTPatrolPoint>& NewPatrolPoint);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Cached Enemy
	UPROPERTY()
	TObjectPtr<class ABaseAICharacter> EnemyOwner = nullptr;
	
	UPROPERTY()
	TObjectPtr<class ABaseAIController> EnemyOwnerController = nullptr;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Patrol")
	TWeakObjectPtr<class ASTPatrolPoint> FirstPatrolPoint = nullptr;
	
private:

	UPROPERTY()
	TObjectPtr<class ASTPatrolPoint> CurrentPatrolPoint = nullptr;
		
};
