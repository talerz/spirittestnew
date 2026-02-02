// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STEnvQueryContext_Target.generated.h"


struct FEnvQueryContextData;
struct FEnvQueryInstance;
UCLASS()
class SPIRITTEST_API USTEnvQueryContext_Target : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
