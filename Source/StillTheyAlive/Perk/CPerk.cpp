#include "CPerk.h"
#include "Engine/Texture2D.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "PerkActionData.h"

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

void ACPerk::SelectDeck()
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

void ACPerk::SetMode(EPerkType InType)
{
	if (Type == InType)
	{
		SetUnarmed();
		return;
	}
	ChangeType(InType);
}

void ACPerk::ChangeType(EPerkType InType)
{
	Type = InType;
}
