// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "BehaviorTree/BTService.h"
#include "GodfallBTServiceBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GODFALL_API UGodfallBTServiceBase : public UBTService
{
	GENERATED_BODY()

public:
	UGodfallBTServiceBase();

protected:
	// �� ���񽺷� ������ �� ȣ��˴ϴ�.
	virtual void OnSearchStartEvent(FBehaviorTreeSearchData& SearchData) {}

	// ���񽺰� ���۵� �� ȣ��˴ϴ�.
	virtual void OnBecomeRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {}

	// ����� �ߴܵ� �� ȣ��˴ϴ�.
	virtual void OnCeaseRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {}

	// Interval ���� ȣ��˴ϴ�.
	virtual void TickNodeEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {}

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) final override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) final override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) final override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) final override;

public:
	bool IsValidKey(const class UBlackboardComponent* blackboardComp, const FBlackboardKeySelector& keySelector) const;
	
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Edit Execute flags", Meta = (EditCondition = "false", EditConditionHides))
	bool mEditExecuteFlags = true;

	UPROPERTY(EditAnywhere, DisplayName = "Execute on Search Start", Meta = (EditCondition = "mEditExecuteFlags == true"))
	bool mExecuteOnSearchStart = true;

	UPROPERTY(EditAnywhere, DisplayName = "Execute on Tick", Meta = (EditCondition = "mEditExecuteFlags == true"))
	bool mExecuteOnTick = true;

	UPROPERTY(EditAnywhere, DisplayName = "Execute on Become Relevant", Meta = (EditCondition = "mEditExecuteFlags == true"))
	bool mExecuteOnBecomeRelevant = true;

	UPROPERTY(EditAnywhere, DisplayName = "Execute on Cease Relevant", Meta = (EditCondition = "mEditExecuteFlags == true"))
	bool mExecuteOnCeaseRelevant = true;
};
