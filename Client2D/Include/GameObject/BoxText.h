#pragma once
#include "GameObject\GameObject.h"
class CBoxText :
    public CGameObject
{
	friend class CScene;

protected:
	CBoxText();
	CBoxText(const CBoxText& Obj);
	virtual ~CBoxText();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBoxText* Clone()    const;
};

