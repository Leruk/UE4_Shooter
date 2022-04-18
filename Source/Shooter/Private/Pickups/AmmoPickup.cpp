// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPickup.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ShootUtils.h"

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}