#include "CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/CDoAction.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	deck->GetCurrentPerk()->GetCurrent()->GetDoAction()->Begin_DoAction();
}

