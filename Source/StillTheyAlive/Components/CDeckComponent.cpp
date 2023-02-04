#include "CDeckComponent.h"
#include "Global.h"
#include "Perk/CPerk.h"

UCDeckComponent::UCDeckComponent()
{
}

void UCDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	FTransform transform;
	if (!!PerkClass)
	{
		Perks.Add(GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass, transform, GetOwner()));

		UGameplayStatics::FinishSpawningActor(Perks[0], transform);
	}
}

void UCDeckComponent::PerkAction()
{
	Perks[0]->L_Action();
}
void UCDeckComponent::SetCurrentPerk(int index)
{
	CurrentPerk = Perks[index];
	CheckNull(CurrentPerk);
	switch (CurrentPerk->Type)
	{
	case EPerkType::Unarmed:	break;
	case EPerkType::Weapon:		break;
	case EPerkType::Trap:		break;
	case EPerkType::Spawn:		break;
	case EPerkType::Trinket:	break;
	}
}