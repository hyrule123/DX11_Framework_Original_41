#pragma once

#include "GameObject.h"

class CMonster :
    public CGameObject
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonster* Clone()    const;
};

