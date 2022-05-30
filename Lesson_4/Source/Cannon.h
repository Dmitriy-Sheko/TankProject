#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include <Tankogeddon/GameStructs.h>
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Componets")
	    UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Componets")
	    UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Fire | Componets")
		float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Fire | Componets")
		float FireRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Fire | Componets")
		float FireDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Fire | Componets")
		ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Fire | Componets")
		TSubclassOf<class AProjectile>ProjectileClass;

	void LineTrace();

	FTimerHandle ReloadTimer;

	bool ReadyToFire = true;

	void Reload();

public:
	ACannon();

	void Fire();

	bool IsReadyToFire();
	
};
