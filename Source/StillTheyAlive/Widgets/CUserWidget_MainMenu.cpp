#include "CUserWidget_MainMenu.h"
#include "Components/Button.h"
#include "Global.h"

bool UCUserWidget_MainMenu::Initialize()
{
	bool success = Super::Initialize();
	if(success == false) return false;

	CheckNullResult(PlayButton, false);
	CheckNullResult(CharacterButton, false);
	CheckNullResult(OptionButton, false);
	CheckNullResult(QuitButton, false);

	PlayButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::Play);
	CharacterButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::Character);
	OptionButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::Option);
	QuitButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::Quit);

	return true;
}

void UCUserWidget_MainMenu::Play()
{
	CLog::Print("Play");
}

void UCUserWidget_MainMenu::Character()
{
	CLog::Print("Character");
}

void UCUserWidget_MainMenu::Option()
{
	CLog::Print("Option");
}

void UCUserWidget_MainMenu::Quit()
{
	CLog::Print("Quit");
}

void UCUserWidget_MainMenu::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* world = GetWorld();
	if (world == nullptr) return;

	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr) return;
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;
}

void UCUserWidget_MainMenu::Teardown()
{
	RemoveFromParent();
	bIsFocusable = false;

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	if (world == nullptr) return;

	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr) return;
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = false;
}
