// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		if(LineOfSightTo(PlayerPawn))
		{
			SetFocus(PlayerPawn);		
			MoveToActor(PlayerPawn, AcceptanceRadius);		
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}
	
}
