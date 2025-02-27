#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h" // ��ƼŬ �ý��� ������Ʈ�� ����ϱ� ���� ���
#include "PortalActor.generated.h"

UCLASS()
class NXPROJECT_API APortalActor : public AActor
{
    GENERATED_BODY()

public:
    APortalActor(); // ������

protected:
    virtual void BeginPlay() override; // ���� ���� �� ȣ��Ǵ� �Լ�


public:
    virtual void Tick(float DeltaTime) override; // �� ������ ȣ��Ǵ� �Լ�

    // ��Ż�� �ٸ� ���Ͱ� ��ĥ �� ȣ��Ǵ� �Լ�
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // ��Ż�� ����� �� �̵��� ������ ��ġ (�����Ϳ��� ���� ����)
    UPROPERTY(EditAnywhere, Category = "Portal")
    FVector DestinationLocation;



private:
    // ��Ż�� Ʈ���� ������ �����ϴ� �ڽ� ������Ʈ
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;


    UPROPERTY(VisibleAnywhere, Category = "Effects")
    class UParticleSystemComponent* PortalEffect;//����Ʈ
};