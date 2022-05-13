// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootGameInstance.generated.h"



UCLASS()
class SHOOTER_API UShootGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FName GetStartupLevelName() const { return StartupLevelName; }

	FName GetMainMenuName() const { return MainMenuName; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MainMenuName = NAME_None;
};
