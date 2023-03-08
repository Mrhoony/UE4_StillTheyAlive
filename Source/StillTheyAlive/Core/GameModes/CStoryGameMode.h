#pragma once

#include "CoreMinimal.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Core/Structs/FSpawnData.h"
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
	UFUNCTION(BlueprintCallable)
		void DecreaseLifes();

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
	void DecreaseRoundCount();

public:
	FORCEINLINE int32 GetScore() const { return Score; }
	FORCEINLINE int32 GetMoney() const { return Money; }
	FORCEINLINE int32 GetLife() const { return Life; }


private:
	UFUNCTION()
	void SpawnMonster();

	UFUNCTION()
	void ClearSapwn();

private:
	void RoundWave();
	void GameClear();

	TArray<FSpawnData*> CurrentRoundDatas();
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
	int32 Life;

	TArray<class ACSpawnPoint*> SpawnPoints;
	TArray<class ACGoalPoint*> GoalPoints;
	TArray<class AActor*> SpawnMonsters;	
	TArray<FSpawnData*> RoundDatas;

	int32 RoundAmount = 0;
	int32 WaveCount = 1;
	int CurrentRound = 1;
	bool bStarted = true;
	FTransform SpawnTransform;
	UClass* Monclass;

	FTimerHandle timerHandle;

	FStoryMapData* StoryMapData;
};
