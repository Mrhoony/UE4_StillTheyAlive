#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_PlayerStatus.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_PlayerStatus : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwnerComponent(class UCStatusComponent* InOnwerComponent) { OwnerComponent = InOnwerComponent; }

private:
	class UCStatusComponent* OwnerComponent;
};
