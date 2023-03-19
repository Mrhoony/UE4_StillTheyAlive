#include "AN_Skill1.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_Boss.h"

FString UAN_Skill1::GetNotifyName_Implementation() const
{
	return "Skill1";
}

void UAN_Skill1::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if (!!boss)
		boss->BeginSkill();
}
