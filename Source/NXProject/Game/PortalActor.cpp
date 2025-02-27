#include "Game/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Player/NXPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h" // ��ƼŬ �ý��� ������Ʈ�� ����ϱ� ���� ���

// ������: ���Ͱ� ������ �� ȣ���
APortalActor::APortalActor()
{
    // ���Ͱ� �� ������ Tick �Լ��� ȣ���� �� �ֵ��� ����
    PrimaryActorTick.bCanEverTick = true;

    // Ʈ���� �ڽ� ������Ʈ ���� �� ����
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox; // Ʈ���� �ڽ��� ��Ʈ ������Ʈ�� ����
  
    TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // �浹 ������ ����
    // Ʈ���� �ڽ��� �ٸ� ���Ͱ� ��ĥ �� ȣ��� �Լ� ���ε�
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);

    // ��ƼŬ �ý��� ������Ʈ �ʱ�ȭ
    PortalEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(RootComponent); // ��Ʈ ������Ʈ�� ����
}

// ���� ���� �� ȣ��Ǵ� �Լ�
void APortalActor::BeginPlay()
{
    Super::BeginPlay();
}

// �� ������ ȣ��Ǵ� �Լ�
void APortalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Ʈ���� �ڽ��� �ٸ� ���Ͱ� ��ĥ �� ȣ��Ǵ� �Լ�
void APortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    // ��ģ ���Ͱ� �÷��̾� ĳ�������� Ȯ��
    ANXPlayerCharacter* Character = Cast<ANXPlayerCharacter>(OtherActor);
    if (Character)
    {
        // �÷��̾� ĳ���͸� ������ ������ ��ġ�� �̵�
        Character->SetActorLocation(DestinationLocation);
    }
}

