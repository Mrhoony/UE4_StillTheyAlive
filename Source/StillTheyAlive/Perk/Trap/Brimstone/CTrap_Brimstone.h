#pragma once

#include "CoreMinimal.h"
#include "Perk/Trap/CTrap.h"
#include "CTrap_Brimstone.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACTrap_Brimstone : public ACTrap
{
	GENERATED_BODY()

public:
	ACTrap_Brimstone();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
		void Burn(class AActor* OtherActor);

private:
	UFUNCTION()
		void RegenerateUseResource();

//=======================================================
// [Variables]
//=======================================================
private:
	FString Name;			// �̸�
	FString Description;	// ����
	ETrapType TrapType;		// Ÿ��
	int32 BuyPrice;			// �������� �����Ҷ� ����
	int32 BuildCost;		// ������ ����
	float MaxMana = 100.0f;	// ������ �ϱ����� �ڿ��� �ƽ�
	float CurMana;			// ���� �ڿ���
	float NeedMana = 30.0f;	// ���ݽ� �ʿ��� �ڿ���
	float BaseDamage;		// ���������̺��� �о�� �⺻ ���ݷ�
	float AddedDamage;		// ���׷��̵峪 �����̻� ���� �߰� ���ݷ�
	float FinalDamage;		// base + added

	// ���� ����
	//FString Upgrade;		// ���׷��̵� �̸�
	//int32 Upgrade1Cost;	// 1��������
	//int32 Upgrade2Cost;	// 2��������
	//int32 Upgrade3Cost;
	//FString Unique1;		// Ư�� �̸�
	//FString Unique2;		//
	//int32 UniqueCost;		// Ư�� ����
	//bool HasUnique;		// Ư���� ����� / �Ȼ����
};
