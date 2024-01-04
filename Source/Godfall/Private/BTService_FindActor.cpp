// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindActor.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include "GodfallPlayerController.h"
#include <AIController.h>

UBTService_FindActor::UBTService_FindActor()
{
	NodeName = TEXT("Find Actor");

	mEditExecuteFlags = true;
	mExecuteOnSearchStart = true;
	mExecuteOnBecomeRelevant = false;
	mExecuteOnCeaseRelevant = false;
	mExecuteOnTick = false;

	mTargetActorKey.AddObjectFilter(this, NAME_None, AActor::StaticClass());
}

void UBTService_FindActor::OnSearchStartEvent(FBehaviorTreeSearchData& SearchData)
{
	FindActor(SearchData.OwnerComp);
}

void UBTService_FindActor::OnBecomeRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FindActor(OwnerComp);
}

void UBTService_FindActor::OnCeaseRelevantEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FindActor(OwnerComp);
}

void UBTService_FindActor::TickNodeEvent(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FindActor(OwnerComp);
}

void UBTService_FindActor::FindActor(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	AActor* actor = nullptr;
	switch (mFindType)
	{
		case EServiceFindActorType::Player:
		{
			AGodfallPlayerController* playerController = Cast<AGodfallPlayerController>(GetWorld()->GetFirstPlayerController());
			if (playerController)
			{
				AActor* player = playerController->GetPawn();
				if (IsFindableActor(OwnerComp.GetAIOwner()->GetPawn(), player)) actor = player;
			}
		}
		break;
	}
	blackboardComp->SetValueAsObject(mTargetActorKey.SelectedKeyName, actor);
}

bool UBTService_FindActor::IsFindableActor(const AActor* ownerActor, const AActor* otherActor) const
{
	// ���ϴ� ���Ͱ� ���� ���� �����ϴ��� �˻�
	if (mUseRadius)
	{
		if (FVector::Distance(ownerActor->GetActorLocation(), otherActor->GetActorLocation()) > mRadius) return false;
	}
	// ���ϴ� ���Ͱ� ������ ������ �þ߰��� �����ϴ��� �˻�
	if (mUseHalfAngle)
	{
		FVector ownerForward = ownerActor->GetActorForwardVector();
		FVector ownerToOther = (otherActor->GetActorLocation() - ownerActor->GetActorLocation()).GetSafeNormal();
		if (FMath::Cos(FMath::DegreesToRadians(mHalfAngle)) > FVector::DotProduct(ownerForward, ownerToOther)) return false;
	}
	// ���ϴ� ���Ͱ� ���� ���� �ִ��� �˻�
	if (mUseRaycast)
	{
		FHitResult hit;
		FCollisionQueryParams params(NAME_None, true);
		bool raycastResult = GetWorld()->LineTraceSingleByProfile(
			hit,
			ownerActor->GetActorLocation(), otherActor->GetActorLocation(),
			GodfallPresets::SweepCollision,
			params);

		if (raycastResult) return false;
	}
	return true;
}
