#include "CDoAction_Spawn.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFrameWork/Character.h"
#include "Characters/Players/CSpawnCharacter.h"

void ACDoAction_Spawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACDoAction_Spawn::DoAction_L()
{
	Super::DoAction_L();

	CheckFalse(State->IsIdle());
	State->SetAction();
	if (Datas[0].Diversity)
	{
		OwnerCharacter->PlayAnimMontage(Datas[0].DivMontage.AnimMontage, Datas[0].DivMontage.PlayRate, Datas[0].DivMontage.StartSection);
	}
	else
	{
		if (Datas[0].Montage.AnimMontage == nullptr)
		{
			Begin_DoAction();
			End_DoAction();
		}
		OwnerCharacter->PlayAnimMontage(Datas[0].Montage.AnimMontage, Datas[0].Montage.PlayRate, Datas[0].Montage.StartSection);
	}

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}


void ACDoAction_Spawn::Begin_DoAction()
{
	Super::Begin_DoAction();
	FVector location = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 200;

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);

	ACSpawnCharacter* spawn = GetWorld()->SpawnActorDeferred<ACSpawnCharacter>(Datas[0].SpawnClass, transform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	UGameplayStatics::FinishSpawningActor(spawn, transform);
}

void ACDoAction_Spawn::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdle();
	Status->SetMove();
}
