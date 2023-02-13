#include "CPerk.h"
#include "Engine/Texture2D.h"
#include "Global.h"
#include "CEquipment.h"
#include "Components/CStatusComponent.h"
#include "PerkActionData.h"
#include "GameFramework/Character.h"

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
		Data->BeginPlay(DeckCharacter, this);
}
