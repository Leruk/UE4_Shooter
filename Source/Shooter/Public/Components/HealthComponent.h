// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootCoreTypes.h"
#include "HealthComponent.generated.h"

class ABaseCharacter;
class UCameraShakeBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

	float GetHealth() const { return Health; }

	float GetHealthPercent() const { return Health / MaxHealth; }

	bool IsDead() const { return Health <= 0.0f; }

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	bool TryToAddHealth(int32 HealthAmount);

	FOnDeath Death;
	FOnChangedHealth OnChangedHealth;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "AutoHeal")
	FAutoHeal AutoHealData;

	ABaseCharacter* Player;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;


private:

	FTimerHandle TimerHandle;
	float Health = 0.0f;

	void AutoHeal();

	void PlayCameraShake();

	void Killed(AController* KillerController);
};
