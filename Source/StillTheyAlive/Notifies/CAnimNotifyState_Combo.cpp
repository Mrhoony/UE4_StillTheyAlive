#include "CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/CDoAction_Melee.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(deck->GetCurrentPerk()->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(deck->GetCurrentPerk()->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->DisableCombo();
}
