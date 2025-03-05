#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NXGameState.generated.h"

class APortalActor; // ���� ����

UCLASS()
class NXPROJECT_API ANXGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ANXGameState();

    virtual void BeginPlay() override;

    // ������ �������� �Լ�
    int32 GetScore() const;

    // ������ �߰��ϴ� �Լ�
    void AddScore(int32 Amount);

    // ��Ż ����Ʈ�� Ȱ��ȭ�ϴ� �Լ�
    void ActivatePortalEffect();

    // PortalActor�� �ʱ�ȭ�ϴ� �Լ�
    void InitializePortalActor(APortalActor* Portal);

    UFUNCTION(BlueprintCallable)
    void ShowWinGameUI();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> WinUserWidgetClass;


    //���
    void UpdateHUD();

private:
    int32 Score; // ���� ����
    int32 RequiredScoreToActivatePortal; // ��Ż Ȱ��ȭ�� �ʿ��� ����

    UPROPERTY()
    APortalActor* PortalActor; // ��Ż ���� ����
};