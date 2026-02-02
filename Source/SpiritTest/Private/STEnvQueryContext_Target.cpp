// Fill out your copyright notice in the Description page of Project Settings.


#include "STEnvQueryContext_Target.h"

#include "SpiritTest.h"
#include "Characters/AI/BaseAICharacter.h"
#include "Characters/AI/BaseAIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTEnvQueryContext_Target::ProvideContext(FEnvQueryInstance& QueryInstance,
                                               FEnvQueryContextData& ContextData) const
{
	const TObjectPtr<ABaseAICharacter> QueryOwner = Cast<ABaseAICharacter>(QueryInstance.Owner.Get());
	if (!QueryOwner)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("USTEnvQueryContext_Target: QueryOwner is nullptr."));
		return;
	}
	const TObjectPtr<ABaseAIController> QueryOwnerContoller = Cast<ABaseAIController>(QueryOwner->GetController());
	if (!QueryOwnerContoller)
	{
		UE_LOG(LogSpiritTest, Warning, TEXT("USTEnvQueryContext_Target: QueryOwnerContoller is nullptr."));
		return;
	}
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, QueryOwnerContoller->GetCurrentTargetActor());
}
