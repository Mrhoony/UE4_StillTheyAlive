#include "AN_Skill2.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_Boss.h"

FString UAN_Skill2::GetNotifyName_Implementation() const
{
	return "Skill2";
}

void UAN_Skill2::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if (!!boss)
		boss->BeginSkill2();
}
