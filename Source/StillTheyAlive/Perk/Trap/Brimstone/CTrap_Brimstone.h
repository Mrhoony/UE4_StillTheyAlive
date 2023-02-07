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
	FString Name;			// 이름
	FString Description;	// 설명
	ETrapType TrapType;		// 타입
	int32 BuyPrice;			// 상점에서 구매할때 가격
	int32 BuildCost;		// 지을때 가격
	float MaxMana = 100.0f;	// 공격을 하기위한 자원의 맥스
	float CurMana;			// 현재 자원량
	float NeedMana = 30.0f;	// 공격시 필요한 자원량
	float BaseDamage;		// 데이터테이블에서 읽어올 기본 공격력
	float AddedDamage;		// 업그레이드나 상태이상에 따른 추가 공격력
	float FinalDamage;		// base + added

	// 구현 예정
	//FString Upgrade;		// 업그레이드 이름
	//int32 Upgrade1Cost;	// 1레벨가격
	//int32 Upgrade2Cost;	// 2레벨가격
	//int32 Upgrade3Cost;
	//FString Unique1;		// 특성 이름
	//FString Unique2;		//
	//int32 UniqueCost;		// 특성 가격
	//bool HasUnique;		// 특성을 샀는지 / 안샀는지
};
