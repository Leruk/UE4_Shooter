// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Player/BaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
	SetRootComponent(WeaponMesh);

}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	checkf(DefaultAmmo.Bullets > 0, TEXT("Warning: Bullets can't be negative"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Warning: Clips can't be negative"));

	CurrentAmmo = DefaultAmmo;

}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseWeapon::StartFire() {

}

void ABaseWeapon::StopFire() {

}

void ABaseWeapon::MakeShot() {}

float ABaseWeapon::AngleBetweenVectors(FVector First, FVector Second) {

	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(First, Second)));
}

AController* ABaseWeapon::GetCharacterController() const {
	const auto Player = Cast<ACharacter>(GetOwner());

	if (!Player) return nullptr;

	return Player->GetController();
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {

	const auto Controller = GetCharacterController();

	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	return true;
}

FTransform ABaseWeapon::GetMuzzleTransform() const {
	return WeaponMesh->GetSocketTransform("MuzzleSocket");
}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {

	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;

	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * MaxDistant;

	return true;
}

void ABaseWeapon::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
	FCollisionQueryParams CollisionParam;
	CollisionParam.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

}

void ABaseWeapon::DecreaseAmmo() {
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clip is empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool ABaseWeapon::IsAmmoEmpty() const {
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ABaseWeapon::IsClipEmpty() const {
	return CurrentAmmo.Bullets == 0;
}

void ABaseWeapon::ChangeClip() {

	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogTemp, Display, TEXT("----CLIP IS CHANGED-----"));

}

bool ABaseWeapon::CanReload() const {
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets&& CurrentAmmo.Clips > 0;
}

void ABaseWeapon::LogAmmo() {
	FString AmmoString = FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoString += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoString);
}

bool ABaseWeapon::IsAmmoFull() const {
	return CurrentAmmo.Clips == DefaultAmmo.Clips &&
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ABaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount == 0) return false;

	if (IsAmmoEmpty()) {
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips) {
		const int32 NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0) {
			CurrentAmmo.Clips += ClipsAmount;
		}
		else {
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else {
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}

	return true;
}