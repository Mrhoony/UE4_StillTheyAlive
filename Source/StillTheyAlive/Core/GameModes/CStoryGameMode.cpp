#include "CStoryGameMode.h"
#include "Global.h"

#include "Core/CGameInstance.h"
#include "Core/BossSpawn.h"
#include "Characters/Enemies/CEnemy.h"
#include "Maps/CSpawnPoint.h"
#include "Maps/CGoalPoint.h"
#include "Maps/StartDoor.h"
#include "Characters/Players/CPlayer.h"

#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ACStoryGameMode::ACStoryGameMode()
{
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/Belica/BP_Belica.BP_Belica_C'");
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/Phase/BP_Phase.BP_Phase_C'");
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/Yin/BP_Yin.BP_Yin_C'");

	DefaultPawnClass = nullptr;

	CHelpers::GetClass<APawn>(&PlayerCharacterClass[0], "Blueprint'/Game/_Project/Characters/Players/Belica/BP_Belica.BP_Belica_C'");
	CHelpers::GetClass<APawn>(&PlayerCharacterClass[1], "Blueprint'/Game/_Project/Characters/Players/Phase/BP_Phase.BP_Phase_C'");
	CHelpers::GetClass<APawn>(&PlayerCharacterClass[2], "Blueprint'/Game/_Project/Characters/Players/Yin/BP_Yin.BP_Yin_C'");

	USoundCue* cue;
	CHelpers::GetAsset(&cue, "SoundCue'/Game/_Project/Sounds/battle01_Cue.battle01_Cue'");
	BGMs.Add(cue);
	CHelpers::GetAsset(&cue, "SoundCue'/Game/_Project/Sounds/battle02_Cue.battle02_Cue'");
	BGMs.Add(cue);

	Audio = UGameplayStatics::CreateSound2D(GetWorld(), BGMs[UKismetMathLibrary::RandomIntegerInRange(0, BGMs.Num() - 1)]);
}

void ACStoryGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(NewPlayer->GetPawn() != nullptr)
		NewPlayer->GetPawn()->DetachFromControllerPendingDestroy();

	FVector position = FVector(6800, 1400, 300);
	APawn* newunit = Cast<APawn>(GetWorld()->SpawnActor(PlayerCharacterClass[playercharacterindex++], &position));
	//APawn* newunit = Cast<APawn>(GetWorld()->SpawnActor(PlayerCharacterClass[2], &position));

	NewPlayer->Possess(newunit);

}

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Find & Save SpawnPoints
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSpawnPoint::StaticClass(), actors);
	for (AActor* actor : actors)
		SpawnPoints.Add(Cast<ACSpawnPoint>(actor));
	if (actors.Num() < 1) { UE_LOG(LogTemp, Error, TEXT("Cannot Found SpawnPoints")); return; }

	actors.Empty();
	actors.Shrink();

	// Find & Save GoalPoints
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGoalPoint::StaticClass(), actors);
	for (AActor* actor : actors)
		GoalPoints.Add(Cast<ACGoalPoint>(actor));
	if (actors.Num() < 1) { UE_LOG(LogTemp, Error, TEXT("Cannot Found GoalPoints")); return; }

	// Load StoryMapData
	StoryMapData = Cast<UCGameInstance>(GetGameInstance())->GetCurrentStoryMap();
	if (StoryMapData != nullptr)
	{
		CHelpers::GetAssetDynamic(&DataTable, StoryMapData->DataPath);
		Money = StoryMapData->Money;
		Life = StoryMapData->Lifes;
	}
	else // Play PlayLevel In Editor = DEBUG Only
	{
		CHelpers::GetAssetDynamic(&DataTable, "DataTable'/Game/_Project/DataTables/DT_StoryMap_Test.DT_StoryMap_Test'");
		Money = 10000;
		Life = 30;
	}

	actors.Empty();
	actors.Shrink();

	// Find & Save Door
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStartDoor::StaticClass(), actors);
	for (AActor* actor : actors)
		Doors.Add(Cast<AStartDoor>(actor));
	if (actors.Num() < 1) { UE_LOG(LogTemp, Error, TEXT("Cannot Found StartDoor")); return; }

	// ¸ÊÀÌ ¹Ù²ð ¶§ ¸¶´Ù ÃÊ±âÈ­
	Score = 0;
	RoundAmount = 0;
	WaveCount = 1;
	CurrentRound = 1;
	bStarted = true;

	DataTable->GetAllRows<FSpawnData>("GetAllRows", RoundDatas);
}

void ACStoryGameMode::DecreaseLifes()
{
	Life--;
	CLog::Print(FString::FromInt(Life) + " Life Left");

	if (Life < 1)
	{
		UWorld* world = GetWorld();
		CheckNull(world);

		APlayerController* controller = world->GetFirstPlayerController();
		CheckNull(controller);

		
		controller->ConsoleCommand("Quit");
	}
}

void ACStoryGameMode::StartNextRound()
{
	if (bStarted == false) return;

	bStarted = false;

	if (CurrentRound == 1) 
	{
		OpenDoor();
	}
		

	TArray<FSpawnData*> roundDatas;
	for (FSpawnData* data : RoundDatas)
	{
		if (data->Round == CurrentRound)
			roundDatas.Add(data);
	}

	for (int32 i = 0; i < roundDatas.Num(); i++)
	{
		RoundAmount += roundDatas[i]->SpawnCount;
	}
	
	RoundWave();

	//Audio->SetSound(BGMs[UKismetMathLibrary::RandomIntegerInRange(0, BGMs.Num() - 1)]);
	//Audio->SetActive(true);
}

void ACStoryGameMode::SpawnMonster()
{
	FActorSpawnParameters spawn;
	spawn.bNoFail;

	GetWorld()->SpawnActor<ACEnemy>(Monclass, SpawnTransform, spawn);
}

void ACStoryGameMode::GameClear()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!!player)
		player->PlayGameMessage("Game Clear!!");
	
}

void ACStoryGameMode::BossRound()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPlayer::StaticClass(), actors);
	for (AActor* actor : actors)
	{
		actor->SetActorLocation(FVector(-61230, -9410, 260));
	}
}

void ACStoryGameMode::OpenDoor_Implementation()
{
	for (AStartDoor* doors : Doors)
		doors->OpenDoor();
}

void ACStoryGameMode::RoundWave()
{
	TArray<FSpawnData*> roundDatas = CurrentRoundDatas();

	if (roundDatas.Num() < WaveCount)
	{
		WaveCount = 1;
		return;
	}

	int32 wavedata = WaveCount - 1;
	Monclass = roundDatas[wavedata]->MonsterRef;

	for (int32 i = 0; i < SpawnPoints.Num(); i++)
	{
		if (SpawnPoints[i]->PathNum == (int32)roundDatas[wavedata]->SpawnLocationIndex)
			SpawnTransform.SetLocation(SpawnPoints[i]->GetActorLocation() + FVector(0, 0, 88));
	}
	
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACStoryGameMode::SpawnMonster, 1.f, true);
	
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "ClearSapwn");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, (float)roundDatas[wavedata]->SpawnCount + 0.1f, false);
}

TArray<FSpawnData*> ACStoryGameMode::CurrentRoundDatas()
{
	TArray<FSpawnData*> roundDatas;

	for (FSpawnData* data : RoundDatas)
	{
		if (data->Round == CurrentRound)
			roundDatas.Add(data);
	}
	
	return roundDatas;
}

void ACStoryGameMode::ClearSapwn()
{
	GetWorldTimerManager().ClearTimer(timerHandle);
	WaveCount++;
	RoundWave();
}

void ACStoryGameMode::DecreaseRoundCount()
{
	RoundAmount--;
	if (RoundAmount == 0)
	{
		CurrentRound++;
		if (CurrentRound == 2)
			BossRound();

		bStarted = true;
		Audio->Stop();
	}
}
