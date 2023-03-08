#include "CStoryGameMode.h"
#include "Global.h"

#include "Core/CGameInstance.h"
#include "Characters/Enemies/CEnemy.h"
#include "Maps/CSpawnPoint.h"
#include "Maps/CGoalPoint.h"

#include "Engine/DataTable.h"

ACStoryGameMode::ACStoryGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
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
	
	Score = 0;

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
}

void ACStoryGameMode::SpawnMonster()
{
	FActorSpawnParameters spawn;
	spawn.bNoFail;

	GetWorld()->SpawnActor<ACEnemy>(Monclass, SpawnTransform, spawn);
}

void ACStoryGameMode::GameClear()
{

}

void ACStoryGameMode::RoundWave()
{
	TArray<FSpawnData*> roundDatas = CurrentRoundDatas();

	if (roundDatas.Num() < WaveCount)
	{
		WaveCount = 1;
		return;
	}

	CLog::Print("hi");
	int32 wavedata = WaveCount - 1;
	Monclass = roundDatas[wavedata]->MonsterRef;

	for (int32 i = 0; i < SpawnPoints.Num(); i++)
	{
		if (SpawnPoints[i]->PathNum == (int32)roundDatas[wavedata]->SpawnLocationIndex)
			SpawnTransform.SetLocation(SpawnPoints[i]->GetActorLocation() + FVector(0, 0, 88));
	}
	
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACStoryGameMode::SpawnMonster, 1.0f, true, (float)roundDatas[wavedata]->SpawnCount);
	
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "ClearSapwn");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, (float)roundDatas[wavedata]->SpawnCount * 2, false);
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
		if (CurrentRound == 5)
			GameClear();

		bStarted = true;
	}
}
