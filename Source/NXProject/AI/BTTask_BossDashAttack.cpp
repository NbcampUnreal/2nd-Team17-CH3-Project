// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_BossDashAttack.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "Player/NXPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossDashAttack::UBTTask_BossDashAttack()
{
	NodeName = "BossDashAttack";
}

EBTNodeResult::Type UBTTask_BossDashAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return EBTNodeResult::Failed;

	ANXBossZombie* AICharacter = Cast< ANXBossZombie>(AIController->GetPawn());
	if (!AICharacter)return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return EBTNodeResult::Failed;

	AICharacter->GetCharacterMovement()->StopMovementImmediately();

	FVector PlayerLocation = Player->GetActorLocation();
	FVector MyLocation = AICharacter->GetActorLocation();
	
	float DashDistance = 4500.0f;//�Ÿ�
	
	FVector DashDirection = (PlayerLocation - MyLocation).GetSafeNormal();
	FVector TargetLocation = PlayerLocation + DashDirection * DashDistance;


	FVector DirectionToTarget = (TargetLocation - MyLocation).GetSafeNormal();
	float DashSpeed = 3000.0f;//�ӵ�

	FVector DashVelocity = DirectionToTarget * DashSpeed;
	DashVelocity.Z = 100.0f;
	
	AICharacter->bIsDashAttacking = true;
	
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();
	AICharacter->SetActorRotation(LookAtRotation);

	if (USkeletalMeshComponent* MeshComponent = AICharacter->GetMesh())
	{
		if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
		{
			AnimInstance->Montage_Play(AICharacter->BossDashAnimation, 1.f);
		}
	}

	FTimerHandle DashDelayTimer;
	AICharacter->GetWorldTimerManager().SetTimer(
		DashDelayTimer,
		FTimerDelegate::CreateLambda([AICharacter, DashVelocity]()
			{
				if (AICharacter)
				{
					AICharacter->DashAttack();
					AICharacter->LaunchCharacter(DashVelocity,true,true);
				}
			}),
		0.7f,//�뽬 �غ�ð�
		false
	);

	AIController->GetBlackboardComponent()->SetValueAsBool("CanDashAttack", false);

	FTimerHandle CoolDownTimer;
	AICharacter->GetWorldTimerManager().SetTimer(
		CoolDownTimer,
		FTimerDelegate::CreateLambda([AIController]()
			{
				if (AIController)
				{
					AIController->GetBlackboardComponent()->SetValueAsBool("CanDashAttack", true);
				}
			}),
		4.0f,//�뽬 ��Ÿ��
		false
	);

	//���� ���� ����
	return EBTNodeResult::Succeeded;
}
