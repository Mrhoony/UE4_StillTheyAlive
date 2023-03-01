#include "CAnimNotify_Charging.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/ActionData/PerkActionData.h"
#include "Perk/Weapons/CWeapon.h"
#include "Perk/ActionData/CDoAction.h"

FString UCAnimNotify_Charging::GetNotifyName_Implementation() const
{
	return "Charging";
}

void UCAnimNotify_Charging::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	ACDoAction* doAction = Cast<ACDoAction>(deck->GetCurrentPerk()->GetCurrent()->GetDoAction());
	CheckNull(doAction);

	if (doAction->IsCharging() == false) return;
	else
	{
		ACWeapon* weapon = Cast<ACWeapon>(deck->GetCurrentPerk());
		if (!!weapon)
		{
			weapon->ChargingMontage();
		}
	}
}


