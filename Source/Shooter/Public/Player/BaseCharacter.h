// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootCoreTypes.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;
class USoundCue;

UCLASS()
class SHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable)
	virtual bool IsRun() const;

	virtual void Tick(float DeltaTime) override;

	void SetPlayerColor(const FLinearColor& Color);

	virtual void TurnOff() override;
	virtual void Reset() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Fall")
	FVector2D LandedDamage = (10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Fall")
	FVector2D LandedVelocity = (900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* DeathSound;

	virtual void OnDeath();

private:

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
