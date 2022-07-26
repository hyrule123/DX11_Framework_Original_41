
#include "Transform.h"

CTransform::CTransform()	:
	m_Is2D(true),
	m_InheritScale(false),
	m_InheritRotX(false),
	m_InheritRotY(false),
	m_InheritRotZ(false),
	m_InheritParentRotationPosX(false),
	m_InheritParentRotationPosY(false),
	m_InheritParentRotationPosZ(false),
	m_UpdateScale(false),
	m_UpdateRot(false),
	m_UpdateRotAxis(false),
	m_UpdatePos(false)
{
}

CTransform::CTransform(const CTransform& transform)
{
}

CTransform::~CTransform()
{
}

void CTransform::InheritScale(bool Current)
{
}

void CTransform::InheritRotation(bool Current)
{
}

void CTransform::InheritParentRotationPos(bool Current)
{
}

void CTransform::InheritWorldScale(bool Current)
{
}

void CTransform::InheritWorldRotation(bool Current)
{
}

void CTransform::InheritWorldParentRotationPos(bool Current)
{
}
