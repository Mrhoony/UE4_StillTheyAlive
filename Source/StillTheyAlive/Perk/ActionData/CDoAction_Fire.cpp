#include "CDoAction_Fire.h"
#include "Global.h"
#include "Perk/CAimAction.h"
#include "CThrow.h"
#include "Characters/Players/CPlayer.h"
#include "Characters/Enemies/CEnemy.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACDoAction_Fire::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAimAction>();
	Aim->BeginPlay(OwnerCharacter);

	//에임중 CurrentAction이 바꼇을 때
	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	CheckNull(actionComp);
	actionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_Fire::ABortByActionTypeChanged);

}

void ACDoAction_Fire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
	
}

void ACDoAction_Fire::DoAction_L()
{
	Super::DoAction_L();
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());
	//CheckFalse(State->IsIdle());
	//State->SetAction();

	OwnerCharacter->PlayAnimMontage(Datas[0].Montage.AnimMontage, Datas[0].Montage.PlayRate, Datas[0].Montage.StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
	Begin_DoAction();
}

void ACDoAction_Fire::Begin_DoAction()
{
	Super::Begin_DoAction();


	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Throw");
	FRotator rotation = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotation));

	ThrowObject = GetWorld()->SpawnActorDeferred<ACThrow>(Datas[0].ThrowClass, transform, OwnerCharacter, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ThrowObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Fire::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(ThrowObject, transform);
}

void ACDoAction_Fire::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdle();
	Status->SetMove();
}

void ACDoAction_Fire::DoAction_R()
{
	Super::DoAction_R();

	PrintLine();
	CheckNull(Aim);
	PrintLine();
	Aim->On();
}

void ACDoAction_Fire::DoOffAction_R()
{
	Super::DoOffAction_R();

	CheckNull(Aim);
	Aim->Off();
}

void ACDoAction_Fire::OnThrowBeginOverlap(FHitResult InHitResult)
{
	FVector origin = ThrowObject->GetActorLocation();
	TArray<AActor*> ignoreActor;
	ignoreActor.Add(OwnerCharacter);
	ignoreActor.Add(ThrowObject);

	if (InHitResult.Actor == nullptr) return;
	
	//Play Particle
	UParticleSystem* hitEffect = Datas[0].Effect;
	if (!!hitEffect)
	{
		FTransform transform = Datas[0].EffectTransform;
		transform.AddToTranslation(ThrowObject->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), hitEffect, transform);
	}

	//Apply Radial Damage
	if (UGameplayStatics::ApplyRadialDamageWithFalloff
	(OwnerCharacter->GetWorld(), Datas[0].Power, Datas[0].Power * 0.1f, origin, 100.0f, 300.0f, 1.0f,
	NULL, ignoreActor, nullptr, OwnerCharacter->GetController(), ECollisionChannel::ECC_Visibility))
	{
		ThrowObject->Impulse();
	}
	ThrowObject->Destroy();
}

void ACDoAction_Fire::ABortByActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());

	Aim->Off();
}