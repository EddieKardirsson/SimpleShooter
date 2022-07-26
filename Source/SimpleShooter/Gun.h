// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();
private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* HandleComponent; // root

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 5000;

	void DrawCameraDebug();
};
