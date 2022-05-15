// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include "UI/BaseWidget.h"
#include "Shooter/ShooterGameModeBase.h"

void AGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::InProgress, CreateWidget<UBaseWidget>(GetWorld(), PlayerWidgetClass));
	GameWidgets.Add(EMatchState::Pause, CreateWidget<UBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EMatchState::GameOver, CreateWidget<UBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}


	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AGameHUD::OnMatchStateChanged);
		}
	}
}

void AGameHUD::OnMatchStateChanged(EMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}

	UE_LOG(LogTemp, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}