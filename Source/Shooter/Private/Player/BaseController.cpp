// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseController.h"
#include "Components/RespawnComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Shooter/ShooterGameModeBase.h"
#include "ShootGameInstance.h"

ABaseController::ABaseController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ABaseController::OnMatchStateChanged);
		}
	}
}

void ABaseController::OnMatchStateChanged(EMatchState State)
{
	if (State == EMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else 
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = true;
	}
}

void ABaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void ABaseController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ABaseController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ABaseController::OnMuteSound);
}

void ABaseController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ABaseController::OnMuteSound()
{
	if (!GetWorld()) return;

	const auto ShootInstance = Cast<UShootGameInstance>(GetWorld()->GetGameInstance());
	if (!ShootInstance) return;

	ShootInstance->ToggleVolume();
}