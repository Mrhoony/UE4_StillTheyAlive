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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() {};
	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	/*UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;*/

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;
protected:
	TArray<FDoAction> Datas;
};