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

	//CHelpers::GetAsset<UDataTable>(&DataTable, "DataTable'/Game/_Project/DataTables/DT_SpawnTest.DT_SpawnTest'");
}

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	// Moeny = // CGameInstance에서 데이터테이블의 값을 읽어온다.
	// Lifes = // CGameInstance에서 데이터테이블의 값을 읽어온다.
	//GetGameInstance()->SetCurrnetGameMode();
	// Cast<UCGameInstance>(GetGameInstance())->SetGameModeTypeStory();

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

	UdpateCurrentRoundDatas();
}

void ACStoryGameMode::StartNextRound()
{
	// NoticeUI 숨기기
	// 시작 음악 재생
	// 데이터테이블에서 라운드에 해당하는 몬스터 불러오기
	// 겹치지 않게 소환

	for (FSpawnData* data : RoundDatas)
	{
		ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
		enemy->Move(GoalPoints[0]->GetActorLocation());
	}
}

void ACStoryGameMode::UdpateCurrentRoundDatas()
{
	/*TArray<FSpawnData*> datas;
	DataTable->GetAllRows<FSpawnData>("GetAllRows", datas);

	for (FSpawnData* data : datas)
	{
		if (data->Round == CurrentRound)
		{
			RoundDatas.Add(data);
		}
	}*/
}

/*
* 플레이어가 G키를 누르면 라운드가 시작된다.
* 플레이어가 G키를 눌렀을 때 "Press G-Key to Start Next Round" 텍스트를 종료한다.
* 게임모드는 G키가 눌렸을때 라운드를 시작하는 함수를 호출하고 맵에 지정된 소환지점에서 몬스터를 소환한다.
* << 소환지점을 어떻게 받아올 것인지?
* 몬스터는 소환지점에서 골인지점까지 이동하며, 골인지점에 도달하면 삭제된다.
* 몬스터가 골인지점에 도달해서 삭제되면 게임모드에서 라이프를 1씩 깎는다.
* << TArray<Monster>에 담겨있던 몬스터가 삭제되어 Nullptr이 된 경우 TArray<Monster>().Num()의 영향은?
* << 현재 남아있는 몬스터의 수를 어떻게 판별할 것인지?
* 게임모드의 라이프가 0이되면 게임패배.
*/