// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTER_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	

	ABasePickup();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
