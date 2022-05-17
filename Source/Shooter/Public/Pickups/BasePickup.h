// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTER_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	

	ABasePickup();

	bool CouldBeTaken() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* PickupTakeSound;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float RespawnTime = 5.0f;

private:

	FTimerHandle RespawnTimerHandle;

	float RotationYaw = 0.0f;

	virtual bool GivePickupTo(APawn* PlayerPawn);

	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
};
