#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_PlayerStatus.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCHUD_PlayerStatus : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHP(float CurrentHP, float MaxHP);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMP(float CurrentMP, float MaxMP);
};
