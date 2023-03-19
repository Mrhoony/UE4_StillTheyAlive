#include "AN_Throw.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_Boss.h"

FString UAN_Throw::GetNotifyName_Implementation() const
{
	return "Throw";
}

void UAN_Throw::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if(!!boss)
	boss->BeginRangeAttack();
}
