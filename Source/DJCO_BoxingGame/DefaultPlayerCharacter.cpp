// Fill out your copyright notice in the Description page of Project Settings.

#include "DJCO_BoxingGame.h"
#include "DefaultPlayerCharacter.h"


ADefaultPlayerCharacter::ADefaultPlayerCharacter() :
	ActionState(FActionState::None),
	AnimationTimer(0.0f)
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

	UpdateCharacter(DeltaSeconds);
}

void ADefaultPlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveRight", this, &ADefaultPlayerCharacter::MoveRight);
	InputComponent->BindAction("Punch", IE_Pressed, this, &ADefaultPlayerCharacter::Punch);
	InputComponent->BindAction("Kick", IE_Pressed, this, &ADefaultPlayerCharacter::Kick);
	InputComponent->BindAction("Block", IE_Pressed, this, &ADefaultPlayerCharacter::StartBlocking);
	InputComponent->BindAction("Block", IE_Released, this, &ADefaultPlayerCharacter::StopBlocking);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultPlayerCharacter::Jump);
}
void ADefaultPlayerCharacter::MoveRight(float AxisValue)
{
	if (ActionState != FActionState::None)
		return;

	static const auto worldRightDirection = FVector(1.0f, 0.0f, 0.0f);
	AddMovementInput(worldRightDirection, FMath::Clamp(AxisValue, -1.0f, 1.0f));
}
void ADefaultPlayerCharacter::Punch()
{
	if (ActionState != FActionState::None)
		return;

	ActionState = FActionState::Punch;
	AnimationTimer = 0.0f;
}
void ADefaultPlayerCharacter::Kick()
{
	if (ActionState != FActionState::None)
		return;

	ActionState = FActionState::Kick;
	AnimationTimer = 0.0f;
}
void ADefaultPlayerCharacter::StartBlocking()
{
	if (ActionState != FActionState::None)
		return;
	
	ActionState = FActionState::Block;
	AnimationTimer = 0.0f;
}
void ADefaultPlayerCharacter::StopBlocking()
{
	if (ActionState == FActionState::Block)
		ActionState = FActionState::None;
}
void ADefaultPlayerCharacter::Jump()
{
	ACharacter::Jump();

	if (ActionState == FActionState::None)
		ActionState = FActionState::Jump;
}

void ADefaultPlayerCharacter::UpdateCharacter(float DeltaSeconds)
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

	AnimationTimer += DeltaSeconds;
	if((ActionState == FActionState::Punch || ActionState == FActionState::Kick)
		&& AnimationTimer > 0.3f)
	{
		ActionState = FActionState::None;
		AnimationTimer = 0.0f;
	}
	else if (ActionState == FActionState::Jump && GetVelocity().Z <= 0.01f)
		ActionState = FActionState::None;
}
void ADefaultPlayerCharacter::UpdateAnimation() const
{
	UPaperFlipbook* DesiredAnimation;

	switch(ActionState)
	{
	case FActionState::None: 
		{
			const auto PlayerVelocity = GetVelocity();
			const auto PlayerSpeed = PlayerVelocity.Size();

			// Are we walking?
			if (PlayerSpeed > 0.0f)
				DesiredAnimation = WalkAnimation;

			// We are idle:
			else
				DesiredAnimation = IdleAnimation;
		}

		break;

	case FActionState::Punch: 
		DesiredAnimation = PunchAnimation;
		break;

	case FActionState::Kick:
		DesiredAnimation = KickAnimation;
		break;

	case FActionState::Block: 
		DesiredAnimation = AnimationTimer > 0.2f ? BlockAnimation : StartBlockAnimation;
		break;

	case FActionState::Jump:
		DesiredAnimation = JumpAnimation;
		break;

	default:
		return;
	}
	
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}
