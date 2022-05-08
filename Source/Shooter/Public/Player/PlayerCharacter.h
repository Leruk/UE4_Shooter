// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SHOOTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UCameraComponent* CameraComp;

	virtual void OnDeath() override;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRun() const override;

private:
	bool GoForward = false;
	bool WantToRun = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Sprint();
	void StopSprint();
};
