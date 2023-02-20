#include "CStoryGameMode.h"
#include "Global.h"

#include "Core/CGameInstance.h"
#include "Engine/DataTable.h"
#include "Characters/Enemies/CEnemy.h"
#include "Maps/CSpawnPoint.h"

ACStoryGameMode::ACStoryGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
}

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr) return;
	Score = 0;
	// Moeny = // CGameInstance에서 데이터테이블의 값을 읽어온다.
	// Lifes = // CGameInstance에서 데이터테이블의 값을 읽어온다.
	//GetGameInstance()->SetCurrnetGameMode();
	//Cast<UCGameInstance>(GetGameInstance())->SetGameModeTypeStory();

	DataTable->GetAllRows<FStoryMapData>("", RoundDatas);


	// Find & Save SpawnPoints
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSpawnPoint::StaticClass(), actors);
	for (AActor* actor : actors)
		SpawnPoints.Add(Cast<ACSpawnPoint>(actor));

	//// Find & Save GoalPoints
	//actors.Empty();
	//actors.Shrink();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGoalPoint::StaticClass(), actors);
	//for (AActor* actor : actors)
	//	GoalPoints.Add(Cast<ACGoalPoint>(actor));

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
	// NoticeUI 숨기기
	// 시작 음악 재생
	// 데이터테이블에서 라운드에 해당하는 몬스터 불러오기
	// 겹치지 않게 소환
	TArray<FStoryMapData*> roundDatas;

	for (FStoryMapData* data : RoundDatas)
	for (FSpawnData* data : RoundDatas)
	{
		if (data->Round == CurrentRound)
			roundDatas.Add(data);
	}	
		for (int i = 0; i < data->SpawnCount; i++)
		{
			//ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
			ACEnemy* enemy = GetWorld()->SpawnActorDeferred<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
			enemy->SetMoveDest(GoalPoints[0]->GetActorLocation());
			UGameplayStatics::FinishSpawningActor(enemy, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
		}
	}
}

	for (int32 i = 0; i < roundDatas.Num(); i++)
	{
		RoundAmount += roundDatas[i]->SpawnCount;
		for (int32 z = 0; z < roundDatas[i]->SpawnCount; z++)
		{
			FTimerHandle waitHandle;
		
				FTransform transform;
				for (int32 x = 0; x < SpawnPoints.Num(); x++) 
				{
					if(SpawnPoints[x]->PathNum == (int32)roundDatas[i]->SpawnLocationIndex) 
					transform.SetLocation(SpawnPoints[x]->GetActorLocation() + FVector(0,0,300));
				}
					
				ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(roundDatas[i]->MonsterRef, transform);
		}
	}
}

void ACStoryGameMode::UdpateCurrentRoundDatas()
{
	//TArray<FStoryMapData*> datas;
	//DataTable->GetAllRows<FStoryMapData>("", datas);

	//for (FStoryMapData* data : datas)
	//{
	//	if (data->Round == CurrentRound)
	//	{
	//		RoundDatas.Add(data);
	//	}
	//}
}
