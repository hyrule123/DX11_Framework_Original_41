#pragma once

#include "../EngineInfo.h"

class CTransform
{
	friend class CSceneComponent;

private:
	CTransform();
	CTransform(const CTransform& transform);
	~CTransform();

private:
	class CScene* m_Scene;
	class CGameObject* m_Object;
	class CSceneComponent* m_Owner;

private:
	bool		m_Is2D;
	CTransform* m_Parent;
	std::vector<CTransform*>    m_vecChild;

private:
	bool	m_InheritScale;
	bool	m_InheritRotX;
	bool	m_InheritRotY;
	bool	m_InheritRotZ;
	bool	m_InheritParentRotationPosX;
	bool	m_InheritParentRotationPosY;
	bool	m_InheritParentRotationPosZ;
	bool	m_UpdateScale;
	bool	m_UpdateRot;
	bool	m_UpdateRotAxis;
	bool	m_UpdatePos;

public:
	void SetInheritScale(bool Inherit)
	{
		m_InheritScale = Inherit;
	}

	void SetInheritRotX(bool Inherit)
	{
		m_InheritRotX = Inherit;
	}

	void SetInheritRotY(bool Inherit)
	{
		m_InheritRotY = Inherit;
	}

	void SetInheritRotZ(bool Inherit)
	{
		m_InheritRotZ = Inherit;
	}

	void SetInheritParentRotationPosX(bool Inherit)
	{
		m_InheritParentRotationPosX = Inherit;
	}

	void SetInheritParentRotationPosY(bool Inherit)
	{
		m_InheritParentRotationPosY = Inherit;
	}

	void SetInheritParentRotationPosZ(bool Inherit)
	{
		m_InheritParentRotationPosZ = Inherit;
	}

	// 부모의 정보를 자식 Transform에 적용한다.
	void InheritScale(bool Current);
	void InheritRotation(bool Current);
	void InheritParentRotationPos(bool Current);

	void InheritWorldScale(bool Current);
	void InheritWorldRotation(bool Current);
	void InheritWorldParentRotationPos(bool Current);

private:	// Relative
	Vector3		m_RelativeScale;
	Vector3		m_RelativeRot;
	Vector3		m_RelativePos;
	Vector3		m_RelativeAxis[AXIS_MAX];

public:
	Vector3 GetRelativeScale()	const
	{
		return m_RelativeScale;
	}

	Vector3 GetRelativeRot()	const
	{
		return m_RelativeRot;
	}

	Vector3 GetRelativePos()	const
	{
		return m_RelativePos;
	}

	Vector3 GetRelativeAxis(AXIS Axis)	const
	{
		return m_RelativeAxis[Axis];
	}

public:
	void SetRelativeScale(const Vector3& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScaleX(float x);
	void SetRelativeScaleY(float y);
	void SetRelativeScaleZ(float z);
	void SetRelativeRotation(const Vector3& Rot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativePosition(const Vector3& Pos);
	void SetRelativePosition(float x, float y, float z);
	void SetRelativePositionX(float x);
	void SetRelativePositionY(float y);
	void SetRelativePositionZ(float z);

	void AddRelativeScale(const Vector3& Scale);
	void AddRelativeScale(float x, float y, float z);
	void AddRelativeScaleX(float x);
	void AddRelativeScaleY(float y);
	void AddRelativeScaleZ(float z);
	void AddRelativeRotation(const Vector3& Rot);
	void AddRelativeRotation(float x, float y, float z);
	void AddRelativeRotationX(float x);
	void AddRelativeRotationY(float y);
	void AddRelativeRotationZ(float z);
	void AddRelativePosition(const Vector3& Pos);
	void AddRelativePosition(float x, float y, float z);
	void AddRelativePositionX(float x);
	void AddRelativePositionY(float y);
	void AddRelativePositionZ(float z);
};

