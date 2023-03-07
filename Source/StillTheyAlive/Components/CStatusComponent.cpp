#include "CStatusComponent.h"
#include "Global.h"

#include "Widgets/CHUD.h"
#include "Widgets/CUserWidget_PlayerStatus.h"
#include "Widgets/CUserWidget_Health.h"
#include "Characters/CAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Components/PanelWidget.h"
#include "Net/UnrealNetwork.h"

UCStatusComponent::UCStatusComponent()
{
	CHelpers::GetClass(&WidgetClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_PlayerStatus.WB_PlayerStatus_C'");
	SetIsReplicated(true);
}

void UCStatusComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCStatusComponent, Health);
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Health = MaxHealth;
}

void UCStatusComponent::OnRep_Update()
{
	ACAICharacter* ai = Cast<ACAICharacter>(OwnerCharacter);
	if (!!ai)
	{
		ai->HealthBar->Update(Health, MaxHealth);
		CLog::Print("OnRep_Update");
	}
}

void UCStatusComponent::CreateStatusWidget(UCHUD* HUD)
{
	CheckNull(WidgetClass);
	CheckNull(HUD);

	APlayerController* playerController = Cast<APlayerController>(OwnerCharacter->GetController());
	CheckNull(playerController);

	Widget = Cast<UCUserWidget_PlayerStatus>(CreateWidget(playerController, WidgetClass));
	Widget->SetOwnerComponent(this);

	HUD->Slot_Status->AddChild(Widget);
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
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UCStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}