#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Ultimate.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_Ultimate : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float InGauge, float InMaxGauge);
};
