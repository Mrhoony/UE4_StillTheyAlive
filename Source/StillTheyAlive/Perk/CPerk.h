#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionData/CAttachment.h"
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
	FORCEINLINE class UCActionObject* GetCurrent() { return DataObject; }
	FORCEINLINE EPerkType GetPerkType() { return PerkType; }

public:
	UFUNCTION()
		virtual void TechAction() {};
		virtual void Ultimate() {};

public:
	void BeginData(class ACharacter* DeckCharacter);
	
	void OffAllCollisions();

	void Dead();
	void End_Dead();

public:
	UPROPERTY(EditDefaultsOnly)
		EPerkType PerkType;

	UPROPERTY(EditDefaultsOnly)
		class UPerkActionData* Data;

	UPROPERTY()
		class UCActionObject* DataObject;

	UPROPERTY(EditAnywhere)
		class UTexture2D* Icon;
};
