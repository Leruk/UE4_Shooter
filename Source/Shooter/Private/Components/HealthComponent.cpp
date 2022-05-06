// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Player/BaseCharacter.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "Camera/PlayerCameraManager.h"
#include <Shooter/ShooterGameModeBase.h>

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
	
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health, -1.0f);


	if (IsDead()) {
		Killed(InstigatedBy);
		Player->Death.Broadcast();
	}

	Player->GetWorldTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::AutoHeal, AutoHealData.TimeRate, true, AutoHealData.FirstDelay);

	PlayCameraShake();
}

void UHealthComponent::AutoHeal() {
	Health = FMath::Clamp(Health + AutoHealData.Heal, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health, 1.0f);
}

bool UHealthComponent::TryToAddHealth(int32 HealthAmount) {
	if (!Player || Health == MaxHealth || IsDead()) return false;

	Health = FMath::Clamp(Health + HealthAmount, 0.0f, MaxHealth);

	Player->OnChangedHealth.Broadcast(Health, 1.0f);

	return true;
}

void UHealthComponent::PlayCameraShake()
{
	if (IsDead() && !Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return; 


	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);

}
