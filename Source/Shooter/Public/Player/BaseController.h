// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootCoreTypes.h"
#include "BaseController.generated.h"

class URespawnComponent;

UCLASS()
class SHOOTER_API ABaseController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ABaseController();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChanged(EMatchState State);
};
