// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}