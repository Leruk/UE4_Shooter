// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreTypes.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!Infinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		bool Infinite;

};

UCLASS()
class SHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;

	virtual void Tick(float DeltaTime) override;

	FOnClipEmptySignature OnClipEmpty;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float MaxDistant = 4500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo{30, 3, false};

	virtual void MakeShot();
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	AController* GetCharacterController() const;

	FTransform GetMuzzleTransform() const;

	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

	float AngleBetweenVectors(FVector First, FVector Second);

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void LogAmmo();

private:
	
	FAmmoData CurrentAmmo;
};
