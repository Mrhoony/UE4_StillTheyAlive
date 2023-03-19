#include "BossFallingStone.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Characters/Players/CPlayer.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/DecalComponent.h"

ABossFallingStone::ABossFallingStone()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Sphere);
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Projectile->InitialSpeed = 1000.f;
	Projectile->MaxSpeed = 1000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = false;
	Projectile->bAutoActivate = false;
	Projectile->Velocity = FVector(0, 0, -1);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABossFallingStone::OnComponentBeginOverlap);
}

void ABossFallingStone::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner()); 
	OnStone();
	UKismetSystemLibrary::K2_SetTimer(this, "OnFalling", 0.5f, false);
}

void ABossFallingStone::OnStone()
{
	FVector start = GetActorLocation();
	FVector end = GetActorUpVector() * -1000.f;
	FHitResult hitresult;
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitresult, start, end, ECollisionChannel::ECC_Visibility, collisionQueryParams))
	{
		FRotator decalRotator = hitresult.ImpactNormal.Rotation();
		FVector location = hitresult.Location + FVector(0, 0, 100);
		UDecalComponent* decalComp  = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), location, decalRotator, 20.f);
	}
	
}

void ABossFallingStone::OnFalling()
{
	Projectile->Activate();
}

void ABossFallingStone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (!!player)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorLocation());
		FDamageEvent e;
		player->TakeDamage(50.f, e, OwnerCharacter->GetController(), this);
		Destroy();
	}
}

