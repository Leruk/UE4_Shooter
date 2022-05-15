// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "ShootCoreTypes.h"
#include "MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UShootGameInstance;
class ULevelItemWidget;

UCLASS()
class SHOOTER_API UMenuWidget : public UBaseWidget
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(meta = (BindWidget))
        UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
        UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
        UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
        TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
        UWidgetAnimation* HideAnimation;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
        TArray<ULevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
        void OnStartGame();

    UFUNCTION()
        void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    UShootGameInstance* GetShootGameInstance() const;
};
