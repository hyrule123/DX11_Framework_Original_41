#pragma once

#include "GameObject.h"

class CBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& Obj);
	virtual ~CBullet();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone()    const;
};

