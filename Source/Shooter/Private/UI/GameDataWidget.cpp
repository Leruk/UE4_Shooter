// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameDataWidget.h"
#include "Player/BaseCharacter.h"
#include "Player/ShootPlayerState.h"
#include <Shooter/ShooterGameModeBase.h>


int32 UGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetShooterGameModeBase();
	return GameMode ? GameMode->GetRoundsNum() : 0;
}

int32 UGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetShooterGameModeBase();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetShooterGameModeBase();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}



int32 UGameDataWidget::GetDeathsNum() const
{
	const auto PlayerState = GetShootPlayerState();
	return PlayerState ? PlayerState->GetDeaths() : 0;
}

AShooterGameModeBase* UGameDataWidget::GetShooterGameModeBase() const
{
	return GetWorld() ? Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AShootPlayerState* UGameDataWidget::GetShootPlayerState() const
{
	return GetOwningPlayer() ? Cast<AShootPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
