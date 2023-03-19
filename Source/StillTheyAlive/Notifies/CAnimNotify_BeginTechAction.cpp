#include "CAnimNotify_BeginTechAction.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/ActionData/CDoAction.h"

FString UCAnimNotify_BeginTechAction::GetNotifyName_Implementation() const
{
	return "BeginTech";
}

void UCAnimNotify_BeginTechAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	deck->GetCurrentPerk()->GetCurrent()->GetDoAction()->Begin_DoAction_R();
}

