#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerkActionData.h"
#include "CDoAction.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();
	FORCEINLINE void SetDatas(TArray<FDoAction> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetTechDatas(TArray<FTechDoAction> InDatas) { TechDatas = InDatas; }
	FORCEINLINE bool IsCharging() { return Charging; }

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:

	virtual void DoAction_L() {};
	virtual void End_DoAction_L() {};

	virtual void DoAction_R() {};
	virtual void Begin_DoAction_R() {};
	virtual void DoOffAction_R() {};

	virtual void UltimateAction() {};
	virtual void Begin_Ultimate() {};

	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};

	void OnCharging();
	void OffCharging();

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;
	
	class UCDeckComponent* Deck;

	class UCDeckComponent* Deck;

public:
	TArray<FTechDoAction> TechDatas;

public:
	TArray<FDoAction> Datas;

private:
	bool Charging;
};
