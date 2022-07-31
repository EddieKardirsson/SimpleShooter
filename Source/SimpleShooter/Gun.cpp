// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
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
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticleSystem, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSoundBase, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;
	
	bool bHitSuccess = GunTrace(HitResult, ShotDirection);
	if (bHitSuccess)
	{		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpactParticles, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitImpactSoundBase, HitResult.Location, ShotDirection.Rotation());
		if (auto HitActor = HitResult.GetActor())
		{
			FPointDamageEvent DamageEvent(BaseDamage, HitResult, ShotDirection, nullptr);
			AController* Controller = GetOwnerController();
			HitActor->TakeDamage(BaseDamage, DamageEvent, Controller, this);
		}
	}
}

bool AGun::GunTrace(FHitResult& OutHit, FVector& ShotDirection)
{
	AController* Controller = GetOwnerController();
	if(!Controller)
	{
		return false;
	}

	FVector Location{};
	FRotator Rotation{};
	Controller->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	return GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECC_GameTraceChannel1, CollisionQueryParams);
}

AController* AGun::GetOwnerController() const
{	
	return Cast<AShooterCharacter>(GetOwner())->GetController();	
}



