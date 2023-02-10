#include "CGreatSword.h"
#include "Global.h"
#include "Perk/PerkActionData.h"
#include "GameFrameWork/Character.h"

ACGreatSword::ACGreatSword()
{
	WeaponType = EWeaponType::GreatSword;
}

void ACGreatSword::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACGreatSword::BeginPlay()
{
	Super::BeginPlay();
}

void ACGreatSword::TechAction()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}
