#include "CWeapon.h"
#include "Global.h"

ACWeapon::ACWeapon()
{
	PerkType = EPerkType::Weapon;
}

void ACWeapon::WeaponTypeChanged()
{
	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(WeaponType);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
}
