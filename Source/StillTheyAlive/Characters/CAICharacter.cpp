#include "CAICharacter.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"

ACAICharacter::ACAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &HealthWidget, "HealthWidget", GetMesh());

	// Create ActorComponent
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Deck, "Deck");


	// Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/_Project/Characters/Players/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&animInstanceClass, "AnimBlueprint'/Game/_Project/Characters/Players/AB_CPlayer.AB_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	TSubclassOf<UCUserWidget_Health> healthWidgetClass;
	CHelpers::GetClass<UCUserWidget_Health>(&healthWidgetClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_Health.WB_Health_C'");
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACAICharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	State->OnStateTypeChanged.AddDynamic(this, &ACAICharacter::OnStateTypeChanged);

	HealthWidget->InitWidget();
	UCUserWidget_Health* healthWidgetObject = Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidgetObject)
		healthWidgetObject->Update(Status->GetHealth(), Status->GetMaxHealth());
}

void ACAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActionCoolTime > 0)
		ActionCoolTime -= DeltaTime;
	if (ActionCoolTime < 0)
		ActionCoolTime = 0.f;
}



