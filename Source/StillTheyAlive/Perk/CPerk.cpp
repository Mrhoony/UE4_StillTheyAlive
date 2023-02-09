#include "CPerk.h"
#include "Engine/Texture2D.h"
#include "Global.h"
#include "CEquipment.h"
#include "Components/CStatusComponent.h"
#include "PerkActionData.h"
#include "GameFramework/Character.h"

ACPerk::ACPerk()
{
}

void ACPerk::BeginPlay()
{
	Super::BeginPlay();
}

void ACPerk::L_Action()
{
}

void ACPerk::SetUnarmed()
{
	SetMode(EPerkType::Unarmed);
}

void ACPerk::SetWeapon()
{
	SetMode(EPerkType::Weapon);
}

void ACPerk::SetTrap()
{
	SetMode(EPerkType::Trap);
}

void ACPerk::SetSpawn()
{
	SetMode(EPerkType::Spawn);
}

void ACPerk::SetTrinket()
{
	SetMode(EPerkType::Trinket);
}

void ACPerk::BeginData(class ACharacter* DeckCharacter)
{
	if (!!Data)
		Data->BeginPlay(OwnerCharacter);
}

void ACPerk::SetMode(EPerkType InType)
{
	if (Type == InType)
	{
		SetUnarmed();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		if (!!Data && Data->GetEquipment())
			Data->GetEquipment()->Unequip();
	}
	if (!!Data && Data->GetEquipment())
		Data->GetEquipment()->Equip();

	ChangeType(InType);
}

void ACPerk::ChangeType(EPerkType InType)
{
	Type = InType;
}
