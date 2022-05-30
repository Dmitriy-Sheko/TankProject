#include "TankPlayerController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankPlayerController::Fire);
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}
void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition, mouseDirection);
	FVector PawnPosition = TankPawn->GetActorLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector dir = MousePosition - PawnPosition;
	dir.Normalize();
	MousePosition = PawnPosition +dir* 1000;
	DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Green, false, 0.1f, 0, 5);
}
void ATankPlayerController::MoveForward(float Value)
{
	TankPawn->MoveForward(Value);
}

void ATankPlayerController::RotateRight(float Value)
{
	TankPawn->RotateRight(Value);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

