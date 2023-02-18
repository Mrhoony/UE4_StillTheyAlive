#include "CAimAction.h"
#include "Global.h"
#include "Widgets/CHUD_Aim.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Curves/CurveFloat.h"

UCAimAction::UCAimAction()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/_Project/Objects/Curve_Aim.Curve_Aim'");
}

void UCAimAction::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(150.0f);

	Aim_Hud = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD_Aim>();
	CheckNull(Aim_Hud);
	Aim_Hud->VisibleAimHidden();
}

void UCAimAction::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAimAction::On()
{
	CheckFalse(IsAvailable());
	CheckTrue(IsZooming());
	CheckNull(Aim_Hud);
	PrintLine();

	bZooming = true;
	Aim_Hud->VisibleAim();

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 15);
	SpringArm->bEnableCameraLag = false;

	Timeline.PlayFromStart(); //Ÿ�Ӷ��� ó������ ����
}

void UCAimAction::Off()
{
	CheckFalse(IsAvailable());
	CheckFalse(IsZooming());

	bZooming = false;;
	Aim_Hud->VisibleAimHidden();

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	Timeline.ReverseFromEnd(); //Ÿ�Ӷ��� ���������� ����
}

void UCAimAction::Zooming(float ZoomOut)
{
	Camera->FieldOfView = ZoomOut;
}
