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
		Perk.Add(GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass, transform, GetOwner()));
	
		UGameplayStatics::FinishSpawningActor(Perk[0], transform);
	}

}


void UCDeckComponent::PerkAction()
{
	Perk[0]->L_Action();
}