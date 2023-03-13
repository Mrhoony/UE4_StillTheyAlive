#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_DeckSlot.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_DeckSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetIcon(UTexture2D* IconImage);
	void SetSelected();
	void SetCleared();

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Icon;

	UPROPERTY(meta = (BindWidget))
		class UImage* Border;
};
