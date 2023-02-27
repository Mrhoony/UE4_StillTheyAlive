#include "CFloorAttack.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Perk/Weapons/CWeapon.h"
#include "GameFrameWork/Character.h"
ACFloorAttack::ACFloorAttack()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	CHelpers::CreateSceneComponent(this, &Box, "Box", Scene);

	Box->SetBoxExtent(FVector(500, 500, 300));
	Box->SetRelativeLocation(FVector(0, 0, 250));
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ACFloorAttack::BeginPlay()
{
	Super::BeginPlay();
	OwnerWeapon = Cast<ACWeapon>(GetOwner());
	if (!!OwnerWeapon)
		OwnerCharacter = Cast<ACharacter>(OwnerWeapon->GetOwner());
}

void ACFloorAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


