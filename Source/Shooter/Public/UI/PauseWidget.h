// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTER_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelPauseButton;

private:
	UFUNCTION()
		void OnCancelPause();
};