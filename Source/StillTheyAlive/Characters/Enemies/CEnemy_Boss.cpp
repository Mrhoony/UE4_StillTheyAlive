#include "CEnemy_Boss.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/Enemies/BossThrowStone.h"
#include "Characters/Enemies/BossFallingStone.h"
#include "Characters/Enemies/CAIController.h"
#include "Characters/Players/CPlayer.h"

ACEnemy_Boss::ACEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::GetClass<ABossThrowStone>(&ThrowStone, "Blueprint'/Game/_Project/Blueprints/BP_BossThrowStone.BP_BossThrowStone_C'");
	CHelpers::GetClass<ABossFallingStone>(&FallingStone, "Blueprint'/Game/_Project/Blueprints/BP_BossFallingStone.BP_BossFallingStone_C'");
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", GetMesh());
	CT_RangeAttack = MAXCT_RangeAttack;
	CT_Skill = MAXCT_Skill;
	CT_Skill2 = MAXCT_Skill2;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Boss::OnComponentBeginOverlap);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();
	ACAIController* controller = Cast<ACAIController>(GetController());
	if (!!controller)
		Behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
}

void ACEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRangeAttack == false)
	{
		CT_RangeAttack -= DeltaTime;
		if (CT_RangeAttack <= 0.f)
		{
			CT_RangeAttack = 0.f;
			bRangeAttack = true;
		}
	}

	if (bSkill == false)
	{
		CT_Skill -= DeltaTime;
		if (CT_Skill <= 0.f)
		{
			CT_Skill = 0.f;
			bSkill = true;
		}
	}

	if (bSkill2 == false)
	{
		CT_Skill2 -= DeltaTime;
		if (CT_Skill2 <= 0.f)
		{
			CT_Skill2 = 0.f;
			bSkill2 = true;
		}
	}
}

void ACEnemy_Boss::BeginAttack()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEnemy_Boss::EndAttack()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemy_Boss::PlayAttack()
{
	State->SetAction();
	PlayAnimMontage(Attack);
}

void ACEnemy_Boss::PlayRangeAttack_Implementation()
{
	bRangeAttack = false;
	CT_RangeAttack = MAXCT_RangeAttack;
	State->SetAction();
	PlayAnimMontage(RangeAttack);
}

void ACEnemy_Boss::PlaySkill_Implementation()
{
	bSkill = false;
	CT_Skill = MAXCT_Skill;
	State->SetAction();
	PlayAnimMontage(Skill1);
}

void ACEnemy_Boss::PlaySkill2_Implementation()
{
	bSkill2 = false;
	CT_Skill2 = MAXCT_Skill2;
	State->SetAction();
	PlayAnimMontage(Skill2);
}

void ACEnemy_Boss::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (!!player)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorLocation());
		FDamageEvent e;
		player->TakeDamage(50.f, e, GetController(), this);
	}
}

void ACEnemy_Boss::BeginRangeAttack()
{
	FActorSpawnParameters spawn;
	spawn.Owner = this;
	if (Behavior->GetTarget() == nullptr) return;
		FVector location = Behavior->GetTarget()->GetActorLocation();
	FTransform transform;
	transform.SetLocation(GetActorLocation());
	ABossThrowStone* stone = Cast<ABossThrowStone>(GetWorld()->SpawnActor(ThrowStone, &transform, spawn));
	stone->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Throw_Stone");
	stone->Throw(location);
}
void ACEnemy_Boss::BeginSkill()
{
	TArray<AActor*> actors;
	actors.Add(this);
	TArray<FHitResult> hitResults;
	if (UKismetSystemLibrary::SphereTraceMulti
	(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + FVector(100, 100, 100),
		3000.f,
		ETraceTypeQuery::TraceTypeQuery2,
		false,
		actors,
		EDrawDebugTrace::None,
		hitResults,
		true
	))
	{
		for (FHitResult hitResult : hitResults)
		{
			if (hitResult.bBlockingHit)
			{
				ACPlayer* player = Cast<ACPlayer>(hitResult.GetActor());
				if (!!player)
				{
					FVector location = player->GetActorLocation() + FVector(0, 0, 800);
					FActorSpawnParameters spawn;
					spawn.Owner = this;
					FTransform transform;
					transform.SetLocation(location);
					ABossFallingStone* stone = Cast<ABossFallingStone>(GetWorld()->SpawnActor(FallingStone, &transform, spawn));
				}
			}
		}
	}
}