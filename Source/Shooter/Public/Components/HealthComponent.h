// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootCoreTypes.h"
#include "HealthComponent.generated.h"

class ABaseCharacter;


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

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "AutoHeal")
	FAutoHeal AutoHealData;

	UPROPERTY()
	ABaseCharacter* Player;


private:

	FTimerHandle TimerHandle;

	void AutoHeal();

	float Health = 0.0f;

};
