// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ARifleWeapon::ARifleWeapon() {
	WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::StartFire() {
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARifleWeapon::MakeShot, 0.1f, true);
	MakeShot();
}

void ARifleWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
	SetMuzzleFXVisibility(false);
}

void ARifleWeapon::MakeShot() {

	if (!GetWorld() || IsAmmoEmpty()) {
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;

	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector ActualTraceEnd = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;

	const FVector HitDirectionMuzzle = (ActualTraceEnd - GetMuzzleTransform().GetLocation()).GetSafeNormal();

	float BetweenAngle = AngleBetweenVectors(GetMuzzleTransform().GetRotation().GetForwardVector(), HitDirectionMuzzle);

	FVector TraceFXEnd = TraceEnd;
	
	if (HitResult.bBlockingHit && BetweenAngle <= 90) {
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnFXTrace(GetMuzzleTransform().GetLocation(), TraceEnd);
	DecreaseAmmo();
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {

	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;

	float HalfRad = FMath::DegreesToRadians(BulletSpread);

	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * MaxDistant;

	return true;
}

void ARifleWeapon::MakeDamage(FHitResult HitResult) {

	const auto DamagedActor = HitResult.GetActor();

	if (!DamagedActor) return;

	DamagedActor->TakeDamage(10.0f, FDamageEvent{}, GetCharacterController(), this);

}

void ARifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent) {
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void ARifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
	if (MuzzleFXComponent) {
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, false);
	}
}

void ARifleWeapon::SpawnFXTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), RifleTraceFXComponent, TraceStart);
	if (TraceFXComponent) {
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}
