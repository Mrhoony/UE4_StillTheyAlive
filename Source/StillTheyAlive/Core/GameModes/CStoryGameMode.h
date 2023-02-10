#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Structs/FStoryMapData.h"
#include "CStoryGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreValueChanged, int32, PrevValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoneyValueChanged, int32, PrevValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLifeValueChanged, int32, PrevValue, int32, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoundStateChanged, bool, NewValue);

UCLASS()
class STILLTHEYALIVE_API ACStoryGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	//void Initialize(DataTable data);
	void StartNextRound(); // ���� ���� ����
	void FinishThisRound();

public:
	void IncreaseScore(const int32& InAmount);
	void IncreaseMoney(const int32& InAmount);
	void DecreaseMoney(const int32& InAmount);	
	void IncreaseLifes(const int32& InAmount);
	void DecreaseLifes(const int32& InAmount);

public:
	FScoreValueChanged OnScoreValueChanged;
	FMoneyValueChanged OnMoneyValueChanged;
	FLifeValueChanged OnLifeValueChanged;
	FRoundStateChanged OnRoundStateChanged;

private:
	int32 Score;
	int32 Money;
	int32 Lifes;

	TArray<class AActor*> SpawnMonsters;
	
	FStoryMapData Datas;

	bool bStarted;
};

// �÷��̷��� ���۽� �ش� ������ �ش��ϴ� �������������̺��� �ҷ��´�
// �״��� 1������� �����ϹǷ� 1���忡 �ش��ϴ� ����üŸ���� �����͸� �迭�� �ҷ��´�.
// ���̺긦 �����ؼ� ���̺������ ��ȯ�� ������
// ���� �� ��ȯ���� �����̽ð����� �����ؼ� Ư�� �ð��� �Ǹ� �ٷ� ��ȯ�ǰԲ� �� ������ ���
