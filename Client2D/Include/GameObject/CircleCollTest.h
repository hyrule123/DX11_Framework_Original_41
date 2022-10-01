#pragma once
#include "GameObject/GameObject.h"

class CCircleCollTest :
    public CGameObject
{
	friend class CScene;

protected:
	CCircleCollTest();
	CCircleCollTest(const CCircleCollTest& Obj);
	virtual ~CCircleCollTest();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderSphere2D>	m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCircleCollTest* Clone()    const;
};

