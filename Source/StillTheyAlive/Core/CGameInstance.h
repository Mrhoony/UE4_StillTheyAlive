#pragma once

#include "Structs/FPlayerCharacter.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Widgets/IMenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
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
class STILLTHEYALIVE_API UCGameInstance : public UGameInstance , public IIMenuInterface
{
	GENERATED_BODY()

public:
	UCGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable, Exec)		void LoadMainMenu();
	UFUNCTION(BlueprintCallable, Exec)		void LoadLobbyMenu();

public:
	FORCEINLINE FPlayerCharacter& GetPlayerCharacter() { return PlayerCharacter; }
	FORCEINLINE EGameModeTypes GetGameModeType() { return GameModeType; }
	FORCEINLINE FStoryMapData* GetCurrentStoryMap() { return CurrentStoryMap; }

	FORCEINLINE void SetCurrentStoryMap(FStoryMapData* InStoryMap) { CurrentStoryMap = InStoryMap; }

	UFUNCTION(Exec)
		void Host(FString InServerName) override;

	UFUNCTION(Exec)
		void Join(uint32 Index) override;

	void LoadMainMenuLevel() override;

	void RefreshServerList() override;

	void StartSession();

private:
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);
	void OnFindSessionsComplete(bool InSuccess);
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult);
	void OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InType, const FString& ErrorSting);

	void CreateSession();
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
	TSubclassOf<class UUserWidget> LobbyMenuClass;
	class UCUserWidget_MainMenu* MainMenu;
	class ULobbyMenu* LobbyMenu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName;
private:
	FStoryMapData* CurrentStoryMap;

};
