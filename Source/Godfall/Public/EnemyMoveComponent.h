// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "Components/ActorComponent.h"
#include "GodfallEnemyEnums.h"
#include "EnemyMoveComponent.generated.h"

UENUM(BlueprintType)
enum class EEnemyMoveComponentTargetType : uint8
{
	Vector,
	Actor,
};

UENUM(BlueprintType)
enum class EEnemyMoveComponentState : uint8
{
	Stop,
	Move,
	Wait,
	Avoid,
};

UENUM(BlueprintType)
enum class EEnemyMoveComponentResult : uint8
{
	InProgress,
	Succeeded,
	Failed,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODFALL_API UEnemyMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyMoveComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Stop();
	void WalkToLocation(const FVector& targetLocation, E4Direction walkDirection);
	void WalkToActor(const AActor* targetActor, E4Direction walkDirection);
	void RunToLocation(const FVector& targetLocation);
	void RunToActor(const AActor* targetActor);
	void UptateTargetLocation(const FVector& targetLocation);
	void UptateTargetActor(const AActor* targetActor);
	EEnemyMoveComponentState GetMoveState() const { return mMoveState; }
	EEnemyMoveComponentResult GetResult() const { return mResult; }

	bool GetTargetLocation(FVector& location) const;
	bool IsNearWithTarget() const;
	bool IsNearWith(const FVector& location, float distance) const;
	bool IsNearWith(const AActor* actor, float distance) const;
	bool GetNextLocation(FVector& nextLocation, bool* isPartial = nullptr) const;
	bool GetNextAvoidLocation(FVector& nextLocation, bool* isPartial = nullptr) const;
	FVector RotateVector(const FVector& vector, E4Direction rotateDirection) const;
	bool IsBlocked(const FVector& nextDirection, E4Direction rotateDirection, float distance, FName tagName, FName profileName, float& hitDistance) const;
	bool IsBlocked(const FVector& nextDirection, E4Direction rotateDirection, float distance, FName tagName, FName profileName) const;
	bool IsBlockedByOtherCharacter(const FVector& nextDirection, E4Direction rotateDirection, float distance) const;
	bool IsBlockedByOtherCharacterOrStatic(const FVector& nextDirection, E4Direction rotateDirection, float distance) const;

	float GetMoveDistanceAccumulation() const { return mMoveDistanceAccumulation; }

private:
	void SetState(EEnemyMoveComponentState state);
	void TickMove();
	void TickWait(float deltaTime);
	bool CanAvoid() const;
	bool IsNearWithAvoidTarget() const;
	void TickAvoid();

	void SetToSucceeded();
	void SetToFailed();
	void SetLookDirection(const FVector& direction);
	void ApplyStopToAnimInstance();
	void ApplyMoveTypeToAnimInstance(EEnemyMoveType moveType);
	void ApplyWalkDirectionToAnimInstance(E4Direction direction);
	FVector ConvertXYDirection(const FVector& direction) const;
	FVector GetActorToTargetXYDirection(const FVector& targetLocation) const;

	void AccumulateMoveDistance();

public:
	/* �� ������Ʈ�� ���� �̵� ��� �����Դϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Move")
	bool mMove = true;

	UPROPERTY(EditAnywhere, DisplayName = "Stop if partial path")
	/* ��ǥ ������ ������ �� ���� ��ǥ�� ���� ��������� ��츦 Partial �̶�� �մϴ�.
	�� ��쿡 �׳��� �ּ��� ��ġ�� �̵�����, �ƴϸ� �������� ���� �÷����Դϴ�.
	Ȱ��ȭ�ϸ� ������ �� ���� ��, ����ϴ�.*/
	bool mStopIfPartialPath = true;

	UPROPERTY(EditAnywhere, DisplayName = "Look On Changed Move State")
	/* Move State�� �Ǿ��� �� ��ǥ�� ���ϴ� ������ �Ĵٺ��ϴ�.
	Move State�߿��� ��ǥ�� ���ϴ� ������ �Ĵٺ�����,
	��ǥ���� �Ÿ��� ����� ���� �̵� ����� �̵����� �ʰ� ����Ǿ� ��ǥ ������ �Ĵٺ��� �ʰ� �˴ϴ�.
	������ ��ǥ ������ �Ĵٺ��� �ϱ� ���ؼ� ���Ǵ� �÷����Դϴ�. */
	bool mLookOnChangedMoveState = true;

	/* �� ������Ʈ�� �����ڰ� ���� ĸ���� �̵� ���� Ȥ�� �̵��Ϸ��� �������� �����Ͽ� ���߰ų� ȸ���ϴµ� ���Ǵ� �Ÿ��Դϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Block Distance", Meta = (ClampMin = 0.1f))
	float mBlockDistance = 100.0f;

	/* ��ǥ������ �Ÿ��� �̰ͺ��� �۴ٸ� ���߰� �˴ϴ�.
	ĳ���Ͱ� ��ǥ�� ��쿡�� �� ĳ���Ϳ� ��ǥ ĳ������ �������� ��ģ �͸�ŭ�� �Ÿ��� ���� �� ������ �Ÿ����� �����Ͽ� �����մϴ�.
	���Ͱ� ��ǥ�� ��쿡�� �� ĳ������ �������� ���� �� ������ �Ÿ����� �����Ͽ� �����մϴ�.
	�̰��� ĳ������ ĸ�� ���������� ���� ��ǥ�� ������ �ٴٸ� �� ���� ��츦 �����ϱ� �����Դϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Stop Radius", Meta = (ClampMin = 0.1f))
	float mStopRadius = 100.0f;

	/* �̵��ϰ��� �ϴ� ������ �ٸ� ĳ���ͳ� �ݶ��̴��� ���� ���� ��쿡 ����ϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Use Wait")
	bool mUseWait = true;

	/* ���ߴ� �߿� ��ǥ�� �Ĵٺ��ϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Look On Wait", Meta = (EditCondition = "mUseWait == true", EditConditionHides))
	bool mLookOnWait = true;

	/* ���ߴ� �߿� ȸ�� ���·� ��ȯ�� �� �ֽ��ϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Use Avoid")
	bool mUseAvoid = true;

	/* ȸ�Ǹ� ������������ �Ÿ��κ��� �󸶳� �ָ� ȸ�������� ���� �Ÿ��Դϴ�. */
	UPROPERTY(EditAnywhere, DisplayName = "Avoid Distance", Meta = (EditCondition = "mUseAvoid == true", EditConditionHides, ClampMin = 0.1f))
	float mAvoidDistance = 450.0f;

	UPROPERTY(EditAnywhere, DisplayName = "Move Type")
	EEnemyMoveType mMoveType = EEnemyMoveType::Run;

	UPROPERTY(EditAnywhere, DisplayName = "Walk Direction", Meta = (EditCondition = "mMoveType == EEnemyMoveType::Walk", EditConditionHides))
	E4Direction mWalkDirection = E4Direction::Forward;

	UPROPERTY(EditAnywhere, DisplayName = "Target Type")
	EEnemyMoveComponentTargetType mTargetType = EEnemyMoveComponentTargetType::Vector;

	UPROPERTY(EditAnywhere, DisplayName = "Target Location", Meta = (EditCondition = "mTargetType == EEnemyMoveComponentTargetType::Vector", EditConditionHides))
	FVector mTargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, DisplayName = "Target Actor", Meta = (EditCondition = "mTargetType == EEnemyMoveComponentTargetType::Actor", EditConditionHides))
	TWeakObjectPtr<const AActor> mTargetActor = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Avoid Collision Ignore", Meta = (EditCondition = "mUseAvoid == true", EditConditionHides))
	TWeakObjectPtr<const AActor> mAvoidCollisionIgnore;

	UPROPERTY(EditAnywhere, DisplayName = "Avoid Collision Ignores", Meta = (EditCondition = "mUseAvoid == true", EditConditionHides))
	TArray<TWeakObjectPtr<const AActor>> mAvoidCollisionIgnores;

private:
	UPROPERTY()
	class AGodfallEnemyBase* mEnemy = 0;

	UPROPERTY()
	class UGodfallEnemyAnimInstanceBase* mEnemyAnimInstance = 0;

	UPROPERTY(VisibleAnywhere, DisplayName = "Move State", Meta = (AllowPrivateAccess))
	EEnemyMoveComponentState mMoveState = EEnemyMoveComponentState::Stop;

	UPROPERTY(VisibleAnywhere, DisplayName = "Move Result", Meta = (AllowPrivateAccess))
	EEnemyMoveComponentResult mResult = EEnemyMoveComponentResult::Succeeded;

	UPROPERTY(VisibleAnywhere, DisplayName = "Wait Accumulation", Meta = (AllowPrivateAccess))
	float mWaitAccumulation = 0.0f;

	UPROPERTY(VisibleAnywhere, DisplayName = "Avoid Target Location", Meta = (AllowPrivateAccess))
	FVector mAvoidTargetLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, DisplayName = "Avoid Direction", Meta = (AllowPrivateAccess))
	E4Direction mAvoidDirection = E4Direction::Backward;

	UPROPERTY()
	FVector mPrevLocation;

	UPROPERTY()
	float mMoveDistanceAccumulation = 0.0f;
};
