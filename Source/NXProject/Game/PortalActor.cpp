#include "Game/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Player/NXPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NXGameState.h"

// 생성자: 액터가 생성될 때 호출됨
APortalActor::APortalActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // 트리거 박스 컴포넌트 생성 및 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin); // 오버랩 이벤트 추가

    // 파티클 시스템 컴포넌트 초기화
    PortalEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalEffect"));
    PortalEffect->SetupAttachment(RootComponent);

    // 초기화: 포탈은 비활성화 상태로 시작
    bIsPortalActive = false;
}

// 게임 시작 시 호출되는 함수
void APortalActor::BeginPlay()
{
    Super::BeginPlay();
    // GameState 가져오기
    ANXGameState* GameState = Cast<ANXGameState>(GetWorld()->GetGameState());
    if (GameState)
    {
        GameState->InitializePortalActor(this); // PortalActor 초기화
    }

    if (PortalEffect)
    {
        PortalEffect->Deactivate(); // 시작 시 이펙트 비활성화
    }

  

}


// 매 프레임 호출되는 함수
void APortalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 포탈 이펙트를 즉시 활성화하는 함수
void APortalActor::ActivateEffect()
{
    if (PortalEffect)
    {
        PortalEffect->Activate(); // 이펙트 활성화
        bIsPortalActive = true; // 포탈 활성화 상태로 변경
    }
    // 사운드 재생
    if (PickupSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            PickupSound,
            GetActorLocation()
        );
    }
}
// 포탈 활성화 상태를 설정하는 함수
void APortalActor::SetPortalActive(bool bActive)
{
    bIsPortalActive = bActive;
    if (bActive)
    {
        ActivateEffect(); // 포탈 활성화 시 이펙트 재생
    }
    else
    {
        if (PortalEffect)
        {
            PortalEffect->Deactivate(); // 포탈 비활성화 시 이펙트 중지
        }
    }
}

// 포탈 활성화 상태를 확인하는 함수
bool APortalActor::IsPortalActive() const
{
    return bIsPortalActive;
}

// 오버랩 이벤트 함수
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
        // GameState 가져오기
        ANXGameState* GameState = Cast<ANXGameState>(GetWorld()->GetGameState());
        if (GameState && bIsPortalActive && GameState->GetScore() >= 2)
        {
            // 캐릭터를 지정된 목적지 위치로 이동
            Character->SetActorLocation(DestinationLocation); // 포탈 이동
        }
    }

    
}