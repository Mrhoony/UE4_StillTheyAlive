#include "CUserWidget_PlayerStatus.h"
#include "Global.h"

#include "Components/CStatusComponent.h"

#include "Components/ProgressBar.h"

void UCUserWidget_PlayerStatus::NativeConstruct()
{
	Super::NativeConstruct();

	//PrintLine();
	UpdateHealthBar();
	UpdateManaBar();
}

void UCUserWidget_PlayerStatus::UpdateHealthBar()
{
	float maxHealth = OwnerComponent->GetMaxHealth();
	float curHealth = OwnerComponent->GetHealth();

	float healthPercent = curHealth / maxHealth;
	healthPercent = FMath::Clamp(healthPercent, 0.f, 1.f);

	HealthBar->SetPercent(healthPercent);
}

void UCUserWidget_PlayerStatus::UpdateManaBar()
{
	// 마나 관련 스탯이 없음
	/*float maxHealth = OwnerComponent->GetMaxHealth();
	float curHealth = OwnerComponent->GetHealth();

	float healthPercent = curHealth / maxHealth;
	healthPercent = FMath::Clamp(healthPercent, 0.f, 1.f);

	ManaBar->Percent = healthPercent;*/

	ManaBar->SetPercent(1.f);
}