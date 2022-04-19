// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;


	if (Hit.PhysMaterial.IsValid()) {
		const auto PhysMaterial = Hit.PhysMaterial.Get();
		if (EffectMap.Contains(PhysMaterial)) {
			Effect = EffectMap[PhysMaterial];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}