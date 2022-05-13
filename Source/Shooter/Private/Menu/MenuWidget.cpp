// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShootGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitGame);
	}
}

void UMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UShootGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Level name is NONE"));
		return; 
	}


	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void UMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
