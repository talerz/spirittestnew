// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "STBTDecorator_InRange.generated.h"

/**
 * 
 */
UCLASS()
class SPIRITTEST_API USTBTDecorator_InRange : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
public:
	USTBTDecorator_InRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, meta=(ClampMin = "0.0", UIMin="0.0"))
	FValueOrBBKey_Float MinRange = FValueOrBBKey_Float(300.0f);

	UPROPERTY(EditAnywhere, meta=(ClampMin = "0.0", UIMin="0.0"))
	FValueOrBBKey_Float MaxRange = FValueOrBBKey_Float(1000.0f);
	
	UPROPERTY(EditAnywhere)
	bool bInversed = false;
	
};
