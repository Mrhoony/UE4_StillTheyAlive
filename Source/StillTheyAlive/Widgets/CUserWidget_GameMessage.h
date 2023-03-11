#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_GameMessage.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_GameMessage : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void StartMessage(const FString& inText);

};
