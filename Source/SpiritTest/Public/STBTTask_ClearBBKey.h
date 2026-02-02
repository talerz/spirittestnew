// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "STBTTask_ClearBBKey.generated.h"

/**
 * 
 */
UCLASS()
class SPIRITTEST_API USTBTTask_ClearBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USTBTTask_ClearBBKey();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
