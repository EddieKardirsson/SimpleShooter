// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:

	AShooterAIController();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere, Category = "Combat | Movement");
	float AcceptanceRadius = 200;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetAcceptanceRadius() const { return AcceptanceRadius; }
	UFUNCTION(BlueprintCallable)
	void SetAcceptanceRadius(const float AcceptanceRadiusValue) { AcceptanceRadius = AcceptanceRadiusValue; }
};
