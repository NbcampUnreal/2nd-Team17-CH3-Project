#include "NXGrenadeWeapon.h"
#include "Kismet/GameplayStatics.h" //게임 유틸리티 기능

ANXGrenadeWeapon::ANXGrenadeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrenadeMesh"));
	RootComponent = GrenadeMesh; //물리적인 상호작용

	
	GrenadeMesh->SetSimulatePhysics(true); //물리설정
}

void ANXGrenadeWeapon::BeginPlay()
{
	Super::BeginPlay();

	// FuseTime 후에 폭발
	FuseTime = 7.0f; // 7초 후에 폭발

	FTimerHandle TimerHandle; //타이머를 관리하기 위한 핸들
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ANXGrenadeWeapon::Explode,
		FuseTime,
		false); 
}

void ANXGrenadeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANXGrenadeWeapon::Initialize(float Damage, float NewFuseTime) //수류탄의 데미지와 폭발까지의 시간
{
	DamageAmount = Damage;
	this->FuseTime = NewFuseTime;
}

void ANXGrenadeWeapon::Explode() //폭발할 때 함수
{
	// 폭발 효과 및 데미지 처리
	UGameplayStatics::ApplyRadialDamage( //반경 내의 데미지 주는 함수
		GetWorld(),
		DamageAmount,
		GetActorLocation(),
		300.f, //반경은 300
		nullptr,
		TArray<AActor*>(),
		this,
		nullptr,
		true);
	Destroy(); //폭발 후엔 사라짐
}