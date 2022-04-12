// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/HealthComponent.h"
#include "Components/BaseCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponComponent.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	HealthComp = CreateDefaultSubobject<UHealthComponent>("HealthComp");

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

	OnTakeAnyDamage.AddDynamic(HealthComp, &UHealthComponent::OnTakeAnyDamage);
	LandedDelegate.AddDynamic(this, &ABaseCharacter::OnGroundLanded);
	OnChangedHealth.AddUObject(this, &ABaseCharacter::SetHealthText);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Death.AddUObject(this, &ABaseCharacter::OnDeath);

	OnChangedHealth.Broadcast(HealthComp->GetHealth());

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Look", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::StopSprint);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
}

void ABaseCharacter::MoveForward(float Amount) {

	GoForward = Amount > 0.0f;

	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABaseCharacter::MoveRight(float Amount) {
	AddMovementInput(GetActorRightVector(), Amount);
}

void ABaseCharacter::Sprint() {
	WantToRun = true;
}

void ABaseCharacter::StopSprint() {
	WantToRun = false;
}

bool ABaseCharacter::IsRun() const {
	return WantToRun && GoForward && !GetVelocity().IsZero();
}

void ABaseCharacter::OnDeath() {

	PlayAnimMontage(DeathAnim);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	Controller->ChangeState(NAME_Spectating);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ABaseCharacter::OnGroundLanded(const FHitResult& Hit) {
	float FallVelocity = GetVelocity().Z;
	
	if (-FallVelocity < LandedVelocity.X) return;

	float Damage = FMath::GetMappedRangeValueClamped(LandedVelocity, LandedDamage, -FallVelocity);
	TakeDamage(Damage, FDamageEvent{}, Controller, this);
}

void ABaseCharacter::SetHealthText(float Health) {

	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%0.0f"), HealthComp->GetHealth())));
}