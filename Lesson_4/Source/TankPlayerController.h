#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FVector GetMousePosition() { return MousePosition; };

protected:
	UPROPERTY()
		class ATankPawn* TankPawn;

	UPROPERTY()
		FVector MousePosition;

	void MoveForward(float Value);
	void RotateRight(float Value);
	void Fire();
};
