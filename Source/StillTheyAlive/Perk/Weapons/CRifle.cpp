#include "CRifle.h"
#include "Global.h"
#include "Perk/PerkActionData.h"
#include "GameFrameWork/Character.h"

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
}

void ACRifle::TechAction()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if(datas.Num()!=0)
	OwnerCharacter->PlayAnimMontage(datas[0].AnimMontage, datas[0].PlayRate, datas[0].StartSection);
}
