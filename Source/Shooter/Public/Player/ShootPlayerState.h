// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShootPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void SetTeamId(int32 ID) { TeamId = ID; }
	int32 GetTeamId() { return TeamId; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() { return TeamColor; }

	void AddKill() { ++KillsNum; }
	int32 GetKills() { return KillsNum; }

	void AddDeath() { ++DeathsNum; }
	int32 GetDeaths() { return DeathsNum; }

	void LogInfo();

private:
	int32 TeamId;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
