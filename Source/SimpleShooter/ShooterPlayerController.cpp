// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

AShooterPlayerController::AShooterPlayerController()
{
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if(bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if(WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
