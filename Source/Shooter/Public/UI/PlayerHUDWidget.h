// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootCoreTypes.h"
#include "Components/WeaponComponent.h"
#include "Components/HealthComponent.h"
#include "PlayerHUDWidget.generated.h"



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

	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual bool Initialize() override;

private:

	FString PrintAmmo(FAmmoData& AmmoData) const;

	void OnHealthChanged(float Health, float DeltaHealth);
	void OnNewPawn(APawn* NewPawn);
};
