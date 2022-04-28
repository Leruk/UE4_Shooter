// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ShootAIController.h"
#include "AI/AICharacter.h"

void AShootAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAICharacter>(InPawn);

	if (AICharacter) {
		RunBehaviorTree(AICharacter->BehaviorTree);
	}
}
