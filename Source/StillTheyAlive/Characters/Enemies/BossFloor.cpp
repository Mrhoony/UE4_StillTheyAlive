#include "BossFloor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Characters/Players/CPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/CapsuleComponent.h"

ABossFloor::ABossFloor()
{
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABossFloor::OnComponentBeginOverlap);
	CHelpers::CreateSceneComponent<UParticleSystemComponent>(this, &SendStrom, "SendStrom", Scene);
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/_Project/Objects/Curve_Alpha.Curve_Alpha'");
	InitialLifeSpan = 10.f;
}

void ABossFloor::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UKismetSystemLibrary::K2_SetTimer(this, "DamageAction", 1.f, true);
	End_Action();
}

void ABossFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Box->UpdateOverlaps();
}

void ABossFloor::Finish()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "DamageAction");
	FDamageEvent e;
	if (HittedCharacters.Num() > 0)
	{
		for (ACharacter* player : HittedCharacters)
		{
			bool bIgnore = false;
			bIgnore |= (player->IsPendingKill());

			if (bIgnore) continue;
			player->GetCharacterMovement()->GravityScale = 1;
			FVector launch = (player->GetActorLocation() - GetActorLocation());
			launch.Normalize();
			launch.Z = 0.f;
			player->LaunchCharacter(launch * 10000, true, true);
			player->TakeDamage(30.f, e, OwnerCharacter->GetController(), OwnerCharacter);
		}
	}
}

void ABossFloor::End_Action()
{
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, 9.0f, false);
}

void ABossFloor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (!!player)
		HittedCharacters.AddUnique(player);
}

void ABossFloor::DamageAction()
{
	FDamageEvent e;
	if (HittedCharacters.Num() > 0)
	{
		for (ACharacter* player : HittedCharacters)
		{
			bool bIgnore = false;
			bIgnore |= (player->IsPendingKill());

			if (bIgnore) continue;
			FVector start = GetActorLocation();
			FVector target = player->GetActorLocation();
			FVector direction = start - target;
			direction.Normalize();
			direction = direction * 80 + FVector(0,0,350);
			player->GetCharacterMovement()->GravityScale = 0.5;
			player->LaunchCharacter(direction, true, true);
			player->TakeDamage(10.f, e, OwnerCharacter->GetController(), OwnerCharacter);
		}
	}
}

