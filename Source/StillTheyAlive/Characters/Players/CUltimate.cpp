#include "CUltimate.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Characters/Players/CPlayer.h"
#include "Components/CUltimateComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

ACUltimate::ACUltimate()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");
	RootComponent = Mesh;

	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", Mesh);
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Mesh);
}

void ACUltimate::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACUltimate::OnComponentBeginOverlap);
	Mesh->AddImpulse(Direction);
}

void ACUltimate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACUltimate::SetUltimateGauge(float InGauge)
{
	UltimateGauge = InGauge;
}

void ACUltimate::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player == nullptr) return;
	UCUltimateComponent* ultimate = CHelpers::GetComponent<UCUltimateComponent>(player);
	if (ultimate == nullptr) return;

	ultimate->IncreaseUltimate(UltimateGauge);

	Destroy();
}