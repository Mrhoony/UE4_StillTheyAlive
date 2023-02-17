#pragma once

#include "CoreMinimal.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Core/Structs/FSpawnData.h"
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
	virtual void StartNextRound() override; // ���� ���� ����
	void FinishThisRound();

public:
	void IncreaseScore(const int32& InAmount);
	void IncreaseMoney(const int32& InAmount);
	void DecreaseMoney(const int32& InAmount);	
	void IncreaseLifes(const int32& InAmount);
	void DecreaseLifes(const int32& InAmount);

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

	TArray<class AActor*> SpawnMonsters;
	
	TArray<FSpawnData*> RoundDatas;

	bool bStarted;

	int CurrentRound = 1;
};

// �÷��̷��� ���۽� �ش� ������ �ش��ϴ� �������������̺��� �ҷ��´�
// �״��� 1������� �����ϹǷ� 1���忡 �ش��ϴ� ����üŸ���� �����͸� �迭�� �ҷ��´�.
// ���̺긦 �����ؼ� ���̺������ ��ȯ�� ������
// ���� �� ��ȯ���� �����̽ð����� �����ؼ� Ư�� �ð��� �Ǹ� �ٷ� ��ȯ�ǰԲ� �� ������ ���
