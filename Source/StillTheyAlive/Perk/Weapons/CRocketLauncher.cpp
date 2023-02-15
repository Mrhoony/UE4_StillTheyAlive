#include "CRocketLauncher.h"
#include "Global.h"
#include "Characters/Players/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACRocketLauncher::ACRocketLauncher()
{
	WeaponType = EWeaponType::RocketLauncher;
}

void ACRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}

void ACRocketLauncher::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACRocketLauncher::TechAction()
{
	CheckNull(OwnerCharacter);
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(player);
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(player);

	CheckNull(springArm);
	CheckNull(camera);

	if (Zoomin == false)
	{
		springArm->TargetArmLength = 200.0f;
		springArm->SocketOffset = FVector(0, 0, 0);
		springArm->CameraLagSpeed = 10.0f;
		camera->SetFieldOfView(90.0f);
		Zoomin = true;
	}
	else
	{
		springArm->TargetArmLength = 100.0f;
		springArm->SocketOffset = FVector(0, 30, 15);
		springArm->CameraLagSpeed = 100.0f;
		camera->SetFieldOfView(45.0f);
		Zoomin = false;
	}

}

