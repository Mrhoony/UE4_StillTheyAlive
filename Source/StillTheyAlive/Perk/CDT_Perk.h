#pragma once

#include "CoreMinimal.h"
#include "CPerk.h"
#include "Engine/DataTable.h"
#include "CDT_Perk.generated.h"

USTRUCT(BlueprintType)
struct FPerkData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EPerkType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

};

UCLASS()
class STILLTHEYALIVE_API UCDT_Perk : public UDataTable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FPerkData PerkData;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;
};
