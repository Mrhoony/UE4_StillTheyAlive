#include "CGreatSword.h"
#include "Global.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"
#include "GameFrameWork/Character.h"
#include "CFloorGreat.h"
#include "particles/ParticleSystemComponent.h"

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
	DataObject->GetDoAction()->OnCharging();
	ChargingStack = 0;
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}

void ACGreatSword::ChargingMontage()
{
	Super::ChargingMontage();
	
	ChargingStack++;
	if (ChargingStack >= 4)
	{
		EndTechAction();
		return;
	}

	OwnerCharacter->StopAnimMontage();
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, "Start");
}

void ACGreatSword::EndTechAction()
{
	DataObject->GetDoAction()->OffCharging();
}

void ACGreatSword::Ultimate()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].UltimateMontage.AnimMontage, datas[0].UltimateMontage.PlayRate, datas[0].UltimateMontage.StartSection);
}

void ACGreatSword::Begin_Ultimate()
{
	FTransform transform;
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("GreatSwordTrailEnd");
	transform.SetLocation(location + FVector(0, 0, 100));
	transform.SetRotation(FQuat(OwnerCharacter->GetActorForwardVector().Rotation()));
	
	ACFloorGreat* floor = GetWorld()->SpawnActorDeferred<ACFloorGreat>(ACFloorGreat::StaticClass(), transform, this);
	UGameplayStatics::FinishSpawningActor(floor, transform);

	transform.SetScale3D(FVector(2, 2, 2));
	UParticleSystem* attackEffect;
	CHelpers::GetAssetDynamic<UParticleSystem>(&attackEffect, TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_HeldCharge_Fire_02.P_HeldCharge_Fire_02'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackEffect, transform);
}