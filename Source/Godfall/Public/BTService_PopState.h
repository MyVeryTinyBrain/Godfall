// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GodfallBTServiceBase.h"
#include "BTService_PopState.generated.h"

/**
 * 
 */
UCLASS()
class GODFALL_API UBTService_PopState : public UGodfallBTServiceBase
{
	GENERATED_BODY()
	
public:
	UBTService_PopState();

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
	void PopState(UBehaviorTreeComponent& OwnerComp);

private:
	UPROPERTY(EditAnywhere, DisplayName = "State Table Key")
	FBlackboardKeySelector mStateTableKey;

	UPROPERTY(EditAnywhere, DisplayName = "Pop Target State Key")
	FBlackboardKeySelector mPopTargetStateKey;

	UPROPERTY(EditAnywhere, DisplayName = "Target State Names")
	TArray<FName> mTargetStateNames;

	UPROPERTY(EditAnywhere, DisplayName = "Use Prioirty")
	bool mUsePriority = false;
};
