// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShootUtils.h"
#include "Components/ShootAIPerceptionComponent.h"

UFindEnemyService::UFindEnemyService() {
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetOwner();
		const auto PerceptionComponent = Utils::GetPlayerComponent<UShootAIPerceptionComponent>(Controller);
		if (PerceptionComponent) {
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}