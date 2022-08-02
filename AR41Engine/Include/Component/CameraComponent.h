#pragma once

#include "SceneComponent.h"

class CCameraComponent :
    public CSceneComponent
{
    friend class CCameraManager;
	friend class CGameObject;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& component);
	virtual ~CCameraComponent();

protected:
	Matrix		m_matView;
	Matrix		m_matProj;

public:
	virtual void Destroy();
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCameraComponent* Clone()    const;
};

