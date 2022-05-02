// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/NeedAmmoDecorator.h"
#include "AIController.h"
#include "ShootUtils.h"
#include "Components/WeaponComponent.h"
#include "Components/HealthComponent.h"
#include "Weapon/LauncherWeapon.h"
#include "ShootCoreTypes.h"

UNeedAmmoDecorator::UNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool UNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}