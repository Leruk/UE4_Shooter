// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "GameFramework/Character.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Player/BaseCharacter.h"
#include "ShootUtils.h"

bool UPlayerHUDWidget::Initialize() {

	const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	
	if (Player) {
		Player->OnChangedHealth.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);	
	}

	return Super::Initialize();

}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) {

	if (HealthDelta < 0.0f) {
		OnTakeDamage();
	}

}

float UPlayerHUDWidget::GetHealthPercent() const {

	const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}

bool UPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const {

	const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());

	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

FString UPlayerHUDWidget::GetAmmoData() const {

	const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());

	if (!WeaponComponent) return "";

	FAmmoData CurrentWeapon;
	WeaponComponent->GetWeaponAmmoData(CurrentWeapon);

	return PrintAmmo(CurrentWeapon);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());

	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

FString UPlayerHUDWidget::PrintAmmo(FAmmoData& AmmoData) const {
	FString StringAmmo;
	StringAmmo = FString::FromInt(AmmoData.Bullets) + " / ";
	StringAmmo += AmmoData.Infinite ? TEXT("∞") : FString::FromInt(AmmoData.Clips);
	return StringAmmo;
}