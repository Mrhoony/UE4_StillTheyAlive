#include "CGameInstance.h"
#include "Global.h"

#include "CSaveGame.h"
#include "Widgets/CUserWidget_MainMenu.h"

#include "GameFramework/SaveGame.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&MainMenuClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_MainMenu.WB_MainMenu_C'");
}

void UCGameInstance::LoadMainMenu()
{
	if (MainMenuClass == nullptr) return;
	MainMenu = CreateWidget<UCUserWidget_MainMenu>(this, MainMenuClass);

	if (MainMenu == nullptr) return;
	MainMenu->Setup();
}

void UCGameInstance::Save()
{
	TSubclassOf<USaveGame> saveGameClass;
	CHelpers::GetClass<USaveGame>(&saveGameClass, "Class'/Script/StillTheyAlive.CSaveGame_C'");
	SaveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(saveGameClass));

	SaveGame->PlayerCharacters = PlayerCharacters;

	UGameplayStatics::SaveGameToSlot(SaveGame, "SaveData", 0);
}

bool UCGameInstance::Load()
{
	SaveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
	PlayerCharacters = SaveGame->PlayerCharacters;

	for (FPlayerCharacter player : PlayerCharacters)
	{
		if (player.IsLastCharacter == true)
		{
			PlayerCharacter = player;
			return true;
		}
	}

	return false;
}

void UCGameInstance::CreateNewCharacter(FString Name, TSubclassOf<ACPlayer> Character)
{
	FPlayerCharacter newCharacter;
	newCharacter.Name = Name;
	//newCharacter.HasPerks
	//newCharacter.HasSkins
	newCharacter.character = Character;
	newCharacter.KillScore = 0;
	newCharacter.Money = 0;
	newCharacter.IsLastCharacter = true;

	PlayerCharacters.Add(PlayerCharacter);
}

void UCGameInstance::DeleteCharacter(int32 index)
{
	PlayerCharacters.RemoveAt(index);
}
