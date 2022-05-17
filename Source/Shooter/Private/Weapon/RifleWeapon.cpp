// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ARifleWeapon::ARifleWeapon() {
	WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::StartFire() {
	InitFX();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARifleWeapon::MakeShot, 0.1f, true);
	MakeShot();
}

void ARifleWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
	SetFXActive(false);
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

	DamagedActor->TakeDamage(10.0f, FDamageEvent{}, GetController(), this);

}

void ARifleWeapon::InitFX()
{
	if (!MuzzleFXComponent) {
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if (!FireAudioComponent) {
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, "MuzzleSocket");
	}

	SetFXActive(true);
}

void ARifleWeapon::SetFXActive(bool isActive)
{
	if (MuzzleFXComponent) {
		MuzzleFXComponent->SetPaused(!isActive);
		MuzzleFXComponent->SetVisibility(isActive, false);
	}

	if (FireAudioComponent) {
		isActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
	}
}

void ARifleWeapon::SpawnFXTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), RifleTraceFXComponent, TraceStart);
	if (TraceFXComponent) {
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* ARifleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void ARifleWeapon::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;
	
	if (Enabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}

	Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
	
}