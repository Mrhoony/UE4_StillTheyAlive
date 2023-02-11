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

	CHelpers::GetAsset<UDataTable>(&DataTable, "DataTable'/Game/_Project/DataTables/DT_SpawnTest.DT_SpawnTest'");
}

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	// Moeny = // CGameInstance���� ���������̺��� ���� �о�´�.
	// Lifes = // CGameInstance���� ���������̺��� ���� �о�´�.
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
	// NoticeUI �����
	// ���� ���� ���
	// ���������̺��� ���忡 �ش��ϴ� ���� �ҷ�����
	// ��ġ�� �ʰ� ��ȯ

	for (FStoryMapData* data : RoundDatas)
	{
		ACEnemy* enemy = GetWorld()->SpawnActor<ACEnemy>(data->MonsterRef, SpawnPoints[data->SpawnLocationIndex]->GetTransform());
		enemy->Move(GoalPoints[0]->GetActorLocation());
	}	
}

void ACStoryGameMode::UdpateCurrentRoundDatas()
{
	TArray<FStoryMapData*> datas;
	DataTable->GetAllRows<FStoryMapData>("", datas);

	for (FStoryMapData* data : datas)
	{
		if (data->Round == CurrentRound)
		{
			RoundDatas.Add(data);
		}
	}
}

/*
* �÷��̾ GŰ�� ������ ���尡 ���۵ȴ�.
* �÷��̾ GŰ�� ������ �� "Press G-Key to Start Next Round" �ؽ�Ʈ�� �����Ѵ�.
* ���Ӹ��� GŰ�� �������� ���带 �����ϴ� �Լ��� ȣ���ϰ� �ʿ� ������ ��ȯ�������� ���͸� ��ȯ�Ѵ�.
* << ��ȯ������ ��� �޾ƿ� ������?
* ���ʹ� ��ȯ�������� ������������ �̵��ϸ�, ���������� �����ϸ� �����ȴ�.
* ���Ͱ� ���������� �����ؼ� �����Ǹ� ���Ӹ�忡�� �������� 1�� ��´�.
* << TArray<Monster>�� ����ִ� ���Ͱ� �����Ǿ� Nullptr�� �� ��� TArray<Monster>().Num()�� ������?
* << ���� �����ִ� ������ ���� ��� �Ǻ��� ������?
* ���Ӹ���� �������� 0�̵Ǹ� �����й�.
*/