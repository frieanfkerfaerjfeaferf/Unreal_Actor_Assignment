#include "MyActor.h"

// 기본 생성자
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// 게임 시작 시 실행되는 로직
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// [조건 1] 시작 위치 고정 (0, 50, 0)
	FVector CurrentLocation = FVector(0.0f, 50.0f, 0.0f);
	SetActorLocation(CurrentLocation);

	// 변수 초기화
	EventCount = 0;
	TotalDistance = 0.0f;
	MaxDistance = 0.0f;

	// [조건 2] 랜덤 반복 실행 (10회)
	for (int32 i = 1; i <= 10; i++)
	{
		// 이전 위치 저장 (거리 계산용)
		FVector PreviousLocation = CurrentLocation;

		// 랜덤 이동 좌표 생성 (X, Y축으로 -100 ~ 100 사이 랜덤 이동)
		float RandX = FMath::RandRange(-100.0f, 100.0f);
		float RandY = FMath::RandRange(-100.0f, 100.0f);

		// 새로운 좌표 계산
		FVector NextLocation = CurrentLocation + FVector(RandX, RandY, 0.0f);

		// [조건 3] 이동 거리 계산 로직 (FVector::Dist 사용)
		float StepDistance = FVector::Dist(PreviousLocation, NextLocation);

		// 데이터 분석: 총 거리 누적 및 최대 거리 갱신
		TotalDistance += StepDistance;
		if (StepDistance > MaxDistance)
		{
			MaxDistance = StepDistance;
		}

		// 현재 위치 업데이트
		CurrentLocation = NextLocation;

		// [조건 4] 실시간 좌표 및 회차 로그 출력 (AddOnScreenDebugMessage)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan,
			FString::Printf(TEXT("Step %d - Location: %s"), i, *CurrentLocation.ToString()));

		// [조건 5] 50% 확률 이벤트 시스템 실행
		TriggerEvent();
	}

	// [조건 6] 최종 결과 리포트 출력
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("=============================="));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
		FString::Printf(TEXT("Final: Total Distance Travelled: %.2f"), TotalDistance));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange,
		FString::Printf(TEXT("Analysis: Max Single Move Distance: %.2f"), MaxDistance));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red,
		FString::Printf(TEXT("Final: Total Events Occurred: %d"), EventCount));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("========= MISSION COMPLETE ========"));
}

// 50% 확률 이벤트 처리 함수
void AMyActor::TriggerEvent()
{
	// FMath::FRand()는 0.0 ~ 1.0 사이의 랜덤 숫자를 반환 (0.5 이하면 50% 확률)
	if (FMath::FRand() <= 0.5f)
	{
		EventCount++;
		// 이벤트 발생 시 시각적 알림 로그
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT(">> EVENT! [Special Action Triggered] <<"));
	}
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
