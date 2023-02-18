#include "CDoAction_Fire.h"
#include "Global.h"
#include "CAimAction.h"
#include "CThrow.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CActionComponent.h"
#include "GameFramework/Character.h"

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
	PrintLine();
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

	CheckNull(Aim);
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
	FDamageEvent damageEvent;
	//damageEvent.IsOfType(FRadialDamageEvent::ClassID);
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, damageEvent, OwnerCharacter->GetController(), ThrowObject);
}

void ACDoAction_Fire::ABortByActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());

	Aim->Off();
}