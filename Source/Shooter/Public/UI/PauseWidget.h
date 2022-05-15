// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTER_API UPauseWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelPauseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnCancelPause();

	UFUNCTION()
		void OnGoToMenu();
};
