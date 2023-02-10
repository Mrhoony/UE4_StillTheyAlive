#include "CRifle.h"
#include "Global.h"
#include "Perk/PerkActionData.h"
#include "GameFrameWork/Character.h"

ACRifle::ACRifle()
{
	WeaponType = EWeaponType::Rifle;
}

void ACRifle::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
}

void ACRifle::TechAction()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if(datas.Num()!=0)
	OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}
