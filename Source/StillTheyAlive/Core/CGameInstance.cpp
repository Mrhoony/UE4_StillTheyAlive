#include "CGameInstance.h"
#include "Global.h"

#include "CSaveGame.h"
#include "Widgets/CUserWidget_MainMenu.h"
#include "Widgets/LobbyMenu.h"

#include "GameFramework/SaveGame.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("GameSession");
const static FName SEVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&MainMenuClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_MainMenu.WB_MainMenu_C'");
	CHelpers::GetClass(&LobbyMenuClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_Lobby.WB_Lobby_C'");
}

void UCGameInstance::Init()
{
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();  
	if (!!oss)
	{
		UE_LOG(LogTemp, Error, TEXT("OSS Pointer Found. Name : %s"), *oss->GetSubsystemName().ToString());

		SessionInterface = oss->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionComplete); 
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not found OSS"));
	}

	if (!!GEngine)
		GEngine->OnNetworkFailure().AddUObject(this, &UCGameInstance::OnNetworkFailure);
}

void UCGameInstance::LoadMainMenu()
{
	if (MainMenuClass == nullptr) return;
	MainMenu = CreateWidget<UCUserWidget_MainMenu>(this, MainMenuClass);

	if (MainMenu == nullptr) return;
	MainMenu->SetMenuInterface(this);
	MainMenu->Setup();
}

 void UCGameInstance::LoadLobbyMenu()
{
	 if (LobbyMenuClass == nullptr) return;
	 LobbyMenu = CreateWidget<ULobbyMenu>(this, LobbyMenuClass);

	 if (LobbyMenu == nullptr) return;
	 LobbyMenu->Setup();
}

void UCGameInstance::Host(FString InServerName)
{
	DesiredServerName = InServerName;

	if (SessionInterface.IsValid())
	{
		auto exsistiongSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (!!exsistiongSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UCGameInstance::Join(uint32 Index)
{
	if (SessionInterface.IsValid() == false) return;
	if (SessionSearch.IsValid() == false) return;

	if (!!MainMenu)
		MainMenu->Teardown();

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UCGameInstance::LoadMainMenuLevel()
{
	APlayerController* controller = GetFirstLocalPlayerController();
	if (controller == nullptr) return;
	controller->ClientTravel("/Game/_Project/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 4;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); 
		UE_LOG(LogTemp, Error, TEXT("Start Find Sessions"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UCGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
		SessionInterface->StartSession(SESSION_NAME);
}

void UCGameInstance::OnCreateSessionComplete(FName InSessionName, bool InSuccess)
{

	if (InSuccess == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not Create Session"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Session : %s"), *InSessionName.ToString());

	if (!!MainMenu)
		MainMenu->Teardown();

	UWorld* world = GetWorld();
	if (world == nullptr) return;
	world->ServerTravel("/Game/_Project/Maps/Lobby?listen");
}

void UCGameInstance::OnDestroySessionComplete(FName InSessionName, bool InSuccess)
{
	if (InSuccess == true)
		CreateSession();
}

void UCGameInstance::OnFindSessionsComplete(bool InSuccess)
{
	if (InSuccess == true && SessionSearch.IsValid() && MainMenu != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Finished Find Sessions"));

		TArray<FServerData> serverNames;
		for (const FOnlineSessionSearchResult& searchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session ID : %s"), *searchResult.GetSessionIdStr());
			UE_LOG(LogTemp, Warning, TEXT("Ping: %d"), searchResult.PingInMs);

			FServerData data;
			data.MaxPlayers = searchResult.Session.SessionSettings.NumPublicConnections;
			data.CurrentPlayers = data.MaxPlayers - searchResult.Session.NumOpenPublicConnections;
			data.HostUserName = searchResult.Session.OwningUserName;

			FString serverName;
			if (searchResult.Session.SessionSettings.Get(SEVER_NAME_SETTINGS_KEY, serverName))
			{
				data.Name = serverName;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Session Name no Found"));
			}
			serverNames.Add(data);
		}

		MainMenu->SetServerList(serverNames);
	}
}

void UCGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult)
{
	if (SessionInterface.IsValid() == false) return;

	FString address;
	if (SessionInterface->GetResolvedConnectString(InSessionName, address) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("not get IP %s"), *address);
		return;
	}

	UEngine* engine = GetEngine();
	if (engine == nullptr) return;
	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join to %s"), *address));

	APlayerController* controller = GetFirstLocalPlayerController();
	if (controller == nullptr) return;
	controller->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InType, const FString& ErrorSting)
{
	LoadMainMenuLevel();
}

void UCGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettiongs;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			sessionSettiongs.bIsLANMatch = true;
		}
		else
		{
			sessionSettiongs.bIsLANMatch = false;
		}
		sessionSettiongs.NumPublicConnections = 4;		
		sessionSettiongs.bShouldAdvertise = true;       
		sessionSettiongs.bUsesPresence = true;			
		sessionSettiongs.Set(SEVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettiongs);
	}
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
