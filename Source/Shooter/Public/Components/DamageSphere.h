// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageSphere.generated.h"

class USceneComponent;

UCLASS()
class SHOOTER_API ADamageSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageSphere();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Sphere")
	float Radius = 356.0f;

	UPROPERTY(EditAnywhere, Category = "Sphere")
	FColor Color = FColor::Blue;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	bool DoFullDamage = false;

public:	

	virtual void Tick(float DeltaTime) override;

};
