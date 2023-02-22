#include "CPerk.h"
#include "Engine/Texture2D.h"
#include "Global.h"
#include "ActionData/CEquipment.h"
#include "ActionData/PerkActionData.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "ActionData/CActionObject.h"
#include "ActionData/CDoAction.h"

ACPerk::ACPerk()
{
}

void ACPerk::BeginPlay()
{
	Super::BeginPlay();
}

void ACPerk::BeginData(ACharacter* DeckCharacter)
{
	if (!!Data)
		Data->BeginPlay(DeckCharacter, this, &DataObject);
}

void ACPerk::Dead()
{
	OffAllCollisions();
}

void ACPerk::End_Dead()
{
	DataObject->GetDoAction()->Destroy();
	DataObject->GetEquipment()->Destroy();
	DataObject->GetAttachment()->Destroy();
}

void ACPerk::OffAllCollisions()
{
	DataObject->GetAttachment()->OffCollisions();
}
