#pragma once

#include "GameObject.h"

class CPlayer2D :
    public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSceneComponent>	m_RightChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone()    const;

public:
	void MoveUp();
	void MoveDown();
	void Rotation();
	void RotationInv();
};

