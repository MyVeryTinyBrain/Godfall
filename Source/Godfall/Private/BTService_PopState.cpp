// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PopState.h"
#include "BlackboardKeyType_StateTable.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "GodfallUtil.h"

UBTService_PopState::UBTService_PopState()
{
	NodeName = TEXT("Pop State");

	//mStateTableKey.AddObjectFilter(this, NAME_None, UBlackboardKeyType_StateTable::StaticClass());

	const FString FilterName = FName(NAME_None).ToString() + TEXT("_StateTable");
	mStateTableKey.AllowedTypes.Add(NewObject<UBlackboardKeyType_StateTable>(this, *FilterName));

	mPopTargetStateKey.AddNameFilter(this, NAME_None);

	mEditExecuteFlags = true;
	mExecuteOnSearchStart = true;
	mExecuteOnBecomeRelevant = false;
	mExecuteOnCeaseRelevant = false;
	mExecuteOnTick = false;
}

void UBTService_PopState::OnSearchStartEvent(FBehaviorTreeSearchData& SearchData)
{
	PopState(SearchData.OwnerComp);
}

void UBTService_PopState::OnBecomeRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	PopState(OwnerComp);
}

void UBTService_PopState::OnCeaseRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	PopState(OwnerComp);
}

void UBTService_PopState::TickNodeEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	PopState(OwnerComp);
}

void UBTService_PopState::PopState(UBehaviorTreeComponent& OwnerComp)
{	
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	FStateTable stateTable = blackboardComp->GetValue<UBlackboardKeyType_StateTable>(mStateTableKey.SelectedKeyName);
	TArray<FName> targetStateNames = mTargetStateNames;
#pragma region SHUFFLE STATE NAMES
	if (!mUsePriority)
	{
		GodfallUtil::Sort::Mix(targetStateNames, targetStateNames.Num());
	}
#pragma endregion
	int32 numContains = 0, numSetSucceeded = 0;
	for (const auto& name : targetStateNames)
	{
		bool containsName;
		bool setSucceeded = stateTable.TrySetAvailable(name, false, containsName);
		ensureMsgf(containsName, TEXT("The state name \"%s\" does not exist in the state table."), *name.ToString());
		if (containsName) ++numContains;
		if (setSucceeded) ++numSetSucceeded;
		// �ϳ��� ���� ���濡 �����ϸ� �����մϴ�.
		if (containsName && setSucceeded)
		{
			uint32 numAvailable = 0, numStates = 0;
			for (auto& state : stateTable.States)
			{
				numAvailable += state.Available ? 1 : 0;
				++numStates;
			}
			blackboardComp->SetValue<UBlackboardKeyType_StateTable>(mStateTableKey.SelectedKeyName, stateTable);
			blackboardComp->SetValueAsName(mPopTargetStateKey.SelectedKeyName, name);
			return;
		}
	}
	// ���� �̸��� ��ȿ�ϳ� ���� ������ ��� ���µ��� ��Ȱ��ȭ �����̸�
	// ����� �迭�� �����ϴ� ���µ��� ã�� Ȱ��ȭ ��Ű�� �ٽ� �� �� ���¸� �̽��ϴ�.
	// �� �� ������� ���� ���´� Ȱ��ȭ���� �ʽ��ϴ�.
	// ���� �ʿ��� ���¸� ���������� �̾Ƴ� �� �ְ� �˴ϴ�.
	if (numContains > 0 && numSetSucceeded == 0)
	{
		for (const auto& name : targetStateNames)
		{
			bool containsName;
			stateTable.SetAvailable(name, true, containsName);
			blackboardComp->SetValue<UBlackboardKeyType_StateTable>(mStateTableKey.SelectedKeyName, stateTable);
		}
		PopState(OwnerComp);
	}
}
