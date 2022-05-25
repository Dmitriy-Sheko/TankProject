// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}
void ATankPlayerController::MoveForward(float Value)
{
	TankPawn->MoveForward(Value);
}

void ATankPlayerController::RotateRight(float Value)
{
	TankPawn->RotateRight(Value);
}

