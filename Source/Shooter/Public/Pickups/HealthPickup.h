// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
public:

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = "0.0", ClampMax = "250.0"))
		int32 HealthAmount = 50.0f;

	virtual bool GivePickupTo(APawn* PlayerPawn) override;

private:
};
