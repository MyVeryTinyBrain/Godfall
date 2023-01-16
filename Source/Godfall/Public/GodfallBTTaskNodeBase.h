// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GodfallBTTaskNodeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GODFALL_API UGodfallBTTaskNodeBase : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UGodfallBTTaskNodeBase();
	
protected:
	// �½�ũ�� ���۵� �� ȣ��˴ϴ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// �½�ũ�� �ߴܵ� �� ȣ��˴ϴ�.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// �½�ũ�� ���۵� �� �������̶�� �� ƽ���� ȣ��˴ϴ�.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// �޼����� �޾��� �� ȣ��˴ϴ�.
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;

	// �½�ũ�� �ߴܵǸ� ȣ��˴ϴ�.
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

public:
	bool IsValidKey(const class UBlackboardComponent* blackboardComp, const FBlackboardKeySelector& keySelector) const;
};
