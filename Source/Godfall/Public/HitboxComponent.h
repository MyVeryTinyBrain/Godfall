// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Godfall.h"
#include "Components/ActorComponent.h"
#include "HitboxComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(
FOnHitboxOverlap,
UPrimitiveComponent*, OverlappedComponent,
AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex,
bool, bFromSweep, const FHitResult&, SweepResult);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODFALL_API UHitboxComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHitboxComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	UFUNCTION()
	void OnHitboxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:
	void RemoveHitbox(UPrimitiveComponent* hitbox);
	void AddHitboxIndex(int index, UPrimitiveComponent* hitbox);
	int GetHitboxIndex(UPrimitiveComponent* hitbox) const;
	void SetHitboxCollision(int index, bool value);
	bool AddActorToHitBuffer(int index, AActor* actor);
	bool IsContainsInHitBuffer(int index, AActor* actor) const;
	void ResetHitBuffer(int index);

	void SetCollisionTagUse(bool value) { mUseCollisionTags = value; }
	bool IsUsingCollisionTag()const { return mUseCollisionTags; }
	void AddCollisionTag(const FName& tag);
	void SetCollisionTags(const TArray<FName>& tags);
	bool RemoveCollisionTag(const FName& tag);
	bool ContainsCollisionTag(const FName& tag);

	bool CompareTags(const AActor* otherActor) const;

private: 
	// ��ϵ� ��� �ε������Դϴ�.
	TArray<int> mIndices;

	// ��ϵ� ��� ��Ʈ�ڽ����Դϴ�.
	TArray<UPrimitiveComponent*> mHitboxes;

	// ��ϵ� ��Ʈ�ڽ��� �ε����� �����Ǿ� �ֽ��ϴ�.
	// ���� �ε����� ��Ʈ�ڽ����� �ϳ��� ��Ʈ�ڽ��� ����մϴ�.
	// ex) 0�� �ε����� ��Ʈ�ڽ�A�� ��Ʈ�� ��� 0�� �ε����� ��Ʈ�ڽ�B�� ��Ʈ�ϴ��� �̺�Ʈ�� �߻����� �ʽ��ϴ�.
	TMap<UPrimitiveComponent*, int> mHitboxIndices;

	// �ε����� ��Ʈ�ڽ����� �з��Ǿ� �ֽ��ϴ�.
	TMap<int, TArray<UPrimitiveComponent*>> mHitboxesByIndex;

	// ��Ʈ �����Դϴ�.
	// ��Ʈ�� ���͵��� ����Ǹ� ���� ������ ����˴ϴ�.
	TMap<int, TSet<AActor*>> mHitBuffer;

private:
	UPROPERTY(EditAnywhere, DisplayName = "Use Collision Tags", Meta = (AllowPrivateAccess))
	bool mUseCollisionTags = false;

	UPROPERTY(EditAnywhere, DisplayName = "Collision Tags", Meta = (AllowPrivateAccess))
	TArray<FName> mCollisionTags;

public:
	FOnHitboxOverlap OnOverlap;
	FOnHitboxOverlap OnOverlapWithoutCondition;
};
