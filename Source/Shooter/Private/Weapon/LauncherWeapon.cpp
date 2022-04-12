// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LauncherWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Projectile.h"

void ALauncherWeapon::StartFire() {
	MakeShot();
}

void ALauncherWeapon::MakeShot() {

	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	FVector ShootDirection = (EndPoint - GetMuzzleTransform().GetLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleTransform().GetLocation());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);

	if (!Projectile) return;

	Projectile->SetShotDirection(ShootDirection);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);

	DecreaseAmmo();
}