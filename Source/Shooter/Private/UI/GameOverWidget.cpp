// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverWidget.h"
#include "Shooter/ShooterGameModeBase.h"
#include "Player/ShootPlayerState.h"
#include "UI/PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "ShootUtils.h"
#include "Kismet/GameplayStatics.h"
#include "ShootGameInstance.h"

void UGameOverWidget::NativeOnInitialized()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnResetLevel);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnGoToMenu);
	}

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

void UGameOverWidget::OnResetLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void UGameOverWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UShootGameInstance>();

	if (GameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}