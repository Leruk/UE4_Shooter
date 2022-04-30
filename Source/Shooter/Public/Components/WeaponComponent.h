// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootCoreTypes.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
class USkeletalMeshComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UWeaponComponent();

	virtual void StartFire();
	void StopFire();

	virtual void NextWeapon();

	void Reload();

	void ChangeClip();
	void OnClipEmpty(ABaseWeapon* AmmoEmptyWeapon);

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmount);

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReson) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipFinishedAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* CurrentReloadAnim;

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;

	bool EquipInProgress = false;
	bool ReloadInProgress = false;

	int32 CurrentWeaponIndex = 0;

	bool CanFire() const;
	bool CanEquip() const;

	void EquipFinished(USkeletalMeshComponent* SkeletalMesh);

	void EquipWeapon(int32 CurrentWeaponIndex);

private:

	void SpawnWeapons();

	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void AnimInit();

	void ReloadFinished(USkeletalMeshComponent* SkeletalMesh);

	bool CanReload() const;
};
