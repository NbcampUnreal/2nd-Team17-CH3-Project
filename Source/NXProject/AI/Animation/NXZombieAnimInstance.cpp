#include "AI/Animation/NXZombieAnimInstance.h"

UNXZombieAnimInstance::UNXZombieAnimInstance()
{
}

void UNXZombieAnimInstance::NotifyCheckHit()
{
	// 이벤트 브로드캐스트 (OnCheckHit 바인딩된 모든 함수 실행)
	OnCheckHit.Broadcast();
}