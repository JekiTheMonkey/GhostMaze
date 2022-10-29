#include "Character/GM_PlayerCharacter.h"

#include "GM_Log.h"
#include "Camera/CameraComponent.h"
#include "Character/GM_RunComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGM_PlayerCharacter::AGM_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	CameraBoom->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	CameraBoom->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

	UCharacterMovementComponent *Cmc = GetCharacterMovement();
	Cmc->bUseControllerDesiredRotation = false;
	Cmc->bOrientRotationToMovement = true;
	Cmc->bIgnoreBaseRotation = false;
	Cmc->RotationRate.Roll = 180.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AGM_PlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::OnMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::OnMoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ThisClass::OnLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::OnLookUp);

	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, RunComponent.Get(), &UGM_RunComponent::TryStartRunning);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, RunComponent.Get(), &UGM_RunComponent::StopRunning);
}

void AGM_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

static FVector GetDirection(FRotator Rotation, EAxis::Type Axis)
{
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	return FRotationMatrix(YawRotation).GetUnitAxis(Axis);
}

void AGM_PlayerCharacter::OnMoveForward(float Ratio)
{
	if (Ratio == 0.f || !IsValid(Controller))
		return;

	const FVector Direction = GetDirection(Controller->GetControlRotation(), EAxis::X);

	AddMovementInput(Direction, Ratio);
}

void AGM_PlayerCharacter::OnMoveRight(float Ratio)
{
	if (Ratio == 0.f || !IsValid(Controller))
		return;

	const FVector Direction = GetDirection(Controller->GetControlRotation(), EAxis::Y);

	AddMovementInput(Direction, Ratio);
}

void AGM_PlayerCharacter::OnLookUp(float Ratio)
{
	if (Ratio == 0.f)
		return;

	AddControllerPitchInput(Ratio);
}

void AGM_PlayerCharacter::OnLookRight(float Ratio)
{
	if (Ratio == 0.f)
		return;
	
	AddControllerYawInput(Ratio);
}
