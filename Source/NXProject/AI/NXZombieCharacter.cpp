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
//    // �⺻ ü�� ����
//    MaxHealth = 100.f;
//    Health = MaxHealth;
//}
//
//void ANXZombieCharacter::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // �ִϸ��̼� �ν��Ͻ����� ���� ���� ��������Ʈ ���ε�
//    UNXZombieAnimInstance* AnimInstance = Cast<UNXZombieAnimInstance>(GetMesh()->GetAnimInstance());
//    if (IsValid(AnimInstance))
//    {
//        AnimInstance->OnCheckHit.AddDynamic(this, &ANXZombieCharacter::HandleCheckHit);
//    }
//
//    // AI �⺻ �̵� ����
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
//    // ���� ���� ���� (ex. ���� ���� �� ���� �¾Ҵ��� Ȯ��)
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
//    if (!bIsNowAttacking) // �ߺ� ���� ����
//    {
//        bIsNowAttacking = true;
//
//        // ���� �ִϸ��̼��� ������ ����
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
//    if (bIsDead) return 0.f; // �̹� ����� ���¶�� �������� ���� ����
//
//    float FinalDamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//    Health -= FinalDamageAmount; // ü�� ����
//
//    if (Health <= 0.f) // ü�� 0 �����̸� ��� ó��
//    {
//        Die();
//    }
//
//    return FinalDamageAmount;
//}
//
//void ANXZombieCharacter::Die()
//{
//    if (bIsDead) return; // �̹� ���� ���¶�� ���� �� ��
//    bIsDead = true;
//
//    // AI ��Ʈ�ѷ� ��Ȱ��ȭ
//    ANXZombieAIController* AIController = Cast<ANXZombieAIController>(GetController());
//    if (IsValid(AIController))
//    {
//        AIController->EndAI();
//    }
//
//    // ��� �ִϸ��̼� ���� (���� ���)
//    float DeathAnimDuration = 0.0f;
//    if (DeathMontage)
//    {
//        DeathAnimDuration = PlayAnimMontage(DeathMontage);
//    }
//
//    // ���� �ð� �Ŀ� Destroy()
//    GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ANXZombieCharacter::DestroyCharacter, DeathAnimDuration + 1.0f, false);
//}
//
//void ANXZombieCharacter::DestroyCharacter()
//{
//    Destroy();
//}
