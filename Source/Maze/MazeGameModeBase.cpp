// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeGameModeBase.h"

void AMazeGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// Debug messages for 5 sec
		// first argument (-1) - we will never need to update this msg
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("UnrealEngine Maze game"));
	}
}
