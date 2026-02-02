// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/Enviro/STPatrolPoint.h"

#include "Characters/AI/BaseAICharacter.h"
#include "Characters/Components/STPatrolComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ASTPatrolPoint::ASTPatrolPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	PatrolCollision = CreateDefaultSubobject<UBoxComponent>("PatrolCollision");
	PatrolCollision->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	PatrolCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PatrolCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PatrolCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	RootComponent = PatrolCollision;

	PatrolCollision->OnComponentBeginOverlap.AddDynamic(this, &ASTPatrolPoint::OnPatrolPointReached);
	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
}

void ASTPatrolPoint::OnPatrolPointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	const TObjectPtr<ABaseAICharacter> PatrollingEnemy = Cast<ABaseAICharacter>(OtherActor);
	if (!IsValid(PatrollingEnemy))
	{
		return;
	}
	USTPatrolComponent* PatrolComponent = PatrollingEnemy->GetComponentByClass<USTPatrolComponent>();
	if (!IsValid(PatrolComponent))
	{
		return;
	}

	//Set next patrol point 
	PatrolComponent->NewPatrolPointReached(NextPatrolPoint);
}
