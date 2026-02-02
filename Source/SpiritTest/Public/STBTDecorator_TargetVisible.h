// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "STBTDecorator_TargetVisible.generated.h"

/**
 * 
 */
UCLASS()
class SPIRITTEST_API USTBTDecorator_TargetVisible : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

public:
	USTBTDecorator_TargetVisible();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(EditAnywhere)
	bool bInversed = false;
	
	
};
