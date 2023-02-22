#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAimAction.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCAimAction : public UObject
{
	GENERATED_BODY()
	
public:
	UCAimAction();

	void BeginPlay(class ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

	FORCEINLINE bool IsAvailable() { return SpringArm != nullptr && Camera != nullptr; }
	FORCEINLINE bool IsZooming() { return bZooming; }

	void On();
	void Off();

private:
	UFUNCTION()
		void Zooming(float ZoomOut);

private:
	//OwnerCharacter와 Owner의 Component를 담을 변수
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bZooming; //현재 Zoom상태확인

private:
	class UCurveFloat* Curve; //타임라인 파라미터에 쓰일 커브변수
	FTimeline Timeline; //타임라인 변수
	FOnTimelineFloat TimelineFloat;

	class ACHUD_Aim* Aim_Hud; //에임을 그리기 위한 위젯
};
