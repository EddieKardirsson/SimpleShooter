// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Particles/ParticleEventManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 70));
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); //NOTE: USpringArmComponent has a SocketName for the endpoint
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("StrafeRight"), this, &AShooterCharacter::StrafeRight);
	PlayerInputComponent->BindAxis(TEXT("MousePitch"), this, &APawn::AddControllerPitchInput); 
	PlayerInputComponent->BindAxis(TEXT("MouseYaw"), this, &APawn::AddControllerYawInput);	//NOTE: MousePitch and MouseYaw are delegating the parent function
	PlayerInputComponent->BindAxis(TEXT("StickPitch"), this, &AShooterCharacter::Pitch);			
	PlayerInputComponent->BindAxis(TEXT("StickYaw"), this, &AShooterCharacter::Yaw);			//NOTE: StickPitch and StickYaw are delegating member functions
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::StrafeRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Pitch(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Yaw(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}



