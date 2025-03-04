#include "NXBaseItem.h"
#include "Components/SphereComponent.h"
#include "Player/NXPlayerCharacter.h"
#include "Engine/Engine.h" // GEngine

ANXBaseItem::ANXBaseItem()
{
    PrimaryActorTick.bCanEverTick = false;

    // 루트 컴포넌트 생성 및 설정
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    // 충돌 컴포넌트 생성 및 설정
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    // 겹침만 감지하는 프로파일 설정
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    // 루트 컴포넌트로 설정
    Collision->SetupAttachment(Scene);

    // 스태틱 메시 컴포넌트 생성 및 설정
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

    
}
void ANXBaseItem::BeginPlay()
{
    Super::BeginPlay();

    // Overlap 이벤트 바인딩
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ANXBaseItem::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ANXBaseItem::OnItemEndOverlap);

}

void ANXBaseItem::OnItemOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{

    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        ActivateItem(OtherActor);
    }
}

void ANXBaseItem::OnItemEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

void ANXBaseItem::ActivateItem(AActor* Activator)
{
}

FName ANXBaseItem::GetItemType() const
{
    return ItemType;
}

void ANXBaseItem::DestroyItem()
{
    Destroy();
}