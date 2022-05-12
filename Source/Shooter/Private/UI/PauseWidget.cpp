// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UPauseWidget::NativeOnInitialized()
{
	const auto InitStatus = Super::Initialize();

	if (CancelPauseButton)
	{
		CancelPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnCancelPause);
	}

}

void UPauseWidget::OnCancelPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
