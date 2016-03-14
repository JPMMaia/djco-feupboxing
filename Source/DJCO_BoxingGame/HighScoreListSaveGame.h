// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "HighScoreListSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DJCO_BOXINGGAME_API UHighScoreListSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	UHighScoreListSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FString> PlayersNames;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FString> PlayersScores;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;
};
