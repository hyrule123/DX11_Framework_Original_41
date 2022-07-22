#pragma once

#include "../../Ref.h"

class CMesh :
    public CRef
{
    friend class CMeshManager;

protected:
    CMesh();
    virtual ~CMesh() = 0;

protected:
    class CScene* m_Scene;

public:
    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

protected:
    std::vector<MeshContainer*> m_vecContainer;
    std::vector<MeshSlot*>      m_vecMeshSlot;

    Vector3 m_Min;
    Vector3 m_Max;
    MeshType    m_MeshType;

public:
    MeshType GetMeshType()  const
    {
        return m_MeshType;
    }

    const Vector3& GetMin() const
    {
        return m_Min;
    }

    const Vector3& GetMax() const
    {
        return m_Max;
    }

public:
    virtual bool CreateMesh(void* VtxData, int Size, int Count,
        D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
        void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
        D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
        DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);
    virtual void Render();
    virtual void Render(int SlotNumber);


protected:
    bool CreateBuffer(BufferType Type, void* Data, int Size,
        int Count, D3D11_USAGE Usage, ID3D11Buffer** Buffer);
};

