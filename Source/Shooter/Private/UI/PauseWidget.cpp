// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool UPauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (CancelPauseButton)
	{
		CancelPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnCancelPause);
	}

	return InitStatus;
}

void UPauseWidget::OnCancelPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
