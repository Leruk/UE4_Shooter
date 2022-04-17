// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Player/BaseCharacter.h"
#include "Animation/EquipAnimNotify.h"
#include "Animation/ReloadAnimNotify.h"
#include "Animation/AnimUtilities.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();

	EquipWeapon(CurrentWeaponIndex);
	AnimInit();
}

void UWeaponComponent::SpawnWeapons() {

	ACharacter* Player = Cast<ABaseCharacter>(GetOwner());

	if (!Player || !GetWorld()) return;
	
	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnClipEmpty);
		Weapon->SetOwner(Player);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Player->GetMesh(), WeaponArmorySocketName);
	}
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReson)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons) {
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReson);
}


void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex) {
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) {
		UE_LOG(LogTemp, Display, TEXT("Invalid Weapons Index"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon) {
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
		CurrentWeapon->StopFire();
	}

	CurrentWeapon = Weapons[WeaponIndex];
	CurrentReloadAnim = WeaponData[WeaponIndex].ReloadWeaponAnim;
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipInProgress = true;
	Character->PlayAnimMontage(EquipFinishedAnim);
}

void UWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::StartFire() {
	if (!CanFire()) return;
	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire() {
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UWeaponComponent::AnimInit() {

	const auto EquipNotify = AnimUtilities::FindNotifyByClass<UEquipAnimNotify>(EquipFinishedAnim);
	
	if (EquipNotify) {
		EquipNotify->OnNotify.AddUObject(this, &UWeaponComponent::EquipFinished);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("EquipNotify Not Found"));
		checkNoEntry();
	}


	for (auto OneDataWeapon : WeaponData) {
		const auto ReloadNotify = AnimUtilities::FindNotifyByClass<UReloadAnimNotify>(OneDataWeapon.ReloadWeaponAnim);

		if (!ReloadNotify) {
			UE_LOG(LogTemp, Warning, TEXT("ReloadNotify Not Found"));
			checkNoEntry();
		}

		ReloadNotify->OnNotify.AddUObject(this, &UWeaponComponent::ReloadFinished);
	}
}

void UWeaponComponent::EquipFinished(USkeletalMeshComponent* SkeletalMeshComponent) {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != SkeletalMeshComponent) return;

	EquipInProgress = false;
	UE_LOG(LogTemp, Display, TEXT("Equip Finished"));
}

void UWeaponComponent::ReloadFinished(USkeletalMeshComponent* SkeletalMeshComponent) {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != SkeletalMeshComponent) return;

	ReloadInProgress = false;
	UE_LOG(LogTemp, Display, TEXT("Reload Finished"));
}

bool UWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipInProgress && !ReloadInProgress;
}

bool UWeaponComponent::CanEquip() const
{
	return !EquipInProgress && !ReloadInProgress;
}

bool UWeaponComponent::CanReload() const
{
	return CurrentWeapon      //
		&& !EquipInProgress   //
		&& !ReloadInProgress  //
		&& CurrentWeapon->CanReload();
}

void UWeaponComponent::Reload()
{
	ChangeClip();
}

void UWeaponComponent::OnClipEmpty()
{
	ChangeClip();
}

void UWeaponComponent::ChangeClip()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!CanReload() || !Character) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadInProgress = true;

	Character->PlayAnimMontage(CurrentReloadAnim);
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon) {
		UIData = CurrentWeapon->GetWeaponUIData();
		return true;
	}
		return false;
}