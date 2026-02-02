// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STPatrolPoint.generated.h"

UCLASS()
class SPIRITTEST_API ASTPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTPatrolPoint();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	TObjectPtr<ASTPatrolPoint> NextPatrolPoint = nullptr;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBillboardComponent> Billboard = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> PatrolCollision = nullptr;

	UFUNCTION()
	void OnPatrolPointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
