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
	USoundBase* MuzzleSoundBase;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* HitImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitImpactSoundBase;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	float BaseDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float PlayerDamageMultiplier = 2.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float EnemyDamageMultiplier = 1;

	bool GunTrace(FHitResult& OutHit, FVector& ShotDirection);

	AController* GetOwnerController() const;			
};
