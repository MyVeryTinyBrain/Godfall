// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <EngineMinimal.h>
#include <NavigationSystem.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>
#include "GodfallTags.h"
#include "GodfallEnums.h"
#include "GodfallPresets.h"

#define EditAnywhere
#define VisibleAnywhere
#define BlueprintReadOnly
#define BlueprintReadWrite

// �������Ʈ���� ȣ�� ������ �Լ��� �����մϴ�.
#define BlueprintCallable

#define BlueprintPure
#define BlueprintThreadSafe

// �������Ʈ���� ���� ������ �̺�Ʈ�� �����մϴ�.
// �ش� �Լ��� �����θ� �����ϸ� �� �˴ϴ�.
// ���� �ش� �Լ��� �̸� + _Implementation �̶�� �����Լ��� �����մϴ�.
// �� �����Լ��� �ڵ�� �̺�Ʈ ������ ������ �� �ֽ��ϴ�.
#define BlueprintNativeEvent

#define DisplayName
#define Category
#define Transient

#define Abstract
#define BlueprintType
#define Blueprintable

// ��Ÿ �Ӽ��� ������ �� �ֽ��ϴ�.
#define Meta

// Private ���� �����ڸ� �����ų�� �ֽ��ϴ�.
#define AllowPrivateAccess

// ����ڰ� ���콺�� �� �� ���ڰ� ��踦 ����� ���� ������ ������ ������ ����� ���ڸ� �Է��� �� �ֽ��ϴ�.
#define ClampMin

// ����ڰ� ���콺�� �� �� ���ڰ� ��踦 ����� ���� ������ ������ ������ ����� ���ڸ� �Է��� �� �ֽ��ϴ�.
#define ClampMax

// �����ϸ� ����ڰ� ������ ������ ���� �Ӽ��� �� �� ���� �˴ϴ�. 
// �׷��� ��� �� �Է��Ͽ� �� ������ ���� ���ڸ� ������ �� �ֽ��ϴ�. ��κ��� ��� UIMin�� ClampMin�� ��� ����ϴ� ���� �����ϴ�.
#define UIMin

// �����ϸ� ����ڰ� ������ ������ ���� �Ӽ��� �� �� ���� �˴ϴ�. 
// �׷��� ��� �� �Է��Ͽ� �� ������ ���� ���ڸ� ������ �� �ֽ��ϴ�. ��κ��� ��� UIMax�� ClampMax�� ��� ����ϴ� ���� �����ϴ�.
#define UIMax

// �ٸ� �Ӽ��� ���� �Ӽ��� �б� ���뿡�� ���� �������� �����ϴ� �� ����� �� �ֽ��ϴ�.
#define EditCondition

// �⺻������ EditCondition������ false�� �򰡵Ǹ� �Ӽ��� �б� �������� �����մϴ�.
#define EditConditionHides

DECLARE_LOG_CATEGORY_EXTERN(Godfall, Log, All)
#define GODFALL_CALLINFO								(FString(__FUNCTION__) + FString(TEXT(": ")) + FString::FromInt(__LINE__))
#define GODFALL_UE_LOG(Verbosity, Str)					UE_LOG(Godfall, Verbosity, TEXT("%s %s"), *GODFALL_CALLINFO, Str)
#define GODFALL_UE_LOG_FORMAT(Verbosity, Format, ...)	UE_LOG(Godfall, Verbosity, TEXT("%s %s"), *GODFALL_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG(Str)										GODFALL_UE_LOG(Log, Str)
#define LOGF(Format, ...)								GODFALL_UE_LOG_FORMAT(Log, Format, ##__VA_ARGS__)
#define LOGW(Str)										GODFALL_UE_LOG(Warning, Str)
#define LOGFW(Format, ...)								GODFALL_UE_LOG_FORMAT(Warning, Format, ##__VA_ARGS__)
#define LOGE(Str)										GODFALL_UE_LOG(Error, Str)
#define LOGFE(Format, ...)								GODFALL_UE_LOG_FORMAT(Error, Format, ##__VA_ARGS__)


#define Null (0)
#define Nullable (0)
#define CantBeNull (0)