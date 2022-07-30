// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
	
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);		
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if(ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
