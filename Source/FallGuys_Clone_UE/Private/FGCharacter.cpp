// Fill out your copyright notice in the Description page of Project Settings.


#include "FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"

// Sets default values
AFGCharacter::AFGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsSliding = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Creates Capsule
	CapsuleVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleVisual"));
	// Update the CapsuleVisual attachment to cast GetCapsuleComponent() to USceneComponent
	CapsuleVisual->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	CapsuleVisual->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())); // centers
}

// Called when the game starts or when spawned
void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFGCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFGCharacter::StopJump);

	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &AFGCharacter::Slide);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AFGCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFGCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AFGCharacter::StartJump()
{
	bPressedJump = true;
}

void AFGCharacter::StopJump()
{
	bPressedJump = false;
}

void AFGCharacter::CustomJump()
{
	Jump();
}

void AFGCharacter::Slide()
{
	if (!bIsSliding)
	{
		bIsSliding = true;
		GetCharacterMovement()->MaxWalkSpeed *= 1.5f;
		// Crouch() called for better slide animation and collision handling
		Crouch();

		GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &AFGCharacter::EndSlide, 1.5f, false);
	}
}

void AFGCharacter::EndSlide()
{
	bIsSliding = false;
	GetCharacterMovement()->MaxWalkSpeed /= 1.5f;
	UnCrouch();
}

