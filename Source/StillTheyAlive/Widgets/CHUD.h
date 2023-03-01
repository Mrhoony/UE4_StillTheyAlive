#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* Slot_Deck;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* Slot_Status;
};
