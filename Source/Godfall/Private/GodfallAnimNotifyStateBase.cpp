// Fill out your copyright notice in the Description page of Project Settings.


#include "GodfallAnimNotifyStateBase.h"

UGodfallAnimNotifyStateBase::UGodfallAnimNotifyStateBase()
{
	bIsNativeBranchingPoint = true;
}

void UGodfallAnimNotifyStateBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UAnimInstance* animInstance = MeshComp->GetAnimInstance();
	if (animInstance)
	{
		// GetFunctionName이 반환한 함수명을 가진 함수를 탐색합니다.
		UFunction* function = animInstance->FindFunction(GetFunctionName());
		if (function && function->NumParms == 3)
		{
			// 탐색한 함수에 바인드합니다.
			FOnAnimNotifyStateEvent Delegate;
			Delegate.BindUFunction(animInstance, GetFunctionName());
			// 바인드한 함수를 호출하며, 이벤트 데이터를 전달합니다.
			FAnimNotifiyStateData data;
			data.MeshComp = MeshComp;
			data.Animation = Animation;
			data.EventReference = &EventReference;
			data.TotalDuration = TotalDuration;
			Delegate.Execute(EAnimNotifyStateEvent::Begin, this, data);
		}
	}
}

void UGodfallAnimNotifyStateBase::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	UAnimInstance* animInstance = MeshComp->GetAnimInstance();
	if (animInstance)
	{
		UFunction* function = animInstance->FindFunction(GetFunctionName());
		if (function && function->NumParms == 3)
		{
			FOnAnimNotifyStateEvent Delegate;
			Delegate.BindUFunction(animInstance, GetFunctionName());

			FAnimNotifiyStateData data;
			data.MeshComp = MeshComp;
			data.Animation = Animation;
			data.EventReference = &EventReference;
			data.FrameDeltaTime = FrameDeltaTime;
			Delegate.Execute(EAnimNotifyStateEvent::Tick, this, data);
		}
	}
}

void UGodfallAnimNotifyStateBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UAnimInstance* animInstance = MeshComp->GetAnimInstance();
	if (animInstance)
	{
		UFunction* function = animInstance->FindFunction(GetFunctionName());
		if (function && function->NumParms == 3)
		{
			FOnAnimNotifyStateEvent Delegate;
			Delegate.BindUFunction(animInstance, GetFunctionName());

			FAnimNotifiyStateData data;
			data.MeshComp = MeshComp;
			data.Animation = Animation;
			data.EventReference = &EventReference;
			Delegate.Execute(EAnimNotifyStateEvent::End, this, data);
		}
	}
}
