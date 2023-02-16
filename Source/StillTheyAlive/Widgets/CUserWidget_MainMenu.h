#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMenuInterface.h"
#include "CUserWidget_MainMenu.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

public:
	FORCEINLINE void SetMenuInterface(IIMenuInterface* InMenuInterface) { MenuInterface = InMenuInterface; }

private:
	UFUNCTION() void Play();
	UFUNCTION() void Character();
	UFUNCTION() void Option();
	UFUNCTION() void Quit();

public:
	void Setup();
	void Teardown();

protected:
	IIMenuInterface* MenuInterface;

private:
	UPROPERTY(meta = (BindWidget))		class UButton* PlayButton; 
	UPROPERTY(meta = (BindWidget))		class UButton* CharacterButton;
	UPROPERTY(meta = (BindWidget))		class UButton* OptionButton;
	UPROPERTY(meta = (BindWidget))		class UButton* QuitButton;
};
