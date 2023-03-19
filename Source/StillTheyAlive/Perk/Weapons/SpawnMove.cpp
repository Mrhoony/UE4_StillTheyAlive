#include "SpawnMove.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Enemies/CEnemy.h"
#include "Perk/Weapons/CWeapon.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/ActionData/CDoAction.h"

ASpawnMove::ASpawnMove()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &ThrowParticle, "ThrowParticle", Sphere);
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Projectile->InitialSpeed = 1000.f;
	Projectile->MaxSpeed = 1000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = false;

	InitialLifeSpan = 5.f;
}

void ASpawnMove::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnMove::OnComponentBeginOverlap);
}

void ASpawnMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DamageAction();

}

void ASpawnMove::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (!!enemy)
		HittedCharacters.AddUnique(enemy);
	
}

void ASpawnMove::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (!!enemy)
		HittedCharacters.Remove(enemy);
}

void ASpawnMove::DamageAction()
{
	ACWeapon* OwnerWeapon = Cast<ACWeapon>(GetOwner());
	TArray<FTechDoAction> techdata = OwnerWeapon->GetCurrent()->GetDoAction()->TechDatas;
	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerWeapon->GetOwner());
	FDamageEvent e;
	for (ACharacter* enemy : HittedCharacters)
	{
		enemy->GetCharacterMovement()->StopMovementImmediately();
		enemy->TakeDamage(5, e, OwnerCharacter->GetController(), this);

		if (!!ImpactParticle)
		{
			FTransform transform = ImpactParticleTransform;
			transform.AddToTranslation(enemy->GetActorLocation());

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
		}
	}
}

