// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseController.h"
#include "Components/RespawnComponent.h"

ABaseController::ABaseController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void ABaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}
