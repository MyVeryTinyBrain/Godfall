// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "Components/ActorComponent.h"
#include "CharacterManagerComponent.generated.h"

class AGodfallCharacterBase;
class AGodfallEnemyBase;

enum class ECharacterManagerQueryType : uint8
{
	None,
	Character,
	Enemy,
};

enum class ECharacterManagerQueryDistancePriority : uint8
{
	None,	// �Ÿ� �˻縦 ���� �ʽ��ϴ�.
	Near,	// ���� ����� ���� ��ȯ�մϴ�.
	Far,	// ���� �� ���� ��ȯ�մϴ�.
};

enum class ECharacterManagerQueryDistanceFunction : uint8
{
	/* ���� �� ������ �Ÿ�
	Point�� ���� ��ġ�� �����ϼ���. */
	PointToPoint,

	/* ���� �� ������ �Ÿ�
	Point�� ���� ���� ��ġ�� �����ϼ���.  
	Rotation�� ���� ������ �����ϼ���. */
	PointToLine,

	/* ���� �� ������ �Ÿ�, ���� �� ������ �Ÿ� �� ª�� �Ÿ�
	Point�� ���� ���� ��ġ�� �����ϼ���.  
	Rotation�� ���� ������ �����ϼ���. */
	PointToPoint_PointToLine_Smaller,

	/* ���� �� ������ �Ÿ�, ���� �� ������ �Ÿ� �� �� �Ÿ�
	Point�� ���� ���� ��ġ�� �����ϼ���.  
	Rotation�� ���� ������ �����ϼ���. */
	PointToPoint_PointToLine_Greater,
};

enum class ECharacterManagerQueryScreenDistanceFunction : uint8
{
	/* ���� �� ������ �Ÿ�
	Point�� ���� ��ġ�� �����ϼ���. */
	PointToPoint,

	/* ���� ���� �����Դϴ�.
	���� ���� �������� ���� �ݴ��� ���� ��쿡�� ���� �Ÿ��� �߻��մϴ�.
	Point�� ���� ���� ��ġ�� �����ϼ���.  
	Direction�� ���� ������ �����ϼ���. */
	Dot,

	/* ���� ���� �����Դϴ�.
	���� �Ÿ��� ��� �Ÿ��� ��ȯ�˴ϴ�.
	Point�� ���� ���� ��ġ�� �����ϼ���.  
	Direction�� ���� ������ �����ϼ���. */
	DotAbs,
};

struct FCharacterManagerQueryOption
{
	ECharacterManagerQueryType Type = ECharacterManagerQueryType::Enemy;
};

struct FCharacterManager3DQuery
{
	ECharacterManagerQueryDistancePriority DistancePriority = ECharacterManagerQueryDistancePriority::Near;
	ECharacterManagerQueryDistanceFunction DistanceFunction = ECharacterManagerQueryDistanceFunction::PointToPoint_PointToLine_Smaller;
	FVector Point;
	FRotator Rotation;
};

struct FCharacterManagerScreenQuery
{
	// Ȱ��ȭ�ϸ� ���� �Ÿ��� ������ ����� �����մϴ�.
	bool IgnoreNegativeDistance = true;

	ECharacterManagerQueryDistancePriority DistancePriority = ECharacterManagerQueryDistancePriority::Near;
	ECharacterManagerQueryScreenDistanceFunction DistanceFunction = ECharacterManagerQueryScreenDistanceFunction::Dot;
	FVector2D Point = FVector2D::ZeroVector;
	FVector2D LineDirection; // ����ȭ���� ���� ���̾ �������ϴ�.
};

// ĳ���� ������ �θ� ����ü�Դϴ�.
struct FCharacterManagerQueryFilter
{
	virtual ~FCharacterManagerQueryFilter() {}

	// true�� ��ȯ�ϸ� �ش� ĳ���ʹ� ���Ϳ� ����� ĳ�����Դϴ�.
	virtual bool Search(const AActor* character) const = 0;

	// false�� ��ȯ�ϸ� ������ �ߴܵǰ� ���� �޼����� ���Ե˴ϴ�.
	virtual bool IsValid(FString& invalidDescription) const { return true; }
};
// �˻翡�� ������ ĳ���͸� �߰��ϰų�, �±װ� �����ϴ� ĳ���͸��� �����ŵ�ϴ�.
struct FCharacterManagerQueryDefaultFilter : public FCharacterManagerQueryFilter
{
	virtual bool Search(const AActor* character) const override;
	bool IsNotTargetToIgnore(const AActor* character) const;
	bool TagMatch(const AActor* character) const;

	// �� ĳ���͵��� �˻����� ���ܵ˴ϴ�.
	TArray<const AActor*> Ignores; 

	// �±װ� ���ٸ� �±� �˻縦 ���� �ʽ��ϴ�.
	TArray<FName> Tags;			
};
// Ư�� ��ġ�� ���� ���ͷκ��� ���� ���� ���� �����ϴ� ĳ���͸��� �����ŵ�ϴ�.
struct FCharacterManagerQueryAngleFilter : public FCharacterManagerQueryFilter 
{
	virtual bool Search(const AActor* character) const override;
	virtual bool IsValid(FString& invalidDescription) const override;

	/*
		A = Point���� �Ķ���ͷ� ���޵� character���͸� ���ϴ� ���⺤��. 
		B = Direction�� ��Ÿ���� ���⺤��.
		�϶� A�� B�� ������ ���� �ٸ� ĳ���Ϳ��� ������ ���մϴ�. �ش� ������ MaxAngle���� ũ�� ���ܵ˴ϴ�.
	*/

	// �ٸ� ĳ���͸� ���ϴ� ���⺤�͸� ���ϱ� ���� �������Դϴ�.
	FVector Point;

	// ������ ����� ���⺤���Դϴ�.
	FVector Direction;

	// �ִ� �����Դϴ�.
	float MaxAngle = 90.f;
};
// Ư�� ��ġ���� ĳ���ͱ��� ����ĳ��Ʈ�� ���� ������ ���� ��쿡�� �����ŵ�ϴ�.
struct FCharacterManagerQueryRaycastFilter : public FCharacterManagerQueryFilter
{
	virtual bool Search(const AActor* character) const override;
	virtual bool IsValid(FString& invalidDescription) const override;
	bool IsNotBlocked(const AActor* character) const;

	// ����ĳ��Ʈ�� �����ϱ� ���� �������Դϴ�.
	FVector RaystartLocation;

	// �˻翡 ����� �����Դϴ�.
	UWorld* World = nullptr;

	// �˻翡 ����� �������Դϴ�.
	FName BlockedCheckPreset = GodfallPresets::SweepCollision;

	// �� ĳ���͵��� ����ĳ��Ʈ���� ���ܵ˴ϴ�.
	TArray<const AActor*> Ignores;
};
// Ư�� ��ġ���� �ٸ� ĳ���ͱ��� ���� �Ÿ� ���� �����ϴ� ĳ���͸��� �����ŵ�ϴ�.
struct FCharacterManagerQueryDistanceFilter : public FCharacterManagerQueryFilter
{
	virtual bool Search(const AActor* character) const override;
	bool IsInRadius(const AActor* character) const;

	// �Ÿ��� �����ϱ� ���� ���� ���Դϴ�.
	FVector Point;

	// �Ÿ��� ���ϱ� ���� �������Դϴ�.
	float Radius;

	// ĸ���� �������� ����Ͽ� ĸ���� �𼭸����� ������������ �Ÿ��� ���մϴ�.
	bool UseCapsuleRadius = false;
};
// ���� ������ ĳ����(�ǴϽ� ������ ���)���� �����ŵ�ϴ�.
struct FCharacterManagerQueryExecutableFilter : public FCharacterManagerQueryFilter
{
	virtual bool Search(const AActor* character) const override;
};

enum class ECharacterManagerQueryResult : uint8
{
	Succeeded,
	Failed,
	InvalidFilter,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODFALL_API UCharacterManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterManagerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

public:
	void RegistCharacter(AGodfallCharacterBase* character);
	void UnregistCharacter(AGodfallCharacterBase* character);
	bool Contains(const AGodfallCharacterBase* character) const;

	TArray<TWeakObjectPtr<AActor>> GetEnemies() const { return mEnemies; }

	// ��ȯ: ���� �˻�->3D �Ÿ� ����->��ũ�� �Ÿ� ����(nullptr�� �ƴ� ���) ������ ���� �ϳ��� ĳ���͸� ��ȯ�մϴ�.
	// f3Dfilters: �� ���͸� ��� ����� ĳ���͸� ��ȿ�մϴ�.
	// f3DQuery: ���͸� ����� ĳ���͵��� 3D �Ÿ��� ����, ���ǵ� ��Ģ��� ������ ���� ���� ĳ���͸� ��ȯ�ϴµ� ����մϴ�.
	// option: � ������ ĳ���͸� Ž������ �����մϴ�.
	// fScreenQuery: f3DQuery ���Ŀ�, ĳ���͵��� ��ũ���� �Ÿ��� ����, ���ǵ� ��Ģ��� ������ ���� ���� ĳ���͸� ��ȯ�ϴµ� ����մϴ�.
	// result: ������ ���Ÿ���� Enum�Դϴ�.
	// invalidFilterDescription: ������ ���������� ������ ������ ����˴ϴ�.
	AGodfallCharacterBase* Query(
		const TArray<const FCharacterManagerQueryFilter*>& f3Dfilters, 
		const FCharacterManager3DQuery& f3DQuery, 
		const FCharacterManagerQueryOption& option,
		const FCharacterManagerScreenQuery* fScreenQuery,
		ECharacterManagerQueryResult* result = nullptr, FString* invalidFilterDescription = nullptr) const;

private:
	void WriteQueryResult(ECharacterManagerQueryResult* outResult, ECharacterManagerQueryResult inResult) const;
	void WriteInvalidFilterDescription(ECharacterManagerQueryResult* result, FString* outDescription, const FString& inDescription) const;
	float CalcDistance(const AActor* character, const FCharacterManager3DQuery& f3DQuery) const;

	// ȭ�� ���ο� ������ false�� ��ȯ�մϴ�.
	bool CalcScreenDistance(const AActor* character, const FCharacterManagerScreenQuery* fScreenQuery, float& distance) const;

private:
	UPROPERTY(VisibleAnywhere, DisplayName = "Characters", Meta = (AllowPrivateAccess))
	TArray<TWeakObjectPtr<AActor>> mCharacters;

	UPROPERTY(VisibleAnywhere, DisplayName = "Enemies", Meta = (AllowPrivateAccess))
	TArray<TWeakObjectPtr<AActor>> mEnemies;
};
