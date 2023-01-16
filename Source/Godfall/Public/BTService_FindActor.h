// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GodfallBTServiceBase.h"
#include "BTService_FindActor.generated.h"

UENUM(BlueprintType)
enum class EServiceFindActorType : uint8
{
	Player,
};

/**
 * 
 */
UCLASS()
class GODFALL_API UBTService_FindActor : public UGodfallBTServiceBase
{
	GENERATED_BODY()
	
public:
	UBTService_FindActor();

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
	void FindActor(UBehaviorTreeComponent& OwnerComp);

	bool IsFindableActor(const AActor* ownerActor, const AActor* otherActor) const;

private:
	UPROPERTY(EditAnywhere, DisplayName = "Find Type")
	EServiceFindActorType mFindType = EServiceFindActorType::Player;

	UPROPERTY(EditAnywhere, DisplayName = "Target Actor Key")
	FBlackboardKeySelector mTargetActorKey;

	UPROPERTY(EditAnywhere, DisplayName = "Use Radius")
	bool mUseRadius = false;

	UPROPERTY(EditAnywhere, DisplayName = "Radius", Meta = (ClampMin = 0.0f))
	float mRadius = 1000.0f;

	UPROPERTY(EditAnywhere, DisplayName = "Use Half Angle")
	bool mUseHalfAngle = false;

	UPROPERTY(EditAnywhere, DisplayName = "Half Angle", Meta = (ClampMin = 0.0f, ClampMax = 180.0f))
	float mHalfAngle = 180.0f;

	UPROPERTY(EditAnywhere, DisplayName = "Use Raycast")
	bool mUseRaycast = true;
};
