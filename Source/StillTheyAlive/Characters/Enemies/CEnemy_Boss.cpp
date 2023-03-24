#include "CEnemy_Boss.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/Enemies/BossThrowStone.h"
#include "Characters/Enemies/BossFallingStone.h"
#include "Characters/Enemies/BossFloor.h"
#include "Characters/Enemies/CAIController.h"
#include "Characters/Players/CPlayer.h"
#include "Core/GameModes/CStoryGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/BossHealth.h"

void ACEnemy_Boss::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACEnemy_Boss, TargetLocation);
}

ACEnemy_Boss::ACEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::GetClass<ABossThrowStone>(&ThrowStone, "Blueprint'/Game/_Project/Blueprints/BP_BossThrowStone.BP_BossThrowStone_C'");
	CHelpers::GetClass<ABossFallingStone>(&FallingStone, "Blueprint'/Game/_Project/Blueprints/BP_BossFallingStone.BP_BossFallingStone_C'");
	CHelpers::GetClass<ABossFloor>(&BossFloor, "Blueprint'/Game/_Project/Blueprints/BP_BossFloor.BP_BossFloor_C'");
	CHelpers::GetClass<UBossHealth>(&HealthWidgetClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_Boss.WB_Boss_C'");
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", GetMesh());
	CT_RangeAttack = MAXCT_RangeAttack;
	CT_Skill = MAXCT_Skill;
	CT_Skill2 = MAXCT_Skill2;
	CT_Skill3 = MAXCT_Skill3;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Boss::OnComponentBeginOverlap);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();
	ACAIController* controller = Cast<ACAIController>(GetController());
	if (!!controller)
		Behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	
	BossHealth = Cast<UBossHealth>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), HealthWidgetClass));
	BossHealth->AddToViewport();
	BossHealth->UpdateBoss(Status->GetHealth(), Status->GetMaxHealth());
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

	if (Page2 == false)
	{
		CT_Skill3 -= DeltaTime;
		if (CT_Skill3 <= 0.f)
		{
			CT_Skill3 = 0.f;
			if (Status->GetHealth() / Status->GetMaxHealth() <= 0.5f)
			{
				Page2 = true;
			}
		}
	}
}

void ACEnemy_Boss::Dead()
{
	Super::Dead();
	ACStoryGameMode* gameMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!!gameMode)
		gameMode->GameClear();
}

float ACEnemy_Boss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	if (EventInstigator != nullptr)
		Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	Status->DecreaseHealth(DamageValue);
	BossHealth->UpdateBoss(Status->GetHealth(), Status->GetMaxHealth());

	if (Status->GetHealth() <= 0.f)
	{
		State->SetDead();
		return DamageValue;
	}
	
	return DamageValue;

}

void ACEnemy_Boss::Page2Skill_Implementation()
{
	Page2 = false;
	State->SetAction();
	PlayAnimMontage(Skill3);
}

void ACEnemy_Boss::BeginPage2Skill()
{
	UKismetSystemLibrary::K2_SetTimer(this, "TimerSkill", 0.05f, true);
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "TimerEndSkill");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, 5.f, false);
}

void ACEnemy_Boss::BeginAttack()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEnemy_Boss::EndAttack()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemy_Boss::PlayAttack_Implementation()
{
	State->SetAction();
	PlayAnimMontage(Attack);
}

void ACEnemy_Boss::TimerSkill()
{
	FVector location = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(3000, 3000, 0));
	location += FVector(0, 0, 800);
	FActorSpawnParameters spawn;
	spawn.Owner = this;
	FTransform transform;
	transform.SetLocation(location);
	GetWorld()->SpawnActor(FallingStone, &transform, spawn);
}

void ACEnemy_Boss::TimerEndSkill()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "TimerSkill");
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

void ACEnemy_Boss::BeginSkill2()
{
	FVector location = GetActorLocation() - FVector(0,0,88) * 3;
	FActorSpawnParameters spawn;
	spawn.Owner = this;
	FTransform transform;
	transform.SetLocation(location);
	GetWorld()->SpawnActor(BossFloor, &transform, spawn);
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

void ACEnemy_Boss::BeginRangeAttack_Implementation()
{
	FActorSpawnParameters spawn;
	spawn.Owner = this;
	if (!!Behavior)
	{
		if (Behavior->GetTarget() == nullptr) return;
		TargetLocation = Behavior->GetTarget()->GetActorLocation();
	}
	FTransform transform;
	transform.SetLocation(GetMesh()->GetSocketLocation("Throw_Stone"));
	ABossThrowStone* stone = Cast<ABossThrowStone>(GetWorld()->SpawnActor(ThrowStone, &transform, spawn));
	stone->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Throw_Stone");
	stone->Throw(TargetLocation);
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