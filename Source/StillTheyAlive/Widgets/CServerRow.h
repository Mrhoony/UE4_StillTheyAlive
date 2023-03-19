#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CServerRow.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCServerRow : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup(class UCUserWidget_MainMenu* InParent, uint32 InIndex);

private:
	UFUNCTION()
		void OnClicked();
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HostUser;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Connection;

	UPROPERTY(meta = (BindWidget))
		class UButton* RowButton;

	UPROPERTY(BlueprintReadOnly)
		bool bSelected = false;
private:
	class UCUserWidget_MainMenu* Parent;
	uint32 Index;

};
