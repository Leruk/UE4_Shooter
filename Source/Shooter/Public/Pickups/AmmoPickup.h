// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

class ABaseWeapon;

UCLASS()
class SHOOTER_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

public:

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		int32 ClipsAmount = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ABaseWeapon> WeaponType;

	virtual bool GivePickupTo(APawn* PlayerPawn) override;

private:
	
};
