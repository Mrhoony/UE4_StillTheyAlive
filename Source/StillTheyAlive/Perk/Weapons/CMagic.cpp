#include "CMagic.h"
#include "Global.h"
#include "Perk/ActionData/PerkActionData.h"
#include "GameFrameWork/Character.h"

ACMagic::ACMagic()
{
	WeaponType = EWeaponType::Magic;
}

void ACMagic::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACMagic::BeginPlay()
{
	Super::BeginPlay();
}
void ACMagic::TechAction()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}
