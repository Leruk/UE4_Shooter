// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "GameFramework/Character.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"

float UPlayerHUDWidget::GetHealthPercent() const {

	const auto HealthComponent = GetHealthComponent();

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}

bool UPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const {

	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

FString UPlayerHUDWidget::GetAmmoData() const {

	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return "";

	FAmmoData CurrentWeapon;
	WeaponComponent->GetWeaponAmmoData(CurrentWeapon);

	return PrintAmmo(CurrentWeapon);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();

	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

UHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UHealthComponent>(Component);

	if (!HealthComponent) return nullptr;

	return HealthComponent;
}

UWeaponComponent* UPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UWeaponComponent>(Component);

	if (!WeaponComponent) return nullptr;

	return WeaponComponent;
}

FString UPlayerHUDWidget::PrintAmmo(FAmmoData& AmmoData) const {
	FString StringAmmo;
	StringAmmo = FString::FromInt(AmmoData.Bullets) + " / ";
	StringAmmo += AmmoData.Infinite ? TEXT("∞") : FString::FromInt(AmmoData.Clips);
	return StringAmmo;
}