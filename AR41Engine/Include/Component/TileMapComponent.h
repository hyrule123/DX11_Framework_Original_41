#pragma once

#include "PrimitiveComponent.h"
#include "Tile.h"

class CTileMapComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CTileMapComponent();
    CTileMapComponent(const CTileMapComponent& component);
    virtual ~CTileMapComponent();

protected:
    std::vector<CTile*> m_vecTile;
    //CSharedPtr<class CTexture>  m_Texture;

public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CTileMapComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

