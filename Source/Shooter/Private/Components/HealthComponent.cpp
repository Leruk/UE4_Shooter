// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Player/BaseCharacter.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "Camera/PlayerCameraManager.h"
#include <Shooter/ShooterGameModeBase.h>
#include "Perception/AISense_Damage.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

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

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
	ApplyDamage(Damage, InstigatedBy);
}

void UHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	ApplyDamage(FinalDamage, InstigatedBy);
}

void UHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	OnChangedHealth.Broadcast(Health, -1.0f);

	if (IsDead()) {
		Killed(InstigatedBy);
		Death.Broadcast();
	}

	ReportDamageEvent(Damage, InstigatedBy);

	Player->GetWorldTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::AutoHeal, AutoHealData.TimeRate, true, AutoHealData.FirstDelay);

	PlayCameraShake();
}

float UHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if(!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.0f;

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

	return DamageModifiers[PhysMaterial];
}

void UHealthComponent::AutoHeal() {
	Health = FMath::Clamp(Health + AutoHealData.Heal, 0.0f, MaxHealth);

	OnChangedHealth.Broadcast(Health, 1.0f);
}

bool UHealthComponent::TryToAddHealth(int32 HealthAmount) {
	if (!Player || Health == MaxHealth || IsDead()) return false;

	Health = FMath::Clamp(Health + HealthAmount, 0.0f, MaxHealth);

	OnChangedHealth.Broadcast(Health, 1.0f);

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

void UHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;

	UAISense_Damage::ReportDamageEvent(GetWorld(),
		GetOwner(),
		InstigatedBy->GetPawn(),
		Damage,
		InstigatedBy->GetPawn()->GetActorLocation(),
		GetOwner()->GetActorLocation());
}