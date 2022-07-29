// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ShooterCharacter.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandleComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HandleComponent"));
	RootComponent = HandleComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(HandleComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
			
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if(MuzzleFlashParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticleSystem, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));		
	}
	DrawCameraDebug();
}

void AGun::DrawCameraDebug()
{
	AController* Controller = Cast<AShooterCharacter>(GetOwner())->GetController();
	if (!Controller)return;

	FVector Location{};
	FRotator Rotation{};
	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;	
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1,CollisionQueryParams);
	DrawDebugLine(GetWorld(), Location, End, FColor::Red, true);
	if(bHitSuccess)
	{
		DrawDebugPoint(GetWorld(), HitResult.Location, 10, FColor::Red, false, 4);
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpactParticles, HitResult.Location,ShotDirection.Rotation());
		if(auto HitActor = HitResult.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
		}
	}
}

