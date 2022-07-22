#pragma once

#include "EngineMath.h"

struct Vector3
{
	float	x, y;

	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& v);
	Vector3(const DirectX::XMVECTOR& v);

	// operator =
	Vector3& operator = (const Vector3& v);
	Vector3& operator = (const DirectX::XMVECTOR& v);
	Vector3& operator = (float f);

	// operator ==, !=
	bool operator == (const Vector3& v)	const;
	bool operator == (const DirectX::XMVECTOR& v)	const;
	bool operator != (const Vector3& v)	const;
	bool operator != (const DirectX::XMVECTOR& v)	const;

	float& operator [](int Index);

	// operator +
	Vector3 operator + (const Vector3& v)	const;
	Vector3 operator + (const DirectX::XMVECTOR& v)	const;
	Vector3 operator + (float f)	const;

	// operator +=
	void operator += (const Vector3& v);
	void operator += (const DirectX::XMVECTOR& v);
	void operator += (float f);


	// operator -
	Vector3 operator - (const Vector3& v)	const;
	Vector3 operator - (const DirectX::XMVECTOR& v)	const;
	Vector3 operator - (float f)	const;

	// operator -=
	void operator -= (const Vector3& v);
	void operator -= (const DirectX::XMVECTOR& v);
	void operator -= (float f);


	// operator *
	Vector3 operator * (const Vector3& v)	const;
	Vector3 operator * (const DirectX::XMVECTOR& v)	const;
	Vector3 operator * (float f)	const;

	// operator *=
	void operator *= (const Vector3& v);
	void operator *= (const DirectX::XMVECTOR& v);
	void operator *= (float f);


	// operator /
	Vector3 operator / (const Vector3& v)	const;
	Vector3 operator / (const DirectX::XMVECTOR& v)	const;
	Vector3 operator / (float f)	const;

	// operator /=
	void operator /= (const Vector3& v);
	void operator /= (const DirectX::XMVECTOR& v);
	void operator /= (float f);

	// operator ++
	const Vector3& operator ++ ();
	const Vector3& operator ++ (int);

	// operator --
	const Vector3& operator -- ();
	const Vector3& operator -- (int);


	float Length()	const;
	void Normalize();
	float Distance(const Vector3& v)	const;
	float Dot(const Vector3& v)	const;
	float Cross(const Vector3& v)	const;
	float Angle(const Vector3& v)	const;



	DirectX::XMVECTOR Convert()	const;
	void Convert(const DirectX::XMVECTOR& v);
};

