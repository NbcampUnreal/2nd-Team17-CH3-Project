#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

UCLASS()
class NXPROJECT_API APortalActor : public AActor
{
    GENERATED_BODY()

public:
    // ������
    APortalActor();

protected:
    // ���� ���� �� ȣ��Ǵ� �Լ�
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
    USoundBase* PickupSound; // ����

public:
    // �� ������ ȣ��Ǵ� �Լ�
    virtual void Tick(float DeltaTime) override;

    // ��Ż ����Ʈ�� ��� Ȱ��ȭ�ϴ� �Լ�
    void ActivateEffect();

    // ��Ż Ȱ��ȭ ���¸� �����ϴ� �Լ�
    void SetPortalActive(bool bActive);

    // ��Ż Ȱ��ȭ ���¸� Ȯ���ϴ� �Լ�
    bool IsPortalActive() const;

private:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
    class UParticleSystemComponent* PortalEffect;

    UPROPERTY(EditAnywhere, Category = "Portal")
    FVector DestinationLocation; // �̵��� ��ġ

    // ��Ż Ȱ��ȭ ����
    UPROPERTY(VisibleAnywhere, Category = "Portal")
    bool bIsPortalActive;

    // ������ �̺�Ʈ �Լ�
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};