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
	InitialLifeSpan = 5.f;
}

void ABossFloor::BeginPlay()
{
	Super::BeginPlay();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UKismetSystemLibrary::K2_SetTimer(this, "DamageAction", 0.1f, true);
	End_Action();
}

void ABossFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Box->UpdateOverlaps();
	YawAngle += AroundSpeed * DeltaTime;
	if (FMath::IsNearlyEqual(YawAngle, 360.f))
		YawAngle = 0.f;
}

void ABossFloor::Finish()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "DamageAction");
}

void ABossFloor::End_Action()
{
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, 4.5f, false);
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
			FVector center = GetActorLocation();
			FVector awayFromCenter = FVector(300, 0, 0);
			FVector rotVector = awayFromCenter.RotateAngleAxis(YawAngle, FVector::UpVector);
			float up = player->GetActorLocation().Z + 0.1;
			center += rotVector;
			//center.Z += up;
			UCapsuleComponent* cap = player->GetCapsuleComponent();
			FRotator rotator = player->GetActorRotation();
			FVector k = player->GetActorLocation();
			k += FVector(0, 0, 100);
			FLatentActionInfo l;
			UKismetSystemLibrary::MoveComponentTo(cap, k, rotator, true, true, 0.1f, true, EMoveComponentAction::Move, l);
			//player->SetActorLocation(center);

		}
	}
}

