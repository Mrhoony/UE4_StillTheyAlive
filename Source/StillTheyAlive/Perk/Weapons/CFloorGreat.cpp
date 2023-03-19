#include "CFloorGreat.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Characters/Enemies/CEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perk/Weapons/CWeapon.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"

ACFloorGreat::ACFloorGreat()
{
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACFloorGreat::OnComponentBeginOverlap);
	InitialLifeSpan = 3.f;
}

void ACFloorGreat::BeginPlay()
{
	Super::BeginPlay();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UKismetSystemLibrary::K2_SetTimer(this, "DamageAction", 0.1f, true);
	End_Action();
}

void ACFloorGreat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Box->UpdateOverlaps();
}

void ACFloorGreat::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if(!!enemy)
	HittedCharacters.AddUnique(enemy);
}

void ACFloorGreat::End_Action()
{
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, 2.f, false);
}

void ACFloorGreat::Finish()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "DamageAction");
}

void ACFloorGreat::DamageAction()
{
	FDamageEvent e;
	for (int32 i = 0; i < HittedCharacters.Num(); i++)
	{
		bool bIgnore = false;
		bIgnore |= (HittedCharacters[i]->IsPendingKill());

		if (bIgnore) continue;

		if (OwnerWeapon->GetCurrent()->GetDoAction())
		{
			TArray<FTechDoAction> techdata = OwnerWeapon->GetCurrent()->GetDoAction()->TechDatas;
			HittedCharacters[i]->GetCharacterMovement()->StopMovementImmediately();
			HittedCharacters[i]->TakeDamage(techdata[0].Power, e, OwnerCharacter->GetController(), this);
			HittedCharacters[i]->LaunchCharacter(FVector(0, 0, 100), false, false);

			UParticleSystem* hitEffect = techdata[0].Effect;
			if (!!hitEffect)
			{
				FTransform transform = techdata[0].EffectTransform;
				transform.AddToTranslation(HittedCharacters[i]->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
		}
	}
}