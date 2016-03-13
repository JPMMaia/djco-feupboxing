// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Paper2DClasses.h"
#include "FighterCharacter.generated.h"

/**
 *
 */
UCLASS()
class DJCO_BOXINGGAME_API AFighterCharacter : public APaperCharacter
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
	AFighterCharacter();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Actions") void MoveRight(float AxisValue);
	UFUNCTION(BlueprintCallable, Category = "Actions") void Punch();
	UFUNCTION(BlueprintCallable, Category = "Actions") void Kick();
	UFUNCTION(BlueprintCallable, Category = "Actions") void StartBlocking();
	UFUNCTION(BlueprintCallable, Category = "Actions") void StopBlocking();
	UFUNCTION(BlueprintCallable, Category = "Actions") void Jump() override;

	void UpdateCharacter(float DeltaSeconds);
	void UpdateAnimation() const;

	UFUNCTION(BlueprintCallable, Category = "Actions") bool IsPunching() const;

	UPROPERTY(EditAnywhere, Category = "Animations")
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

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		float Health;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		float Energy;

private:
	FActionState ActionState;
	float AnimationTimer;
};
