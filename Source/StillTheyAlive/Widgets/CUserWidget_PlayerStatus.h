#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_PlayerStatus.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_PlayerStatus : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetOwnerComponent(class UCStatusComponent* InOnwerComponent) { OwnerComponent = InOnwerComponent; }

public:
	void UpdateHealthBar();
	void UpdateManaBar();

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ManaBar;

private:
	class UCStatusComponent* OwnerComponent;
};
