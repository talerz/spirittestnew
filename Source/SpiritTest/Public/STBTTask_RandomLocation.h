// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "STBTTask_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class SPIRITTEST_API USTBTTask_RandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USTBTTask_RandomLocation();

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	FValueOrBBKey_Float SearchRadius = 500.0f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OriginLocationKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ResultLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
