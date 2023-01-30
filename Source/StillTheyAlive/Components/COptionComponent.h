#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STILLTHEYALIVE_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetHorizontalLookRate() { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() { return VerticalLookRate; }
	FORCEINLINE float GetZoomSpeed() { return ZoomSpeed; }
	FORCEINLINE FVector2D GetZoomRange() { return ZoomRange; }

// -------------------------------------------------------
// Variables
// -------------------------------------------------------
private:
	UPROPERTY(EditAnywhere)	float HorizontalLookRate = 90.f;
	UPROPERTY(EditAnywhere)	float VerticalLookRate = 90.f;
	UPROPERTY(EditAnywhere)	float ZoomSpeed = 1000.f;
	UPROPERTY(EditAnywhere)	FVector2D ZoomRange = FVector2D(50, 500);
};
