#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.h"
#include "Components/CDeckComponent.h"
#include "CAttachment.h"
#include "CPerk.generated.h"

USTRUCT(BlueprintType)
struct FPerkInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture2D* PerkImage;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACPerk> PerkClass;
};

UCLASS()
class STILLTHEYALIVE_API ACPerk : public ACAttachment
{
	GENERATED_BODY()
	
public:	
	ACPerk();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UPerkActionData* GetCurrent() { return Data; }

	FORCEINLINE EPerkType GetPerkType() { return PerkType; }
public:
	UFUNCTION()
		virtual void TechAction() {};

	void BeginData(class ACharacter* DeckCharacter);
	
public:
	UPROPERTY(EditDefaultsOnly)
		EPerkType PerkType;

	UPROPERTY(EditDefaultsOnly)
		class UPerkActionData* Data;
};