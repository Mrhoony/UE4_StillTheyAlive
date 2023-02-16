#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionObject.h"
#include "PerkActionData.generated.h"

UCLASS()
class STILLTHEYALIVE_API UPerkActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwnerCharacter, class ACAttachment* AttachPerk, UCActionObject** OutObject);

private:
	FString GetLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName);

public:

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

};
