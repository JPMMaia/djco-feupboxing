// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Paper2DClasses.h"
#include "DefaultPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class DJCO_BOXINGGAME_API ADefaultPlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	enum class FActionState
	{
		None,
		Punch,
		Kick,
		Block,
		Jump
	};

public:

	// Sets default values for this pawn's properties
	ADefaultPlayerCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void MoveRight(float AxisValue);
	void Punch();
	void Kick();
	void StartBlocking();
	void StopBlocking();
	void Jump() override;

	void UpdateCharacter(float DeltaSeconds);
	void UpdateAnimation() const;

	UPROPERTY(EditAnywhere, Category="Animations")
		UPaperFlipbook* IdleAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* WalkAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* PunchAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* KickAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* StartBlockAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* BlockAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* JumpAnimation;

private:
	FActionState ActionState;
	float AnimationTimer;
};
