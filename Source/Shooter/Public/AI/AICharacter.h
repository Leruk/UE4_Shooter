// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTER_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	AAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTree;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float HealthVisibilityDistance = 1000.0f;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta);

private:
	void UpdateHealthWidgetVisibility();
};
