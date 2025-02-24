#include "AI/Animation/NXZombieAnimInstance.h"

UNXZombieAnimInstance::UNXZombieAnimInstance()
{
}

void UNXZombieAnimInstance::NotifyCheckHit()
{
    OnCheckHit.Broadcast();
}
