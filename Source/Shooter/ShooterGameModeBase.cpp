// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BaseController.h"
#include "AIController.h"
#include "UI/GameHUD.h"
#include "Player/ShootPlayerState.h"

AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AShootPlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	StartRound();
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

void AShooterGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundsTime;

	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShooterGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AShooterGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogTemp, Display, TEXT("Time: %i / Round %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0) 
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum) 
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("-------- GAME OVER --------"));
		}
	}
}

void AShooterGameModeBase::ResetPlayers()
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It) 
	{
		ResetOnePlayer(It->Get());
	}
}

void AShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AShooterGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamId(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AShooterGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID-1];
	}
	UE_LOG(LogTemp, Display, TEXT("TeamID is wrong"));

	return FLinearColor();
}

void AShooterGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ABaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}
