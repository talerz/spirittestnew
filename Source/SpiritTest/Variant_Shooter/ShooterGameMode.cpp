// Copyright Epic Games, Inc. All Rights Reserved.


#include "Variant_Shooter/ShooterGameMode.h"

#include "K2Node_SpawnActor.h"
#include "ShooterUI.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// create the UI
	ShooterUI = CreateWidget<UShooterUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ShooterUIClass);
	ShooterUI->AddToViewport(0);
}

void AShooterGameMode::IncrementTeamScore(uint8 TeamByte)
{
	// retrieve the team score if any
	int32 Score = 0;
	if (const int32* FoundScore = TeamScores.Find(TeamByte))
	{
		Score = *FoundScore;
	}

	// increment the score for the given team
	++Score;
	TeamScores.Add(TeamByte, Score);

	// update the UI
	ShooterUI->BP_UpdateScore(TeamByte, Score);
}

void AShooterGameMode::RespawnPlayer(const class APlayerCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	AController* PlayerController = PlayerCharacter->GetController();
	if (!PlayerController)
	{
		return;
	}
	const AActor* PlayerStart = FindPlayerStart(PlayerController);
	if (!PlayerStart)
	{
		return;
	}

	const FTransform SpawnTransform = PlayerStart->GetActorTransform();

	// Spawn the new player character
	APlayerCharacter* NewCharacter = World->SpawnActorDeferred<APlayerCharacter>(
		PlayerCharacterClass,
		SpawnTransform);
	
	if (NewCharacter)
	{
		NewCharacter->FinishSpawning(SpawnTransform);
		// Possess the new character
		PlayerController->Possess(NewCharacter);
	}
}
