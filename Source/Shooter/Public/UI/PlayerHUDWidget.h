// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootCoreTypes.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	bool GetWeaponUIData(FWeaponUIData &UIData) const;

	UFUNCTION(BlueprintCallable)
	FString GetAmmoData() const;

private:
	FString PrintAmmo(FAmmoData& AmmoData) const;
};
