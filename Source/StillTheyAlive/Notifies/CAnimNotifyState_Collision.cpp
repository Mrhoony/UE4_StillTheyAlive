#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CDeckComponent.h"
#include "Perk/PerkActionData.h"
#include "Perk/CPerk.h"
#include "Perk/CDoAction_Melee.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(deck->GetCurrentPerk()->GetCurrent()->GetDoAction());
	if (!!melee)
	{
		FString collisionName = melee->GetSpecificCollisionName();
		deck->GetCurrentPerk()->GetCurrent()->GetAttachment()->OnCollisions(collisionName);
	}
	else
		deck->GetCurrentPerk()->GetCurrent()->GetAttachment()->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(MeshComp->GetOwner());
	CheckNull(deck);

	deck->GetCurrentPerk()->GetCurrent()->GetAttachment()->OffCollisions();

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(deck->GetCurrentPerk()->GetCurrent()->GetDoAction());
	CheckNull(melee);
	melee->ClearHittedCharacters();
}
