#pragma once

#include "Structs/FPlayerCharacter.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Core/Structs/FStoryMapData.h"
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
	UCGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, Exec)		void LoadMainMenu();

public:
	FORCEINLINE FPlayerCharacter& GetPlayerCharacter() { return PlayerCharacter; }
	FORCEINLINE EGameModeTypes GetGameModeType() { return GameModeType; }
	FORCEINLINE FStoryMapData* GetCurrentStoryMap() { return CurrentStoryMap; }

	FORCEINLINE void SetCurrentStoryMap(FStoryMapData* InStoryMap) { CurrentStoryMap = InStoryMap; }

public:
	void Save();
	bool Load();
	void CreateNewCharacter(FString Name, TSubclassOf<ACPlayer> Character);
	void DeleteCharacter(int32 Index);

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

	TSubclassOf<class UUserWidget> MainMenuClass;
	class UCUserWidget_MainMenu* MainMenu;

private:
	FStoryMapData* CurrentStoryMap;
};
