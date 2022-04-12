// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageSphere.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ADamageSphere::ADamageSphere()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ADamageSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADamageSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);

}

