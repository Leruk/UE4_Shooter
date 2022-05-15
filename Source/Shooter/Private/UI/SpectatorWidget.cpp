// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SpectatorWidget.h"
#include "Components/RespawnComponent.h"
#include "ShootUtils.h"

bool USpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = Utils::GetPlayerComponent<URespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
