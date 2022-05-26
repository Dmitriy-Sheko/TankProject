#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"


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

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATankPawn::MoveForward(float Value)
{
	TargetForwardAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	TargetRotateAxisValue = Value;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<ATankPlayerController>(GetController());
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Tank Movement
	FVector ActorLocation = GetActorLocation();
	FVector forvardVector = GetActorForwardVector();
	FVector moveposition = ActorLocation + forvardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds;
	SetActorLocation (moveposition, true);

	//Tank Rotation
	float CurrentTargetRotateAxisValue = FMath::Lerp(CurrentTargetRotateAxisValue, TargetRotateAxisValue, RotateInterpolationKey);
	float YawRotation = CurrentTargetRotateAxisValue * RotationSpeed * DeltaSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("CurrentTargetRotateAxisValue :%f, TargetRotateAxisValue :%f"), CurrentTargetRotateAxisValue, TargetRotateAxisValue);

	FRotator ActorRotation = GetActorRotation();
	YawRotation = ActorRotation.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(NewRotation);

	//Turret Rotation
	if (Controller)
	{
		FVector MousePosition = Controller->GetMousePosition();
		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePosition);
		TargetRotation.Pitch = NewRotation.Pitch;
		TargetRotation.Roll = NewRotation.Roll;

		TurretMesh->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, TurretRotateInterpolationKey));

	}
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::SetupCannon()
{
	if (Cannon)
	{
		Cannon -> Destroy();
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}






