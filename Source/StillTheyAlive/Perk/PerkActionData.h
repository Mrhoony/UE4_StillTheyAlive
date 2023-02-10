#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PerkActionData.generated.h"

USTRUCT(BlueprintType)
struct FAnimontage
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FAnimontage Montage;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;

};


USTRUCT(BlueprintType)
struct FDoAction : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.f;

	UPROPERTY(EditAnywhere, Category = "Effect")
		float HitStop;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		FString SpecificCollisionName = "None";

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACThrow> ThrowClass;

	UPROPERTY(EditAnywhere)
		bool Diversity;

	UPROPERTY(EditAnywhere)
		FAnimontage DivMontage;
};

USTRUCT(BlueprintType)
struct FTechDoAction : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.f;

	UPROPERTY(EditAnywhere, Category = "Effect")
		float HitStop;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		FString SpecificCollisionName = "None";

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACThrow> ThrowClass;
};


UCLASS()
class STILLTHEYALIVE_API UPerkActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

public:
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

private:
	FString GetLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TArray<FDoAction> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TechDoAction")
		TArray<FTechDoAction> TechDoActionDatas;

private:
	class ACAttachment* Attachment;
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;
};
