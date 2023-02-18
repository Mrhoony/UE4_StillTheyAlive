#include "CStoryGameMode.h"
#include "Global.h"

#include "Core/CGameInstance.h"
#include "Maps/CSpawnPoint.h"
#include "Engine/DataTable.h"
#include "Maps/CGoalPoint.h"
#include "Characters/Enemies/CEnemy.h"

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
	
	// Find & Save GoalPoints
	actors.Empty();
	actors.Shrink();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGoalPoint::StaticClass(), actors);
	for (AActor* actor : actors)
		GoalPoints.Add(Cast<ACGoalPoint>(actor));

	// Load StoryMapData
	StoryMapData = Cast<UCGameInstance>(GetGameInstance())->GetCurrentStoryMap();	
	CHelpers::GetAssetDynamic(&DataTable, StoryMapData->DataPath);
	Money = StoryMapData->Money;
	Lifes = StoryMapData->Lifes;
	Score = 0;

	UdpateCurrentRoundDatas(); 
}

void ACStoryGameMode::DecreaseLifes()
{
	Lifes--;
	CLog::Print(FString::FromInt(Lifes) + " Lifes Left");

	if (Lifes < 1)
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
	for (FSpawnData* data : RoundDatas)
	{
		for (int i = 0; i < data->SpawnCount; i++)
		{
			//ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
			ACEnemy* enemy = GetWorld()->SpawnActorDeferred<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
			enemy->SetMoveDest(GoalPoints[0]->GetActorLocation());
			UGameplayStatics::FinishSpawningActor(enemy, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
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
