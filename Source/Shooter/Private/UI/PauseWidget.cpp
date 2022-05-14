// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"
#include "ShootGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (CancelPauseButton)
	{
		CancelPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnCancelPause);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::OnGoToMenu);
	}

}

void UPauseWidget::OnCancelPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UPauseWidget::OnGoToMenu()
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