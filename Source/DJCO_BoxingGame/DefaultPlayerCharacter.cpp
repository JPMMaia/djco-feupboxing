// Fill out your copyright notice in the Description page of Project Settings.

#include "DJCO_BoxingGame.h"
#include "DefaultPlayerCharacter.h"


ADefaultPlayerCharacter::ADefaultPlayerCharacter() :
	IsMoving(false),
	MovingRight(true)
{
	auto sprite = GetSprite();
	sprite->SetFlipbook(IdleAnimation);
}

void ADefaultPlayerCharacter::BeginPlay()
{
}

void ADefaultPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}

void ADefaultPlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveRight", this, &ADefaultPlayerCharacter::MoveRight);
}
void ADefaultPlayerCharacter::MoveRight(float AxisValue)
{
	static const auto worldRightDirection = FVector(1.0f, 0.0f, 0.0f);
	AddMovementInput(worldRightDirection, FMath::Clamp(AxisValue, -1.0f, 1.0f));
}

void ADefaultPlayerCharacter::UpdateCharacter()
{
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const auto PlayerVelocity = GetVelocity();
	auto TravelDirection = PlayerVelocity.X;

	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}
void ADefaultPlayerCharacter::UpdateAnimation()
{
	const auto PlayerVelocity = GetVelocity();
	const auto PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	auto DesiredAnimation = (PlayerSpeed > 0.0f) ? WalkAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}
