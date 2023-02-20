#include "CDoAction_Throw.h"
#include "Global.h"
#include "CThrow.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFrameWork/Character.h"


void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

}

void ACDoAction_Throw::DoAction_L()
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
		OwnerCharacter->PlayAnimMontage(Datas[0].Montage.AnimMontage, Datas[0].Montage.PlayRate, Datas[0].Montage.StartSection);
	}

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}


void ACDoAction_Throw::Begin_DoAction()
{
	Super::Begin_DoAction();
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Throw");
	FRotator rotation = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotation));

	ThrowObject = GetWorld()->SpawnActorDeferred<ACThrow>(Datas[0].ThrowClass, transform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ThrowObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(ThrowObject, transform);
}

void ACDoAction_Throw::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdle();
	Status->SetMove();
}

void ACDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent e;

	InHitResult.GetActor()->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), ThrowObject);
}
