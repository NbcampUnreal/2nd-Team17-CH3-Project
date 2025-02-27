#include "Game/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Player/NXPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h" // 파티클 시스템 컴포넌트를 사용하기 위한 헤더

// 생성자: 액터가 생성될 때 호출됨
APortalActor::APortalActor()
{
    // 액터가 매 프레임 Tick 함수를 호출할 수 있도록 설정
    PrimaryActorTick.bCanEverTick = true;

    // 트리거 박스 컴포넌트 생성 및 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox; // 트리거 박스를 루트 컴포넌트로 설정
  
    TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // 충돌 프로필 설정
    // 트리거 박스에 다른 액터가 겹칠 때 호출될 함수 바인딩
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);

    // 파티클 시스템 컴포넌트 초기화
    PortalEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(RootComponent); // 루트 컴포넌트에 부착
}

// 게임 시작 시 호출되는 함수
void APortalActor::BeginPlay()
{
    Super::BeginPlay();
}

// 매 프레임 호출되는 함수
void APortalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 트리거 박스에 다른 액터가 겹칠 때 호출되는 함수
void APortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    // 겹친 액터가 플레이어 캐릭터인지 확인
    ANXPlayerCharacter* Character = Cast<ANXPlayerCharacter>(OtherActor);
    if (Character)
    {
        // 플레이어 캐릭터를 지정된 목적지 위치로 이동
        Character->SetActorLocation(DestinationLocation);
    }
}

