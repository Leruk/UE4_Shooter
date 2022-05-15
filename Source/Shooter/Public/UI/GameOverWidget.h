// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "ShootCoreTypes.h"
#include "GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTER_API UGameOverWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;


	virtual void NativeOnInitialized() override;

private:

	void OnMatchStateChanged(EMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();

	UFUNCTION()
		void OnGoToMenu();
};
