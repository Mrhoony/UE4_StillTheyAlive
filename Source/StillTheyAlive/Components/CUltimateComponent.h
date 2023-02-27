#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CUltimateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCUltimateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCUltimateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetGauge() { return Gauge; }
	FORCEINLINE bool IsActivate() { return Activate; }

	void IncreaseUltimate(float InAmount);
	void DecreaseUltimate(float InAmount);
	void UltimateAction();

private:
	float MaxGauge = 100.f;
	float Gauge = 0.f;
	bool Activate = false;
};
