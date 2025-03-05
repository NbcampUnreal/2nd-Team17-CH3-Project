#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

UCLASS()
class NXPROJECT_API APortalActor : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    APortalActor();

protected:
    // 게임 시작 시 호출되는 함수
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
    USoundBase* PickupSound; // 사운드

public:
    // 매 프레임 호출되는 함수
    virtual void Tick(float DeltaTime) override;

    // 포탈 이펙트를 즉시 활성화하는 함수
    void ActivateEffect();

    // 포탈 활성화 상태를 설정하는 함수
    void SetPortalActive(bool bActive);

    // 포탈 활성화 상태를 확인하는 함수
    bool IsPortalActive() const;

private:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
    class UParticleSystemComponent* PortalEffect;

    UPROPERTY(EditAnywhere, Category = "Portal")
    FVector DestinationLocation; // 이동할 위치

    // 포탈 활성화 상태
    UPROPERTY(VisibleAnywhere, Category = "Portal")
    bool bIsPortalActive;

    // 오버랩 이벤트 함수
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};