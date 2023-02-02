#pragma once

#include "Structs/FPlayerCharacter.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Save();
	bool Load();
	FPlayerCharacter& GetPlayerCharacter() { return PlayerCharacter; }
	void CreateNewCharacter(FString Name, TSubclassOf<ACPlayer> Character);
	void DeleteCharacter(int32 Index);

private:
	FPlayerCharacter PlayerCharacter;
	TArray<FPlayerCharacter> PlayerCharacters;
	class UCSaveGame* SaveGame;

	//Game Settings
	float MasterVolume = 1.f;
	float MusicVolume = 1.f;
	float EffectVolume = 1.f;
};
