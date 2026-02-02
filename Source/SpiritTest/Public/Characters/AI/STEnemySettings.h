
// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "STEnemySettings.generated.h"

/**
 * Data asset containing configuration settings for enemy AI characters.
 */
UCLASS()
class SPIRITTEST_API USTEnemySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// ==================== Health Settings ====================
	
	/** Maximum HP for this character. It dies if it reaches zero through damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	float MaxHP = 100.0f;

	// ==================== Target Tracking Settings ====================
	
	/** Duration in seconds to search for a lost target before giving up */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Target Tracking")
	float SearchForLostTargetTime = 8.0f;

	/** Maximum distance to search for a lost target */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Target Tracking")
	float SearchForLostTargetRange = 800.0f;

	// ==================== Combat Settings ====================
	
	/** Minimum time between attacks in seconds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	float AttackCooldown = 2.0f;

	// ==================== Aim Settings ====================
	
	/** Max range for aiming calculations */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aim")
	float AimRange = 10000.0f;

	/** Cone variance to apply while aiming (half-angle in degrees) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aim")
	float AimVarianceHalfAngle = 10.0f;

	/** Minimum vertical offset from the target center to apply when aiming */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aim")
	float MinAimOffsetZ = -35.0f;

	/** Maximum vertical offset from the target center to apply when aiming */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aim")
	float MaxAimOffsetZ = -60.0f;
	
};
