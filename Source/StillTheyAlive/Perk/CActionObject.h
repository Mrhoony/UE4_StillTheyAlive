#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionObject.generated.h"


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
class STILLTHEYALIVE_API UCActionObject : public UObject
{
	GENERATED_BODY()

public:
	friend class UPerkActionData;

public:
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }

private:
	class ACAttachment* Attachment;
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;
};
