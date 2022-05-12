// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverWidget.h"
#include "Shooter/ShooterGameModeBase.h"
#include "Player/ShootPlayerState.h"
#include "UI/PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "ShootUtils.h"

bool UGameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
		}
	}

	return Super::Initialize();
}

void UGameOverWidget::OnMatchStateChanged(EMatchState State)
{
	if (State == EMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void UGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<UPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(Utils::TextFromInt(PlayerState->GetKills()));
		PlayerStatRowWidget->SetDeaths(Utils::TextFromInt(PlayerState->GetDeaths()));
		PlayerStatRowWidget->SetTeam(Utils::TextFromInt(PlayerState->GetTeamId()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibily(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}
