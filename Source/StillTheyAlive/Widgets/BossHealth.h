#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHealth.generated.h"

UCLASS()
class STILLTHEYALIVE_API UBossHealth : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateBoss(float InHealth, float InMaxHealth);
};
