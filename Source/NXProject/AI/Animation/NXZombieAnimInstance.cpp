#include "AI/Animation/NXZombieAnimInstance.h"

UNXZombieAnimInstance::UNXZombieAnimInstance()
{
}

void UNXZombieAnimInstance::NotifyCheckHit()
{
	// �̺�Ʈ ��ε�ĳ��Ʈ (OnCheckHit ���ε��� ��� �Լ� ����)
	OnCheckHit.Broadcast();
}