// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GodfallBTServiceBase.h"
#include "BTService_FindLocation.generated.h"

/**
 * 
 */
UCLASS()
class GODFALL_API UBTService_FindLocation : public UGodfallBTServiceBase
{
	GENERATED_BODY()

public:
	UBTService_FindLocation();

protected:
	// �� ���񽺷� ������ �� ȣ��˴ϴ�.
	virtual void OnSearchStartEvent(FBehaviorTreeSearchData& SearchData) override;

	// ���񽺰� ���۵� �� ȣ��˴ϴ�.
	virtual void OnBecomeRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// ����� �ߴܵ� �� ȣ��˴ϴ�.
	virtual void OnCeaseRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Interval ���� ȣ��˴ϴ�.
	virtual void TickNodeEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AGodfallEnemyBase* GetPivotEnemy(UBehaviorTreeComponent& OwnerComp) const;
	bool FindLocation(UBehaviorTreeComponent& OwnerComp, FVector& location, FName& directionName) const;
	bool Sweep(class AGodfallEnemyBase* enemy, const FVector& direction, float distance, FName tagName, FName profileName, float& hitDistance) const;

	void SetTargetLocationKey(UBehaviorTreeComponent& OwnerComp);

private:
	UPROPERTY(EditAnywhere, DisplayName = "Pivot Enemy Key")
	FBlackboardKeySelector mPivotEnemyKey;

	UPROPERTY(EditAnywhere, DisplayName = "Target Location Key")
	FBlackboardKeySelector mTargetLocationKey;

	/* ����� �����ϸ� NAME_None
	�� �̿ܿ��� Forward, Backward, Left, Right�� ����� �����ϴ�. */

	UPROPERTY(EditAnywhere, DisplayName = "Direction Key")
	FBlackboardKeySelector mDirectionKey;

	UPROPERTY(EditAnywhere, DisplayName = "Min Distance", Meta = (ClampMin = 0.0f))
	float mMinDistance = 400.0f;

	UPROPERTY(EditAnywhere, DisplayName = "Max Distance", Meta = (ClampMin = 0.0f))
	float mMaxDistance = 800.0f;

	UPROPERTY(EditAnywhere, DisplayName = "Allow Forward")
	bool mAllowForward = false;

	UPROPERTY(EditAnywhere, DisplayName = "Forward Priority", Meta = (EditCondition = "mRandomPriority == false", EditConditionHides))
	uint32 mForwardPrioirty = 3;

	UPROPERTY(EditAnywhere, DisplayName = "Allow Backward")
	bool mAllowBackward = true;

	UPROPERTY(EditAnywhere, DisplayName = "Backward Priority", Meta = (EditCondition = "mRandomPriority == false", EditConditionHides))
	uint32 mBackwardPrioirty = 0;

	UPROPERTY(EditAnywhere, DisplayName = "Allow Left")
	bool mAllowLeft = true;

	UPROPERTY(EditAnywhere, DisplayName = "Left Priority", Meta = (EditCondition = "mRandomPriority == false", EditConditionHides))
	uint32 mLeftPrioirty = 1;

	UPROPERTY(EditAnywhere, DisplayName = "Allow Right")
	bool mAllowRight = true;

	UPROPERTY(EditAnywhere, DisplayName = "Right Priority", Meta = (EditCondition = "mRandomPriority == false", EditConditionHides))
	uint32 mRightPrioirty = 2;

	UPROPERTY(EditAnywhere, DisplayName = "Random Priority")
	bool mRandomPriority = false;
};
