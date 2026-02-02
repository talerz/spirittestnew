// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "STBTTask_FindPatrolPoint.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class SPIRITTEST_API USTBTTask_FindPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	USTBTTask_FindPatrolPoint();
public:
	UPROPERTY(config, Category = Node, EditAnywhere, meta=(ClampMin = "0.0", UIMin="0.0"))
	FValueOrBBKey_Float RadiusToLookForPatrolPointKey = FValueOrBBKey_Float(500.0f);
	
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector PatrolPointKey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

};
