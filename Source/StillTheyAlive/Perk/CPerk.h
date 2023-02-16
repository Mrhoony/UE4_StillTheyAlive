#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.h"
#include "Components/CDeckComponent.h"
#include "CPerk.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACPerk : public ACAttachment
{
	GENERATED_BODY()
	
public:	
	ACPerk();
	
protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class UActionObject* GetCurrent() { return DataObject; }
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

	UPROPERTY()
		class UActionObject* DataObject;

	UPROPERTY(EditAnywhere)
		class UTexture2D* PerkImage;
};
