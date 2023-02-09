#include "CDeckComponent.h"
#include "Global.h"
#include "Perk/CDoAction.h"
#include "Perk/CAttachment.h"
#include "Perk/CEquipment.h"
#include "GameFramework/Character.h"



UCDeckComponent::UCDeckComponent()
{
}

void UCDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	FTransform transform;
	if (!!PerkClass)
	{
		ACPerk* perk = GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass, transform, GetOwner());
		perk->BeginData(OwnerCharacter);
		Perks.Add(perk);
		UGameplayStatics::FinishSpawningActor(Perks[0], transform);
	}
}

void UCDeckComponent::PerkAction()
{
	if (!!Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		PrintLine();
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->DoAction_L();
	}

}

void UCDeckComponent::PerkTechAction()
{
	if (Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->DoAction_R(Perks[DeckNumber]);
	}

}

void UCDeckComponent::SetCurrentPerk(int index)
{
	//ChangePerk(Perks[DeckNumber], Perks[index]);
	DeckNumber = index;
	switch (Perks[DeckNumber]->Type)
	{
	case EPerkType::Unarmed:SetUnarmed();
		break;
	case EPerkType::Weapon:SetWeapon();
		break;
	case EPerkType::Trap:SetTrap();
		break;
	case EPerkType::Spawn:SetSpawn();
		break;
	case EPerkType::Trinket:SetTrinket();
		break;
	}
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
	//히든 상태 만들기
}

void UCDeckComponent::ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk)
{
	End_Perk(InPrevPerk);
	Begin_Perk(InNewPerk);
}


void UCDeckComponent::SetUnarmed()
{
	SetMode(EPerkType::Unarmed);
}

void UCDeckComponent::SetWeapon()
{
	SetMode(EPerkType::Weapon);
}

void UCDeckComponent::SetTrap()
{
	SetMode(EPerkType::Trap);
}

void UCDeckComponent::SetSpawn()
{
	SetMode(EPerkType::Spawn);
}

void UCDeckComponent::SetTrinket()
{
	SetMode(EPerkType::Trinket);
}

void UCDeckComponent::SetMode(EPerkType InType)
{
	if (Type == InType)
	{
		SetUnarmed();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		if (!!Perks[DeckNumber]->Data->GetEquipment())
			Perks[DeckNumber]->Data->GetEquipment()->Unequip();
	}
	if (Perks[DeckNumber]->Data->GetEquipment())
		Perks[DeckNumber]->Data->GetEquipment()->Equip();

	ChangeType(InType);
}

void UCDeckComponent::ChangeType(EPerkType InType)
{
	EPerkType prevType = Type;
	Type = InType;

	if (OnPerkTypeChanged.IsBound())
		OnPerkTypeChanged.Broadcast(prevType, InType);
}
