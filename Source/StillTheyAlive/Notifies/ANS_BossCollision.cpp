#include "ANS_BossCollision.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_Boss.h"

FString UANS_BossCollision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UANS_BossCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if (!!boss)
		boss->BeginAttack();
}

void UANS_BossCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	ACEnemy_Boss* boss = Cast<ACEnemy_Boss>(MeshComp->GetOwner());
	if (!!boss)
		boss->EndAttack();
}
