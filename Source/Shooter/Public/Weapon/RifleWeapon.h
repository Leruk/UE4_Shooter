// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

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

	UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem* RifleTraceFXComponent;

	UPROPERTY(EditAnywhere, Category = "VFX")
	FString TraceTargetName = "TraceTarget";

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	virtual void StartFire() override;

	virtual void StopFire() override;

	void MakeDamage(FHitResult HitResult);

private:

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void InitFX();
	void SetFXActive(bool isActive);

	void SpawnFXTrace(const FVector& TraceStart, const FVector& TraceEnd);
	AController* GetController() const;
};
