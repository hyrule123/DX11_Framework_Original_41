#pragma once

#include "Component.h"
#include "Transform.h"

class CSceneComponent :
    public CComponent
{
	friend class CGameObject;

protected:
	CSceneComponent();
	CSceneComponent(const CSceneComponent& component);
	virtual ~CSceneComponent();

protected:
	class CTransform* m_Transform;
    CSceneComponent* m_Parent;
    std::vector<CSharedPtr<CSceneComponent>>    m_vecChild;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CSceneComponent* Clone()    const;
};

