#pragma once

#include <EngineMinimal.h>
#include "GodfallUtil.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FParabolaCoefficient2
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// y = C * (X - A)^2 + B
	double A = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// y = C * (X - A)^2 + B
	double B = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// y = C * (X - A)^2 + B
	double C = 0;

	bool IsValid() const { return !(A == B && B == C && C == 0.0); }
};

USTRUCT(BlueprintType, Blueprintable)
struct FParabolaCoefficient3
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FParabolaCoefficient2 Coefficient2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector P0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector P1; // CrossPoint

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector P2;

	/*
	XYDistance = XY ��鿡���� �Ÿ�
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double P0XYDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double P1XYDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double P2XYDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CrossPointHeight;

	/* z = f(t') �϶� t'�� ��Ÿ Ÿ���� ������ ���Դϴ�.
	t�� 0 ~ 1 �����϶� �������� ������ ������ ���̿� �����մϴ�. (0�϶� ������, 1�϶� ����)
	�̶� t' = t + DeltaTime �Դϴ�.
	�ᱹ �� ���� DeltaTime�� �����־� �Ÿ��� ���� ������ �ӵ��� �������� �ϴ� ���Դϴ�.
	���� t' = t + DeltaTime * DeltaTimeMultiplier �� �˴ϴ�. */
	double CalDeltaTimeMultiplier(double movePerSec) const { return  movePerSec / P2XYDistance; }

	bool IsValid() const { return Coefficient2.IsValid(); }

	bool UpdateStartPoint(const FVector& p);
};

namespace GodfallUtil
{
	namespace Vector3D
	{
		bool CalcParabolaCoefficient3(const FVector& p0, double crossPointHeight, const FVector& p2, FParabolaCoefficient3& out);

		FVector Parabola(const FParabolaCoefficient3& coefficient, double t);
	}

	namespace Vector2D
	{
		bool CalcParabolaCoefficient2(const FVector2D& p0, const FVector2D& p1, const FVector2D& p2, FParabolaCoefficient2& out);

		FVector2D Parabola(const FParabolaCoefficient2& coefficient, double x);

		// �������� ������ ���ϴ� ������ ���а� �簢���� ������ ���մϴ�.
		// �簢���� ���̰� 0 �Ǵ� ������ ��쿡�� �����͸� ��ȯ�մϴ�.
		// ���� �����Ϳ� ������ ��쿡�� �����͸� ��ȯ�մϴ�.
		FVector2D EndPointInRect(float halfWidth, float halfHeight, const FVector2D& point);
	}

	namespace Sort
	{
		template<typename T>
		void Mix(T& container, uint32 num) 
		{
			for (uint32 i = 0; i < num; ++i) 
			{
				uint32 randIndex = FMath::Rand() % num;
				std::swap(container[i], container[randIndex]);
			}
		}
	}

	struct FConeShape
	{
		FConeShape(const FVector& pivot, const FVector& direction, float radius, float halfAngle) :
			Pivot(pivot), DamageDirection(direction.SquaredLength() < FLT_EPSILON ? FVector::ForwardVector : direction), Radius(radius), HalfAngle(halfAngle)
		{
		}

		FVector Pivot;
		FVector DamageDirection;
		float Radius;
		float HalfAngle;

		bool Contains(const FVector& point) const
		{
			float dist = FVector::Distance(Pivot, point);
			if (dist > Radius) return false;

			float dot = FVector::DotProduct(DamageDirection, (point - Pivot).GetSafeNormal());
			float limitCos = FMath::Cos(FMath::DegreesToRadians(HalfAngle));
			if (dot < limitCos) return false;

			return true;
		}
	};

	namespace String
	{
		bool CompareNames(const TArray<FName>& A, const TArray<FName>& B, FName* equalName = nullptr);
		bool CompareStrings(const TArray<FString>& A, const TArray<FString>& B, FString* equalString = nullptr);
	}
}

