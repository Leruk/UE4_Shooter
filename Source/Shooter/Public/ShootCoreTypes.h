// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootCoreTypes.generated.h"

class ABaseWeapon;

//WEAPON

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!Infinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		bool Infinite;

};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABaseWeapon> WeaponClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadWeaponAnim;

};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossHairIcon;

};

//HEALTH

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangedHealth, float);

USTRUCT(BlueprintType)
struct FAutoHeal {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "AutoHeal")
		float Heal = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal")
		float TimeRate = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal")
		float FirstDelay = 5.0f;
};