// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "ShootCoreTypes.h"
#include "Components/WeaponComponent.h"
#include "Components/HealthComponent.h"
#include "PlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTER_API UPlayerHUDWidget : public UBaseWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	bool GetWeaponUIData(FWeaponUIData &UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable)
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString FormatBullets(int32 BulletsNum) const;

protected:

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor GoodColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor BadColor = FLinearColor::Red;

	virtual void NativeOnInitialized() override;

private:

	void OnHealthChanged(float Health, float DeltaHealth);
	void OnNewPawn(APawn* NewPawn);
	void UpdateHealthBar();
};
