#include "CFloorBlackhole.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Characters/Enemies/CEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perk/Weapons/CWeapon.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"

ACFloorBlackhole::ACFloorBlackhole()
{
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACFloorBlackhole::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACFloorBlackhole::OnComponentEndOverlap);
	CHelpers::CreateSceneComponent<UParticleSystemComponent>(this, &BlackHole, "BlackHole", Scene);
	InitialLifeSpan = 5.f;
}

void ACFloorBlackhole::BeginPlay()
{
	Super::BeginPlay();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UKismetSystemLibrary::K2_SetTimer(this, "DamageAction", 0.5f, true);
	End_Action();
}

void ACFloorBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Box->UpdateOverlaps();
}

void ACFloorBlackhole::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (!!enemy)
		HittedCharacters.AddUnique(enemy);
}

void ACFloorBlackhole::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (!!enemy)
		HittedCharacters.Remove(enemy);
}

void ACFloorBlackhole::End_Action()
{
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, 4.f, false);
}

void ACFloorBlackhole::Finish()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "DamageAction");
}

void ACFloorBlackhole::DamageAction()
{
	FDamageEvent e;
	for (ACharacter* enemy : HittedCharacters)
	{
		bool bIgnore = false;
		bIgnore |= (enemy->IsPendingKill());

		if (bIgnore) continue;

		if (OwnerWeapon->GetCurrent()->GetDoAction())
		{
			TArray<FTechDoAction> techdata = OwnerWeapon->GetCurrent()->GetDoAction()->TechDatas;
			enemy->TakeDamage(techdata[0].Power, e, OwnerCharacter->GetController(), this);

			FVector start = GetActorLocation();
			FVector target = enemy->GetActorLocation();
			FVector direction = start - target;
			direction.Normalize();

			enemy->GetCharacterMovement()->StopMovementImmediately();
			enemy->LaunchCharacter(direction * techdata[0].Power * 30, true, false);

			UParticleSystem* hitEffect = techdata[0].Effect;
			if (!!hitEffect)
			{
				FTransform transform = techdata[0].EffectTransform;
				transform.AddToTranslation(enemy->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
		}
	}
}
