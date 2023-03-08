#include "CMagic.h"
#include "Global.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"
#include "GameFrameWork/Character.h"
#include "SpawnMove.h"
#include "CFloorBlackhole.h"
#include "particles/ParticleSystemComponent.h"

ACMagic::ACMagic()
{
	WeaponType = EWeaponType::Magic;
	CHelpers::GetClass<ACFloorBlackhole>(&Floor, "Blueprint'/Game/BP_CFloorBlackhole.BP_CFloorBlackhole_C'");
	CHelpers::GetClass<ASpawnMove>(&SpawnMove, "Blueprint'/Game/_Project/Perks/Weapons/BP_SpawnMove.BP_SpawnMove_C'");
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
	DataObject->GetDoAction()->OnCharging();
	ChargingStack = 0;
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}

void ACMagic::Begin_TechAction()
{
	FTransform transform;
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Throw_Hand");
	transform.SetLocation(location);

	if(!!OwnerCharacter->GetController())
	transform.SetRotation(FQuat(OwnerCharacter->GetController()->GetControlRotation()));
	ASpawnMove* spawnMove = GetWorld()->SpawnActorDeferred<ASpawnMove>(SpawnMove, transform, this);
	UGameplayStatics::FinishSpawningActor(spawnMove, transform);
}

void ACMagic::ChargingMontage()
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
		OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
}

void ACMagic::EndTechAction()
{
	DataObject->GetDoAction()->OffCharging();
}

void ACMagic::Ultimate()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if (datas.Num() != 0)
		OwnerCharacter->PlayAnimMontage(datas[0].UltimateMontage.AnimMontage, datas[0].UltimateMontage.PlayRate, datas[0].UltimateMontage.StartSection);
}

void ACMagic::Begin_Ultimate()
{
	FTransform transform;
	FVector location = OwnerCharacter->GetActorLocation();
	transform.SetLocation(location + OwnerCharacter->GetActorForwardVector() * 500);
	transform.SetRotation(FQuat(OwnerCharacter->GetActorForwardVector().Rotation()));

	ACFloorBlackhole* floor = GetWorld()->SpawnActorDeferred<ACFloorBlackhole>(Floor, transform, this);
	UGameplayStatics::FinishSpawningActor(floor, transform);
}

FVector ACMagic::SocketLocation()
{
	return OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Throw");
}