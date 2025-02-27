//#include "AI/NXZombieCharacter.h"
//#include "AI/NXZombieAIController.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "AI/Animation/NXZombieAnimInstance.h"
//#include "GameFramework/Actor.h"
//#include "Engine/DamageEvents.h"
//
//ANXZombieCharacter::ANXZombieCharacter()
//    : bIsNowAttacking(false), bIsDead(false)
//{
//    PrimaryActorTick.bCanEverTick = false;
//
//    // 기본 체력 설정
//    MaxHealth = 100.f;
//    Health = MaxHealth;
//}
//
//void ANXZombieCharacter::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // 애니메이션 인스턴스에서 공격 판정 델리게이트 바인딩
//    UNXZombieAnimInstance* AnimInstance = Cast<UNXZombieAnimInstance>(GetMesh()->GetAnimInstance());
//    if (IsValid(AnimInstance))
//    {
//        AnimInstance->OnCheckHit.AddDynamic(this, &ANXZombieCharacter::HandleCheckHit);
//    }
//
//    // AI 기본 이동 설정
//    if (!IsPlayerControlled())
//    {
//        bUseControllerRotationYaw = false;
//        GetCharacterMovement()->bOrientRotationToMovement = false;
//        GetCharacterMovement()->bUseControllerDesiredRotation = true;
//        GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
//        GetCharacterMovement()->MaxWalkSpeed = 300.f;
//    }
//}
//
//void ANXZombieCharacter::HandleCheckHit()
//{
//    // 공격 판정 로직 (ex. 공격 범위 내 적이 맞았는지 확인)
//    UKismetSystemLibrary::PrintString(this, TEXT("Attack hit detection executed!"));
//}
//
//void ANXZombieCharacter::StartAttack()
//{
//    BeginAttack();
//}
//
//void ANXZombieCharacter::BeginAttack()
//{
//    if (!bIsNowAttacking) // 중복 공격 방지
//    {
//        bIsNowAttacking = true;
//
//        // 공격 애니메이션이 있으면 실행
//        if (AttackMontage)
//        {
//            PlayAnimMontage(AttackMontage);
//        }
//    }
//}
//
//void ANXZombieCharacter::EndAttack(UAnimMontage* InMontage, bool bInterrupted)
//{
//    bIsNowAttacking = false;
//    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
//}
//
//float ANXZombieCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
//    AController* EventInstigator, AActor* DamageCauser)
//{
//    if (bIsDead) return 0.f; // 이미 사망한 상태라면 데미지를 받지 않음
//
//    float FinalDamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//    Health -= FinalDamageAmount; // 체력 감소
//
//    if (Health <= 0.f) // 체력 0 이하이면 사망 처리
//    {
//        Die();
//    }
//
//    return FinalDamageAmount;
//}
//
//void ANXZombieCharacter::Die()
//{
//    if (bIsDead) return; // 이미 죽은 상태라면 실행 안 함
//    bIsDead = true;
//
//    // AI 컨트롤러 비활성화
//    ANXZombieAIController* AIController = Cast<ANXZombieAIController>(GetController());
//    if (IsValid(AIController))
//    {
//        AIController->EndAI();
//    }
//
//    // 사망 애니메이션 실행 (있을 경우)
//    float DeathAnimDuration = 0.0f;
//    if (DeathMontage)
//    {
//        DeathAnimDuration = PlayAnimMontage(DeathMontage);
//    }
//
//    // 일정 시간 후에 Destroy()
//    GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ANXZombieCharacter::DestroyCharacter, DeathAnimDuration + 1.0f, false);
//}
//
//void ANXZombieCharacter::DestroyCharacter()
//{
//    Destroy();
//}
