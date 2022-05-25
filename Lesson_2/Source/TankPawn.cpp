#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATankPawn::ATankPawn()
{	
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::MoveForward(float Value)
{
	TargetForwardAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	TargetRotateAxisValue = Value;
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector ActorLocation = GetActorLocation();
	FVector forvardVector = GetActorForwardVector();
	FVector moveposition = ActorLocation + forvardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds;

	SetActorLocation (moveposition, true);

	float CurrentTargetRotateAxisValue = FMath::Lerp(CurrentTargetRotateAxisValue, TargetRotateAxisValue, RotateInterpolationKey);
	float YawRotation = CurrentTargetRotateAxisValue * RotationSpeed * DeltaSeconds;

	UE_LOG(LogTemp, Warning, TEXT("CurrentTargetRotateAxisValue :%f, TargetRotateAxisValue :%f"), CurrentTargetRotateAxisValue, TargetRotateAxisValue);

	FRotator ActorRotation = GetActorRotation();
	YawRotation = ActorRotation.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(NewRotation);
}






