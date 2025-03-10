// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

private:	

	void MoveForward(float AxisValue);
	void StrafeRight(float AxisValue);
	void Pitch(float AxisValue);
	void Yaw(float AxisValue);

public:

	void Shoot();

private:

	UPROPERTY(EditAnywhere)
	float RotationRate = 75;

	UPROPERTY(EditAnywhere, Category = "MainStats | Resources")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "MainStats | Resources")
	float Health = 1;

	/** SpringArmComponent handles the camera location for the third person perspective */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	/** CameraComponent is where the player camera sits on the far end of the SpringArm, enabling third person prespective. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};


