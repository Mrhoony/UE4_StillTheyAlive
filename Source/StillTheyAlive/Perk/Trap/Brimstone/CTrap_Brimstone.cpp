#include "CTrap_Brimstone.h"
#include "Global.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ACTrap_Brimstone::ACTrap_Brimstone()
{
}

void ACTrap_Brimstone::BeginPlay()
{
	Super::BeginPlay();

	CurMana = MaxMana;
	UKismetSystemLibrary::K2_SetTimer(this, "RegenerateUseResource", 1.0f, true);
}

void ACTrap_Brimstone::Burn(AActor* OtherActor)
{
	if (OtherActor == this) return;
	//ACharacter* other = Cast<ACharacter>(OtherActor);

	if (CurMana < NeedMana)
	{
		CLog::Print("Not Enough Mana. Current Mana is : " + FString::SanitizeFloat(CurMana));
		return;
	}
	
	CurMana -= NeedMana;
	CLog::Print("Burning! Current Mana is : " + FString::SanitizeFloat(CurMana));
}

void ACTrap_Brimstone::RegenerateUseResource()
{
	CurMana += 1.0f;
	CurMana = FMath::Clamp<float>(CurMana, 0, MaxMana);
}