#include "CStatusComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Blueprint/UserWidget.h"

UCStatusComponent::UCStatusComponent()
{
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentMana = MaxMana;
}

void UCStatusComponent::CreateStatusWidget()
{	
	/*CheckNull(WidgetClass);
	Widget = CreateWidget<UCUserWidget_PlayerStatus, APlayerController>(GetOwner()->GetInstigatorController<APlayerController>(), WidgetClass);
	Widget->OwnerComp = this;*/	
}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}

void UCStatusComponent::SetSpeed(EWalkSpeedTpye InType)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	movement->MaxWalkSpeed = Speed[(int32)InType];
}

void UCStatusComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UCStatusComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}
