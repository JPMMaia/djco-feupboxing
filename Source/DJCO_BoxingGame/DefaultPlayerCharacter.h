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

public:

	// Sets default values for this pawn's properties
	ADefaultPlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void MoveRight(float AxisValue);

	void UpdateCharacter();
	void UpdateAnimation();


	UPROPERTY(BlueprintReadOnly)
		bool IsMoving;

	UPROPERTY(EditAnywhere, Category="Animations")
		UPaperFlipbook* IdleAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
		UPaperFlipbook* WalkAnimation;

private:
	bool MovingRight;
};
