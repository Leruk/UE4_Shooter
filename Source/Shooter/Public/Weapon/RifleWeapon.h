// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTER_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:

	ARifleWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float BulletSpread = 1.5f;

	FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UWeaponFXComponent* WeaponFXComponent;

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	virtual void StartFire() override;

	virtual void StopFire() override;

	void MakeDamage(FHitResult HitResult);

private:

	UNiagaraComponent* MuzzleFXComponent;

	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible);
};
