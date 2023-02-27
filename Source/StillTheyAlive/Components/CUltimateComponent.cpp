#include "CUltimateComponent.h"

UCUltimateComponent::UCUltimateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCUltimateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCUltimateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Gauge < 100 ? Activate = false : Activate = true;
}

void UCUltimateComponent::IncreaseUltimate(float InAmount)
{
	Gauge += InAmount;
	Gauge = FMath::Clamp(Gauge, 0.f, MaxGauge);
}

void UCUltimateComponent::DecreaseUltimate(float InAmount)
{
	Gauge -= InAmount;
	Gauge = FMath::Clamp(Gauge, 0.f, MaxGauge);
}

void UCUltimateComponent::UltimateAction()
{
	Gauge = 0.f;
}

