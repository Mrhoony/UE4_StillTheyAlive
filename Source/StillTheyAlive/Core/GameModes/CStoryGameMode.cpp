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

	UdpateCurrentRoundDatas(); 
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
	TArray<FSpawnData*> roundDatas;

	for (FSpawnData* data : RoundDatas)
	{
		if (data->Round == CurrentRound)
			roundDatas.Add(data);
	}

	for (int32 i = 0; i < roundDatas.Num(); i++)
	{
		RoundAmount += roundDatas[i]->SpawnCount;
		for (int32 z = 0; z < roundDatas[i]->SpawnCount; z++)
		{
			FTransform transform;
			for (int32 x = 0; x < SpawnPoints.Num(); x++)
			{
				if (SpawnPoints[x]->PathNum == (int32)roundDatas[i]->SpawnLocationIndex)
					transform.SetLocation(SpawnPoints[x]->GetActorLocation() + FVector(0, 0, 300));
			}

			ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(roundDatas[i]->MonsterRef, transform);
		}
	}
}

void ACStoryGameMode::UdpateCurrentRoundDatas()
{
	TArray<FSpawnData*> datas;
	DataTable->GetAllRows<FSpawnData>("GetAllRows", datas);

	for (FSpawnData* data : datas)
	{
		if (data->Round == CurrentRound)
		{
			RoundDatas.Add(data);
		}
	}
}
