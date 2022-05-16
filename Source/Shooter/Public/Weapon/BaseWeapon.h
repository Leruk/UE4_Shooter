// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootCoreTypes.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class SHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;

	FOnClipEmptySignature OnClipEmpty;

	FWeaponUIData GetWeaponUIData() const { return UIData; }

	FAmmoData GetWeaponAmmo() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);

	bool IsAmmoEmpty() const;

	bool IsAmmoFull() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float MaxDistant = 4500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo{30, 3, false};

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* FireSound;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	AController* GetCharacterController() const;

	FTransform GetMuzzleTransform() const;

	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

	float AngleBetweenVectors(FVector First, FVector Second);

	UNiagaraComponent* SpawnMuzzleFX();

	void DecreaseAmmo();
	bool IsClipEmpty() const;
	void LogAmmo();


private:
	
	FAmmoData CurrentAmmo;

};
