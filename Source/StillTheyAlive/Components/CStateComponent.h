#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateTypes : uint8
{
	Idle, Action, Hit, Dead, Equip, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateTypes, InPrevType, EStateTypes, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsIdle() { return Type == EStateTypes::Idle; }
	FORCEINLINE bool IsAction() { return Type == EStateTypes::Action; }
	FORCEINLINE bool IsHit() { return Type == EStateTypes::Hit; }
	FORCEINLINE bool IsDead() { return Type == EStateTypes::Dead; }
	FORCEINLINE bool IsMax() { return Type == EStateTypes::Max; }

	void SetIdle();
	void SetAction();
	void SetHit();
	void SetEquip();
	void SetDead();

private:
	void ChangeType(EStateTypes InNewType);

//=======================================================
// [Variables]
//=======================================================
public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;
	
private:
	EStateTypes Type;
};
