#include "AN_2Page.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_Boss.h"

FString UAN_2Page::GetNotifyName_Implementation() const
{
	return "2Page";
}

void UAN_2Page::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if (!!boss)
		boss->BeginPage2Skill();
}

