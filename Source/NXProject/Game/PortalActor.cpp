#include "Game/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Player/NXPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NXGameState.h"

// ������: ���Ͱ� ������ �� ȣ���
APortalActor::APortalActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Ʈ���� �ڽ� ������Ʈ ���� �� ����
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin); // ������ �̺�Ʈ �߰�

    // ��ƼŬ �ý��� ������Ʈ �ʱ�ȭ
    PortalEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(RootComponent);

    // �ʱ�ȭ: ��Ż�� ��Ȱ��ȭ ���·� ����
    bIsPortalActive = false;
}

// ���� ���� �� ȣ��Ǵ� �Լ�
void APortalActor::BeginPlay()
{
    Super::BeginPlay();
    // GameState ��������
    ANXGameState* GameState = Cast<ANXGameState>(GetWorld()->GetGameState());
    if (GameState)
    {
        GameState->InitializePortalActor(this); // PortalActor �ʱ�ȭ
    }

    if (PortalEffect)
    {
        PortalEffect->Deactivate(); // ���� �� ����Ʈ ��Ȱ��ȭ
    }

  

}


// �� ������ ȣ��Ǵ� �Լ�
void APortalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// ��Ż ����Ʈ�� ��� Ȱ��ȭ�ϴ� �Լ�
void APortalActor::ActivateEffect()
{
    if (PortalEffect)
    {
        PortalEffect->Activate(); // ����Ʈ Ȱ��ȭ
        bIsPortalActive = true; // ��Ż Ȱ��ȭ ���·� ����
    }
    // ���� ���
    if (PickupSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            PickupSound,
            GetActorLocation()
        );
    }
}
// ��Ż Ȱ��ȭ ���¸� �����ϴ� �Լ�
void APortalActor::SetPortalActive(bool bActive)
{
    bIsPortalActive = bActive;
    if (bActive)
    {
        ActivateEffect(); // ��Ż Ȱ��ȭ �� ����Ʈ ���
    }
    else
    {
        if (PortalEffect)
        {
            PortalEffect->Deactivate(); // ��Ż ��Ȱ��ȭ �� ����Ʈ ����
        }
    }
}

// ��Ż Ȱ��ȭ ���¸� Ȯ���ϴ� �Լ�
bool APortalActor::IsPortalActive() const
{
    return bIsPortalActive;
}

// ������ �̺�Ʈ �Լ�
void APortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ANXPlayerCharacter* Character = Cast<ANXPlayerCharacter>(OtherActor);
    if (Character)
    {
        // GameState ��������
        ANXGameState* GameState = Cast<ANXGameState>(GetWorld()->GetGameState());
        if (GameState && bIsPortalActive && GameState->GetScore() >= 2)
        {
            // ĳ���͸� ������ ������ ��ġ�� �̵�
            Character->SetActorLocation(DestinationLocation); // ��Ż �̵�
        }
    }

    
}