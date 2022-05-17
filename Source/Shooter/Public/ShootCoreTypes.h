// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootCoreTypes.generated.h"

class ABaseWeapon;
class UNiagaraSystem;

//WEAPON

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ABaseWeapon*);

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
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedHealth, float, float);

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

//VFX

class UNiagaraSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct FDecalData {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "VFX")
		UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
		FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
		float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
		float FadeOutTime = 0.7f;
};


USTRUCT(BlueprintType)
struct FImpactData {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "VFX")
		FDecalData DecalData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
		UNiagaraSystem* Effect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* Sound;
};


USTRUCT(BlueprintType)
struct FGameData {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		int32 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
		int32 RoundsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
		int32 RoundsTime = 10; //time in seconds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
		int32 RespawnTime = 5; //time in seconds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		TArray<FLinearColor> TeamColors;

};

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);

USTRUCT(BlueprintType)
struct FLevelData {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		FName LevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		FName LevelDisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		UTexture2D* LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);