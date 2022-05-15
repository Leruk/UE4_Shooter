// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootCoreTypes.h"
#include "GameHUD.generated.h"

class UBaseWidget;

UCLASS()
class SHOOTER_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UBaseWidget* CurrentWidget = nullptr;

	UPROPERTY()
	TMap<EMatchState, UBaseWidget*> GameWidgets;
	void OnMatchStateChanged(EMatchState State);
};
