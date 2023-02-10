#include "CDeckComponent.h"
#include "Global.h"
#include "Perk/CDoAction.h"
#include "Perk/CEquipment.h"
#include "Perk/Weapons/CWeapon.h"
#include "GameFramework/Character.h"
#include "Characters/Players/CAnimInstance.h"



UCDeckComponent::UCDeckComponent()
{

}

void UCDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	FTransform transform;
	for (int32 i = 0; i < PerkClass.Num(); i++)
	{
		if (!!PerkClass[i])
		{
			ACPerk* perk = GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass[i], transform, GetOwner());
			perk->BeginData(OwnerCharacter);
			Perks.Add(perk);
			UGameplayStatics::FinishSpawningActor(Perks[i], transform);
		}
	}
	CheckNull(Perks[0]);
	CurrentPerk = Perks[0];
	ChangePerk(nullptr, CurrentPerk);
}

void UCDeckComponent::PerkAction()
{
	CheckFalse(CurrentPerk);
	CheckTrue(IsPerkUnarmed());
	if (!!Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
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
	if (Perks.Num() <= index) return;
	if (DeckNumber == index && !!CurrentPerk)
	{
		SetUnarmed(); 
		return;
	}
	else
	{
		DeckNumber = index;

		BeforePerk = CurrentPerk;

		CurrentPerk = Perks[DeckNumber];
	}
	ChangePerk(BeforePerk, CurrentPerk);
}

void UCDeckComponent::ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk)
{
	if(!!InPrevPerk)
	InPrevPerk->GetCurrent()->GetEquipment()->Unequip();
	InNewPerk->GetCurrent()->GetEquipment()->Equip();
	switch (InNewPerk->GetPerkType())
	{
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

void UCDeckComponent::SetUnarmed()
{
	CheckFalse(CurrentPerk);
	if(CurrentPerk->GetCurrent()->GetEquipment())
		CurrentPerk->GetCurrent()->GetEquipment()->Unequip();
	CurrentPerk = nullptr;
	ChangeType(EPerkType::Unarmed);
}

void UCDeckComponent::SetWeapon()
{
	ChangeType(EPerkType::Weapon);
}

void UCDeckComponent::SetTrap()
{
	ChangeType(EPerkType::Trap);
}

void UCDeckComponent::SetSpawn()
{
	ChangeType(EPerkType::Spawn);
}

void UCDeckComponent::SetTrinket()
{
	ChangeType(EPerkType::Trinket);
}

void UCDeckComponent::ChangeType(EPerkType InType)
{
	EPerkType prevType = Type;
	Type = InType;

	if (OnPerkTypeChanged.IsBound())
		OnPerkTypeChanged.Broadcast(prevType, InType);


	if (Type == EPerkType::Weapon)
	{
		UCAnimInstance* oweneranim = Cast<UCAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance());
		oweneranim->OnWeaponTypeChanged(Cast<ACWeapon>(CurrentPerk)->GetWeaponType());
	}
}
