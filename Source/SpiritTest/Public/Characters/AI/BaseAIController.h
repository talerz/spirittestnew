// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "BaseAIController.generated.h"


class UBehaviorTreeComponent;


UCLASS(abstract)
class SPIRITTEST_API ABaseAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController();
	void InitBBValues(const TObjectPtr<class APawn>& InPawn);
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	virtual void Tick(float DeltaSeconds) override;
	void UpdatePatrolPoint(const TObjectPtr<class ASTPatrolPoint>& NewPatrolPoint) const;
	
	//Info about current target actor
	TObjectPtr<AActor> GetCurrentTargetActor() const {return CurrentTargetActor; };
	
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	//Added for BlueprintCallable
	UFUNCTION(BlueprintCallable, Category = "Team")
	ETeamAttitude::Type GetTeamAttitudeRelationship(const AActor* Other) const;
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> AIBehaviorTreeComponent;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardComponent> AIBlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> AIBehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY()
	TObjectPtr<AActor> CurrentTargetActor = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	void OnTargetPerceptionForgotten(AActor* Actor);

	//BB keys names
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBTarget = TEXT("Target");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_TargetLastKnownLoc = FName("TargetLastKnownLoc");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_PatrolPoint = FName("PatrolPoint");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_SearchForLostTargetTime = FName("SearchForTargetTime");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_SearchForLostTargetRange = FName("SearchForTargetTime");
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_AttackCooldown = FName("AttachCooldown");
	
	
	//~~BB keys names

private:
	void UpdateTargetActor(const TObjectPtr<AActor>& NewTarget);
	
	bool bSensedSuccessfully = false;
	
	float ClearTargetDelay = 3.f;
	
	float CurrentClearTargetDelay = 0.f;
	
	UPROPERTY()
	TObjectPtr<class ABaseAICharacter> OwnerCharacter = nullptr;
};
