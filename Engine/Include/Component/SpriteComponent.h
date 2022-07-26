#pragma once
#include "PrimitiveComponent.h"
class CSpriteComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;

protected:
    CSpriteComponent();
    CSpriteComponent(const CSpriteComponent& component);
    virtual ~CSpriteComponent();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CSpriteComponent* Clone()    const;
};

