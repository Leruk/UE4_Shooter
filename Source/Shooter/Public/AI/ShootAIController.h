// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShootAIController.generated.h"

class UShootAIPerceptionComponent;

UCLASS()
class SHOOTER_API AShootAIController : public AAIController
{
	GENERATED_BODY()

public:

	AShootAIController();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UShootAIPerceptionComponent* ShootAIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
private:

	AActor* GetFocusOnActor() const;
};
