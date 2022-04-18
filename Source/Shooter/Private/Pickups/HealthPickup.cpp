// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPickup.h"
#include "Components/HealthComponent.h"
#include "ShootUtils.h"

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
