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
	//OwnerCharacter�� Owner�� Component�� ���� ����
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bZooming; //���� Zoom����Ȯ��

private:
	class UCurveFloat* Curve; //Ÿ�Ӷ��� �Ķ���Ϳ� ���� Ŀ�꺯��
	FTimeline Timeline; //Ÿ�Ӷ��� ����
	FOnTimelineFloat TimelineFloat;

	class ACHUD_Aim* Aim_Hud; //������ �׸��� ���� ����
};
