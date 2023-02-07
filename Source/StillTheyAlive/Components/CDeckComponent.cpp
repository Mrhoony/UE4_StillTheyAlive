#include "CDeckComponent.h"
#include "Global.h"
#include "Perk/CPerk.h"
#include "Perk/CDoAction.h"
#include "Perk/CAttachment.h"
#include "Perk/CEquipment.h"

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
	ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

	//TODO: Perk ���ۿ� ���� �ڵ� ����
}

void UCDeckComponent::SetCurrentPerk(int index)
{
	ChangePerk(Perks[DeckNumber], Perks[index]);
	DeckNumber = index;
}

void UCDeckComponent::Begin_Perk(ACPerk* InNewPerk)
{
	if (InNewPerk->GetCurrent()->GetAttachment())
	{
		InNewPerk->GetCurrent()->GetAttachment()->OnEquip();
		if (InNewPerk->GetCurrent()->GetEquipment())
			InNewPerk->GetCurrent()->GetEquipment()->Equip();
	}
}

void UCDeckComponent::End_Perk(ACPerk* InPrevPerk)
{
	if(InPrevPerk->GetCurrent()->GetAttachment())
	InPrevPerk->GetCurrent()->GetAttachment()->OnUnequip();
	//���� ���� �����
}

void UCDeckComponent::ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk)
{
	End_Perk(InPrevPerk);
	Begin_Perk(InNewPerk);
}
