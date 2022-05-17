// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;


	if (Hit.PhysMaterial.IsValid()) {
		const auto PhysMaterial = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMaterial)) {
			ImpactData = ImpactDataMap[PhysMaterial];
		}
	}


	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
		ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	if (DecalComponent) {
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}