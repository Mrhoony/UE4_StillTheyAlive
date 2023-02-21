#include "CSpawnCharacter.h"
#include "Global.h"

#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "CAIControllerSpawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"

ACSpawnCharacter::ACSpawnCharacter()
{
}

void ACSpawnCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACSpawnCharacter::Hitted()
{
}

void ACSpawnCharacter::OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType)
{
	switch (InNewType)
	{
	case EStateTypes::Hit:		Hitted();	break;
	case EStateTypes::Dead:		Dead();		break;
	}
}

void ACSpawnCharacter::Dead()
{
	CheckFalse(State->IsDead());

	// Widget Visible false
	//NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	// All Weapon Collision Disable
	Deck->Dead();

	// Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// End_Dead
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 3.f, false);
}

void ACSpawnCharacter::End_Dead()
{
	Deck->EndDead();

	Destroy();
}

float ACSpawnCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

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
