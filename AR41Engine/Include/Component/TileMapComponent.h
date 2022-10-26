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
    CSharedPtr<class CMesh> m_TileMesh;
    CSharedPtr<class CMaterial>  m_TileMaterial;
    ETileShape      m_Shape;
    int     m_CountX;
    int     m_CountY;
    int     m_Count;
    int     m_RenderCount;
    Vector2 m_TileSize;
    Vector4 m_TileTypeColor[(int)ETileOption::End];

public:
    void SetTileMaterial(const std::string& Name);
    void SetTileMaterial(class CMaterial* Material);
    void CreateTile(ETileShape Shape, int CountX, int CountY,
        const Vector2& TileSize);

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

