#include "CDoAction_Melee.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CDeckComponent.h"
#include "GameFrameWork/Character.h"
#include "Perk/CPerk.h"

void ACDoAction_Melee::DoAction_L()
{
	Super::DoAction_L();
	CheckFalse(Datas.Num() > 0);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}

	CheckFalse(State->IsIdle());
	State->SetAction();

	OwnerCharacter->PlayAnimMontage(Datas[0].Montage.AnimMontage, Datas[0].Montage.PlayRate, Datas[0].Montage.StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}


void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bSucceed);
	bSucceed = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].Montage.AnimMontage, Datas[ComboCount].Montage.PlayRate, Datas[ComboCount].Montage.StartSection);
	Datas[ComboCount].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage();
	ComboCount = 0;

	State->SetIdle();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	// 다단히트 방지
	int32 hittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);

	//HitStop
	float hitstop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitstop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDilation", hitstop * 2e-2f, false);
	}

	//Play Particle
	UParticleSystem* hitEffect = Datas[ComboCount].Effect;
	if (!!hitEffect)
	{
		FTransform transform = Datas[ComboCount].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	//Camera Shake
	TSubclassOf<UCameraShake> shake = Datas[ComboCount].ShakeClass;
	if (!!shake)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->PlayCameraShake(shake);
	}

	if (hittedCharactersNum < HittedCharacters.Num())
	{
		//TakeDamage
		FDamageEvent e;
		InOtherCharacter->TakeDamage(Datas[ComboCount].Power, e, InAttacker->GetController(), InCauser);
	}
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::RestoreGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void ACDoAction_Melee::DoAction_R()
{
	CheckFalse(State->IsIdle());
	State->SetAction();
	Deck->GetCurrentPerk()->TechAction();
	TechDatas[ComboCount].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::DoOffAction_R()
{
	Deck->GetCurrentPerk()->EndTechAction();
}

void ACDoAction_Melee::UltimateAction()
{
	CheckFalse(State->IsIdle());
	State->SetAction();
	Deck->GetCurrentPerk()->Ultimate();
	TechDatas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::Begin_Ultimate()
{
	Deck->GetCurrentPerk()->Begin_Ultimate();
}