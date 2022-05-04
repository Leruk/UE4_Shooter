// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BaseController.h"
#include "AIController.h"
#include "UI/GameHUD.h"

AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
}

UClass* AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>()) 
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;
		
	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i) 
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto ShootAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(ShootAIController);
	}
}