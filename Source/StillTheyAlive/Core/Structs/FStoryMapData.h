#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FRoundData.h"
#include "FStoryMapData.generated.h"

USTRUCT(BlueprintType)
struct FStoryMapData : public FTableRowBase
{
	GENERATED_BODY()

		/*
		* // �����
		* // ����̺�
		* // ��ȯ��ġ�ε���
		* // ���
		* // ��������
		*/

public:
	UPROPERTY(EditAnywhere)
		int Round;

	UPROPERTY(EditAnywhere)
		int Wave;

	UPROPERTY(EditAnywhere)
		int SpawnLocationIndex;

	UPROPERTY(EditAnywhere)
		int SpawnCount;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MonsterRef;
};

UCLASS()
class STILLTHEYALIVE_API UFStoryMapData : public UObject { GENERATED_BODY() };
