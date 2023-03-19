#include "CDoAction.h"
#include "Global.h"
#include "Perk/CPerk.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CDeckComponent.h"
#include "GameFramework/Character.h"

ACDoAction::ACDoAction()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACDoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Deck = CHelpers::GetComponent<UCDeckComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ACDoAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACDoAction::OnCharging()
{
	Charging = true;
}

void ACDoAction::OffCharging()
{
	Charging = false;
}