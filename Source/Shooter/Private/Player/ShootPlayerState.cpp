// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShootPlayerState.h"

void AShootPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Display, TEXT("TeamId: %i, Kills: %i, Deaths: %i"), TeamId, KillsNum, DeathsNum);
}
