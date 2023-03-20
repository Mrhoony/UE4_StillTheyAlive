#include "CRifle.h"
#include "Global.h"

#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"

#include "GameFrameWork/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

ACRifle::ACRifle()
{
	WeaponType = EWeaponType::Rifle;
}


void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	USpringArmComponent* spring = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	if (!!spring)
		OwnerSpringArm = spring;
}

void ACRifle::TechAction()
{
	TArray<FTechDoAction> datas = Data->TechDoActionDatas;
	if(datas.Num()!=0)
	OwnerCharacter->PlayAnimMontage(datas[0].Montage.AnimMontage, datas[0].Montage.PlayRate, datas[0].Montage.StartSection);
	Zoom ? OffZoom() : OnZoom();
}

void ACRifle::DivAction()
{
	DataObject->GetDoAction()->Begin_DoAction();
	GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &ACRifle::Fire, 0.1f, true);
}

void ACRifle::EndAction()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	DataObject->GetDoAction()->End_DoAction();
}

void ACRifle::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACRifle::OnZoom()
{
	Zoom = true;
	DataObject->GetDoAction()->Datas[0].Diversity = true;
	OwnerSpringArm->TargetArmLength = 0.f;
	OwnerSpringArm->SocketOffset = FVector(70, 0, -80);
}

void ACRifle::OffZoom()
{
	Zoom = false;
	DataObject->GetDoAction()->Datas[0].Diversity = false;
	OwnerSpringArm->TargetArmLength = 200.f;
	OwnerSpringArm->SocketOffset = FVector(0, 0, 0);
}
void ACRifle::Fire()
{
	DataObject->GetDoAction()->Begin_DoAction();
}

FVector ACRifle::SocketLocation()
{
	USkeletalMeshComponent* rifle = CHelpers::GetComponent<USkeletalMeshComponent>(this);
	if (!!rifle)
		return rifle->GetSocketLocation("MuzzleFlash");
	return FVector::ZeroVector;
}
