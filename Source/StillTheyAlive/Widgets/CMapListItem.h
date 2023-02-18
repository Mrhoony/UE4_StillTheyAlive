#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMapListItem.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCMapListItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(class UCUserWidget_MainMenu* InParent, uint32 InIndex);

private:
	UFUNCTION()
		void OnClicked();

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MapName;

	UPROPERTY(meta = (BindWidget))
		class UButton* ItemButton;

private:
	class UCUserWidget_MainMenu* Parent;
	uint32 Index;
};
