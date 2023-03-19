#include "CBow.h"
#include "Global.h"

#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"

ACBow::ACBow()
{
	WeaponType = EWeaponType::Bow;
}

void ACBow::BeginPlay()
{
	Super::BeginPlay();
}

void ACBow::EndAction()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	DataObject->GetDoAction()->End_DoAction();
}

void ACBow::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

FVector ACBow::SocketLocation()
{
	USkeletalMeshComponent* rifle = CHelpers::GetComponent<USkeletalMeshComponent>(this);
	if (!!rifle)
		return rifle->GetSocketLocation("bow_base");
	return FVector::ZeroVector;
}

void ACBow::Fire()
{
	DataObject->GetDoAction()->Begin_DoAction();
}
