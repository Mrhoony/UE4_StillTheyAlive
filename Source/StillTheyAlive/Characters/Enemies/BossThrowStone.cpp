#include "BossThrowStone.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Characters/Players/CPlayer.h"

ABossThrowStone::ABossThrowStone()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Sphere);
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Projectile->InitialSpeed = 2000.f;
	Projectile->MaxSpeed = 2000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = false;
	Projectile->bAutoActivate = false;
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABossThrowStone::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABossThrowStone::OnComponentBeginOverlap);
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ABossThrowStone::Throw(FVector Location)
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Projectile->Velocity = (Location - GetActorLocation()) * 10;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Projectile->Activate();
}

void ABossThrowStone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (!!player)
	{
		FDamageEvent e;
		player->TakeDamage(50.f, e, OwnerCharacter->GetController(), this);
		Destroy();
	}
}

void ABossThrowStone::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

