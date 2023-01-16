// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "GodfallAnimNotifyStateBase.h"
#include "Animation/AnimInstance.h"
#include "AnimNotifyState_Custom.h"
#include "GodfallAnimInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCustomAnimNotifyState, EAnimNotifyStateEvent, eEvent, const FAnimNotifiyStateData&, data, const FName&, notifyStateName, const FCustomNotifyStateVariable&, variables);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimNotifyFootstep);

/* ��Ÿ�� ���� Ʈ�������� �����ϴ� Ÿ���Դϴ�.
���� ���ǿ��� ��� �ϳ��� ���������� Ʈ�������� �����ϳ�,
�� ���ǿ��� ���� ���������� Ʈ�������� �Ұ����մϴ�.
�ʿ��ϴٸ� ���� ���� ��ȯ�� ����ϼ���. */
struct FMontageSectionTransition
{
	UAnimMontage* Montage = nullptr;
	FName From = NAME_None;
	FName To = NAME_None;

	/* ���ǰ� ��ȯ�� ���Ǵ� ���� �ð��Դϴ�.
	�� ���� 0���� �۴ٸ� ��Ÿ���� Blend In �ð��� ���˴ϴ�. */
	float BlendInTime = -1.0f;

	/* Ʈ������ ���п� ���Ǵ� �̸��Դϴ�.
	������� �ʾƵ� �������ϴ�. */
	FName Name = NAME_None;

	bool IsValid() const;
	bool Equal(const FMontageSectionTransition& other) const;
	bool operator == (const FMontageSectionTransition& rhs) const { return Equal(rhs); }
	bool operator != (const FMontageSectionTransition& rhs) const { return !Equal(rhs); }
};

/**
 * 
 */
UCLASS()
class GODFALL_API UGodfallAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UGodfallAnimInstanceBase();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeThreadSafeUpdateAnimation(float deltaTime) override;
	
public:
	FName GetCurrentStateName(FString stateMachineName) const;
	float GetTimeFraction(FString stateMachineName, FString stateName) const;
	float GetBlendWeight(FString stateMachineName) const;
	float GetBlendWeight(FString stateMachineName, FString stateName) const;

	float Montage_GetTimeFraction(const UAnimMontage* montage) const;
	float Montage_GetTimeFraction(const UAnimMontage* montage, const FName& sectionName) const;
	void Montage_SetTimeFraction(const UAnimMontage* montage, float timeFraction);
	void Montage_SetTimeFraction(const UAnimMontage* montage, const FName& sectionName, float timeFraction);
	bool Montage_IsPlayingSection(const UAnimMontage* montage, const FName& sectionName) const;

	UFUNCTION(BlueprintPure, Meta = (BlueprintThreadSafe))
	bool Montage_IsPlaying_Threadsafe(const UAnimMontage* montage) const;

	UFUNCTION(BlueprintPure, Meta = (BlueprintThreadSafe))
	bool IsAnyMontagePlaying_Threadsafe() const { return (mPlayingMontages.Num() > 0); }

	float Montage_PlayAtSection(UAnimMontage* MontageToPlay, FName section, float blendInTime = -1.f, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, bool bStopAllMontages = true);
	float Montage_PlayAtSection(UAnimMontage* MontageToPlay, int32 section, float blendInTime = -1.f, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, bool bStopAllMontages = true);

	void AddManualMontageSectionTransition(const FMontageSectionTransition& transition);
	void AddManualMontageSectionTransition(UAnimMontage* Montage, FName From, FName To, float BlendInTime = -1.0f, FName Name = NAME_None);
	bool RemoveManualMontageSection(const FMontageSectionTransition* transition);
	const FMontageSectionTransition* FindManualMontageSectionTransitionByName(UAnimMontage* Montage, FName Name) const;
	const FMontageSectionTransition* FindManualMontageSectionTransitionByFrom(UAnimMontage* Montage, FName From) const;
	const FMontageSectionTransition* Montage_ManualSectionTransit(UAnimMontage* Montage);
	const FMontageSectionTransition* Montage_PlayOrManualSectionTransit(UAnimMontage* Montage, FName section = NAME_None, float blendInTime = -1.f, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, bool bStopAllMontages = true, float* result = nullptr);

public:
	bool IsExitable() const { return mExitable > 0; }
	bool IsTransitable() const { return mTransitable > 0; }

protected:
	UFUNCTION()
	virtual void AnimNotifyState_Custom(EAnimNotifyStateEvent eEvent, const UGodfallAnimNotifyStateBase* animNotifyState, const FAnimNotifiyStateData& data);

	virtual void OnCustomAnimNotifyStateCallback(EAnimNotifyStateEvent eEvent, const FAnimNotifiyStateData& data, const FName& notifyStateName, const FCustomNotifyStateVariable& variables) {}

	UFUNCTION()
	virtual void AnimNotifyState_Exitable(EAnimNotifyStateEvent eEvent, const UGodfallAnimNotifyStateBase* animNotifyState, const FAnimNotifiyStateData& data);
	
	UFUNCTION()
	virtual void AnimNotifyState_Transitable(EAnimNotifyStateEvent eEvent, const UGodfallAnimNotifyStateBase* animNotifyState, const FAnimNotifiyStateData& data);

	UFUNCTION()
	virtual void OnMontageStartedCallback(UAnimMontage* montage);

	UFUNCTION()
	virtual void OnMontageEndedCallback(UAnimMontage* montage, bool interrupted);

	UFUNCTION()
	virtual void AnimNotify_FootStep();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true), DisplayName = "Exitable")
	int32 mExitable = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true), DisplayName = "Transitable")
	int32 mTransitable = 0;

	TArray<UAnimMontage*> mPlayingMontages;

	/* TMap<���� ��ȯ�� �� ��Ÿ��, TMap<���� ����, ��Ÿ�� ���� Ʈ������>> */
	TMap<UAnimMontage*, TMap<FName, FMontageSectionTransition>> mManualMontageSectionTransitions;

public:
	FOnCustomAnimNotifyState OnCustomAnimNotifyState;
	FOnAnimNotifyFootstep OnAnimNotifyFootstep;
};
