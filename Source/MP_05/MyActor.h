#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MP_05_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	AMyActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// --- 과제용 추가 변수 및 함수 ---

	// 50% 확률 이벤트를 처리할 함수
	void TriggerEvent();

	// 통계 데이터를 저장할 그릇들
	int32 EventCount = 0;       // 이벤트 발생 횟수
	float TotalDistance = 0.0f;  // 총 이동 거리 합계
	float MaxDistance = 0.0f;    // 단일 최대 이동 거리 (데이터 분석 추가 기능)
};
