#include "CGameInstance.h"
#include "Global.h"
#include "CSaveGame.h"

#include "GameFramework/SaveGame.h"

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
