// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootCoreTypes.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class UTextRenderComponent;
class UWeaponComponent;
class UCameraShake;

UCLASS()
class SHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable)
	bool IsRun() const;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FOnDeath Death;
	FOnChangedHealth OnChangedHealth;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Fall")
	FVector2D LandedDamage = (10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Fall")
	FVector2D LandedVelocity = (900.0f, 1200.0f);

	virtual void OnDeath();

private:

	bool GoForward = false;
	bool WantToRun = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Sprint();
	void StopSprint();


	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	void SetHealthText(float Health, float DeltaHealth);
};
