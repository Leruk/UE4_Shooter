// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShootGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/LevelItemWidget.h"

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

    InitLevelItems();
}

void UMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetShootGameInstance();
    if (!GameInstance) return;

    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<ULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (GameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartupLevel());
    }
}

void UMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto GameInstance = GetShootGameInstance();
    if (!GameInstance) return;

    GameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void UMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}

void UMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation) return;

       const auto GameInstance = GetShootGameInstance();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void UMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UShootGameInstance* UMenuWidget::GetShootGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UShootGameInstance>();
}
