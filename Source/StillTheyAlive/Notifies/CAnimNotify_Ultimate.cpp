#include "CAnimNotify_Ultimate.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/ActionData/CDoAction.h"

FString UCAnimNotify_Ultimate::GetNotifyName_Implementation() const
{
	return "Ultimate";
}

void UCAnimNotify_Ultimate::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	deck->GetCurrentPerk()->GetCurrent()->GetDoAction()->Begin_Ultimate();
}


