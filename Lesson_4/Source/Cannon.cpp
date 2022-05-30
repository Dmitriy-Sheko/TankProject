#include "Cannon.h"
#include <Components/SceneComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "CollisionQueryParams.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include "Projectile.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if(!IsReadyToFire())
	{
		return;
	}
	ReadyToFire = true; //true

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - Projectile");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Fire - Trace");
		LineTrace();
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::LineTrace()
{
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;

	FVector start = ProjectileSpawnPoint->GetComponentLocation();
	FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);

		if (hitResult.Actor.Get())
		{
			hitResult.Actor.Get()->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
	}
}

void ACannon::Reload()
{
	ReadyToFire = true;
}
