#include "CEnemy.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CDissolveComponent.h"
#include "Core/GameModes/CStoryGameMode.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent(this, &Dissolve, "Dissolve");

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();


}

EPathFollowingRequestResult::Type ACEnemy::Move(FVector GoalPoint)
{
	return Cast<AAIController>(GetController())->MoveToLocation(GoalPoint,50.f,false);
}

void ACEnemy::OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType)
{
	switch (InNewType)
	{
	case EStateTypes::Hit:	Hitted();	break;
	case EStateTypes::Dead:		Dead();		break;
	}
}


void ACEnemy::Hitted()
{

}

void ACEnemy::Dead()
{
	CheckFalse(State->IsDead());


	//NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	//All Weapon Collision Disable
	Deck->Dead();

	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Dissolve->Play();

	//End_Dead
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 3.f, false);

	ACStoryGameMode* GameMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->DecreaseRoundAmount();
}

void ACEnemy::End_Dead()
{
	Dissolve->Stop();

	Deck->EndDead();

	Destroy();
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	//AddImpulse를 위한 준비
	FVector attackerForward = Attacker->GetActorForwardVector();
	FVector attackerUp = Attacker->GetActorUpVector();
	attackerForward.Normalize();
	attackerUp.Normalize();

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		const FRadialDamageEvent* radialDamageEvent = static_cast<const FRadialDamageEvent*>(&DamageEvent);
		GetCharacterMovement()->AddImpulse((attackerForward + attackerUp) * 300.0f, true);
		CLog::Print("TakeRadialDamage");
		CLog::Print(DamageValue);
	}
	else
	{
		CLog::Print("TakeNormalDamage");
		Status->DecreaseHealth(DamageValue);
	Status->DecreaseHealth(DamageValue);

	UCUserWidget_Health* healthWidgetObject = Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidgetObject)
		healthWidgetObject->Update(Status->GetHealth(), Status->GetMaxHealth());

	if (Status->GetHealth() <= 0.f)
	{
		State->SetDead();
		return DamageValue;
	}

	//State->SetHit();

	return DamageValue;
}
