#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/ActionData/CEquipment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	if(!!deck->GetCurrentPerk())
	deck->GetCurrentPerk()->GetCurrent()->GetEquipment()->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	if(!!deck->GetCurrentPerk())
	deck->GetCurrentPerk()->GetCurrent()->GetEquipment()->End_Equip();
}
