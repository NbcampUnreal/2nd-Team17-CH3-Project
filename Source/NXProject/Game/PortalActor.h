#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h" // 파티클 시스템 컴포넌트를 사용하기 위한 헤더
#include "PortalActor.generated.h"

UCLASS()
class NXPROJECT_API APortalActor : public AActor
{
    GENERATED_BODY()

public:
    APortalActor(); // 생성자

protected:
    virtual void BeginPlay() override; // 게임 시작 시 호출되는 함수


public:
    virtual void Tick(float DeltaTime) override; // 매 프레임 호출되는 함수

    // 포탈과 다른 액터가 겹칠 때 호출되는 함수
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 포탈에 닿았을 때 이동할 목적지 위치 (에디터에서 설정 가능)
    UPROPERTY(EditAnywhere, Category = "Portal")
    FVector DestinationLocation;



private:
    // 포탈의 트리거 영역을 정의하는 박스 컴포넌트
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;


    UPROPERTY(VisibleAnywhere, Category = "Effects")
    class UParticleSystemComponent* PortalEffect;//이펙트
};