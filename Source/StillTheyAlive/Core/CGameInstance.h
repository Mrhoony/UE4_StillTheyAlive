#pragma once

#include "Structs/FPlayerCharacter.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameModeTypes : uint8
{
	Story,
	Endless,
	Max
};

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

	EGameModeTypes GetGameModeType() { return GameModeType; }

private:
	FORCEINLINE void SetGameModeTypeStory() { GameModeType = EGameModeTypes::Story; }
	FORCEINLINE void SetGameModeTypeEndless() { GameModeType = EGameModeTypes::Endless; }

private:
	FPlayerCharacter PlayerCharacter;
	TArray<FPlayerCharacter> PlayerCharacters;
	class UCSaveGame* SaveGame;

	//Game Settings
	float MasterVolume = 1.f;
	float MusicVolume = 1.f;
	float EffectVolume = 1.f;

	EGameModeTypes GameModeType;
};
