#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_PlayerStatus.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_PlayerStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float InHealth, float InMaxHealth);
	
//=======================================================
// [Variables]
//=======================================================
public:
	class UCStatusComponent* OwnerComp;
};
