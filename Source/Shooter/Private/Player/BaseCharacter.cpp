// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/BaseCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>("HealthComp");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

	OnTakeAnyDamage.AddDynamic(HealthComp, &UHealthComponent::OnTakeAnyDamage);
	LandedDelegate.AddDynamic(this, &ABaseCharacter::OnGroundLanded);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComp->Death.AddUObject(this, &ABaseCharacter::OnDeath);

	HealthComp->OnChangedHealth.Broadcast(HealthComp->GetHealth(), 0.0f);

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance) return;

	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

bool ABaseCharacter::IsRun() const {
	return false;
}

void ABaseCharacter::OnDeath() {

	//PlayAnimMontage(DeathAnim);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(3.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ABaseCharacter::OnGroundLanded(const FHitResult& Hit) {
	float FallVelocity = GetVelocity().Z;
	
	if (-FallVelocity < LandedVelocity.X) return;

	float Damage = FMath::GetMappedRangeValueClamped(LandedVelocity, LandedDamage, -FallVelocity);
	TakeDamage(Damage, FDamageEvent{}, Controller, this);
}

void ABaseCharacter::TurnOff()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::TurnOff();
}

void ABaseCharacter::Reset()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::Reset();
}