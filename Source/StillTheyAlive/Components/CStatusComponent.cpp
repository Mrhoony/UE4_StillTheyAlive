#include "CStatusComponent.h"
#include "Global.h"

#include "Widgets/CUserWidget_PlayerStatus.h"

#include "Blueprint/UserWidget.h"

UCStatusComponent::UCStatusComponent()
{
	CHelpers::GetClass(&WidgetClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_PlayerStatus.WB_PlayerStatus_C'");
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UCStatusComponent::CreateStatusWidget()
{	
	CheckNull(WidgetClass);
	Widget = CreateWidget<UCUserWidget_PlayerStatus, APlayerController>(GetOwner()->GetInstigatorController<APlayerController>(), WidgetClass);
	Widget->OwnerComp = this;	
}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}

void UCStatusComponent::IncreaseHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UCStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}
