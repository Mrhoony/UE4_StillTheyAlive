#include "CAnimNotify_EndAction.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/ActionData/CDoAction.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	deck->GetCurrentPerk()->GetCurrent()->GetDoAction()->End_DoAction();
}

