#pragma once

#include "CoreMinimal.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Core/Structs/FStoryMapData.h"
#include "CStoryGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreValueChanged, int32, PrevValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoneyValueChanged, int32, PrevValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLifeValueChanged, int32, PrevValue, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoundStateChanged, bool, NewValue);

UCLASS()
class STILLTHEYALIVE_API ACStoryGameMode : public ACPlayGameMode
{
	GENERATED_BODY()

public:
	ACStoryGameMode();

protected:
	virtual void BeginPlay() override;

public:
	//void Initialize(DataTable data);
	virtual void StartNextRound() override; // 다음 라운드 실행
	void FinishThisRound();

public:
	void IncreaseScore(const int32& InAmount);
	void IncreaseMoney(const int32& InAmount);
	void DecreaseMoney(const int32& InAmount);	
	void IncreaseLifes(const int32& InAmount);
	void DecreaseLifes(const int32& InAmount);

	FORCEINLINE void DecreaseRoundAmount() { --RoundAmount; }
private:
	void UdpateCurrentRoundDatas();

public:
	FScoreValueChanged OnScoreValueChanged;
	FMoneyValueChanged OnMoneyValueChanged;
	FLifeValueChanged OnLifeValueChanged;
	FRoundStateChanged OnRoundStateChanged;

private:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* DataTable;

private:
	int32 Score;
	int32 Money;
	int32 Lifes;

	TArray<class ACSpawnPoint*> SpawnPoints;
	TArray<class ACGoalPoint*> GoalPoints;
	TArray<FVector> SpawnLocation;
	TArray<class AActor*> SpawnMonsters;
	
	TArray<FStoryMapData*> RoundDatas;

	bool bStarted;
	int RoundAmount = 0;
	int CurrentRound = 1;
};

// 플레이레벨 시작시 해당 레벨에 해당하는 스폰데이터테이블을 불러온다
// 그다음 1라운드부터 시작하므로 1라운드에 해당하는 구조체타입의 데이터를 배열로 불러온다.
// 웨이브를 유지해서 웨이브단위로 소환할 것인지
// 시작 후 소환까지 딜레이시간으로 변경해서 특정 시간이 되면 바로 소환되게끔 할 것인지 고민
