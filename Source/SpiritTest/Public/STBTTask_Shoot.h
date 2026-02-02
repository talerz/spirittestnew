// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "STBTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class SPIRITTEST_API USTBTTask_Shoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	USTBTTask_Shoot();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual FString GetStaticDescription() const override;
protected:
	// EBTNodeResult::Type PerformShootTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
