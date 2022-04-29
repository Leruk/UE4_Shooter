// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponComponent.h"
#include "ShootUtils.h"

UFireService::UFireService() {
	NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller) 
	{
		const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent) {
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}

	}

}
