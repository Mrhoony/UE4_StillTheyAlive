#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Deck.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_Deck : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetOwnerComponent(class UCDeckComponent* InOnwerComponent) { OwnerComponent = InOnwerComponent; }
	FORCEINLINE TArray<class UCUserWidget_DeckSlot*> GetSlots() { return Slots; }

	void SetIcons();

private:
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* Container;

private:
	class UCDeckComponent* OwnerComponent;
	TArray<class UCUserWidget_DeckSlot*> Slots;
};
