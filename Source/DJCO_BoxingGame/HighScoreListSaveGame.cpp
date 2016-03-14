// Fill out your copyright notice in the Description page of Project Settings.

#include "DJCO_BoxingGame.h"
#include "HighScoreListSaveGame.h"


UHighScoreListSaveGame::UHighScoreListSaveGame()
{
	SaveSlotName = TEXT("HighScoreListCpp");
	UserIndex = 0;
}
