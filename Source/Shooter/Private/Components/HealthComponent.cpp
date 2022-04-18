// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Player/BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Player = Cast<ABaseCharacter>(GetOwner());
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	
	if (Damage <= 0.0f || IsDead()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health);

	if (IsDead()) {
		Player->Death.Broadcast();
	}

	Player->GetWorldTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::AutoHeal, AutoHealData.TimeRate, true, AutoHealData.FirstDelay);

}

void UHealthComponent::AutoHeal() {
	Health = FMath::Clamp(Health + AutoHealData.Heal, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health);
}

bool UHealthComponent::TryToAddHealth(int32 HealthAmount) {
	if (!Player || Health == MaxHealth || IsDead()) return false;

	Health = FMath::Clamp(Health + HealthAmount, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health);

	return true;
}