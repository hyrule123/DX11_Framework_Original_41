#pragma once
#include "SceneComponent.h"
class CCollider :
    public CSceneComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CCollider();
    CCollider(const CCollider& component);
    virtual ~CCollider();

protected:
    CSharedPtr<class CMesh> m_Mesh;
    Vector3                 m_Color;
    ECollider_Type          m_ColliderType;
    Vector3                 m_Min;
    Vector3                 m_Max;
    std::list<CCollider*>   m_PrevCollisionList;    // ���� �����ӿ� �浹�ϰ� �ִ� ��ü��
    std::list<int>          m_CurrentSectionList;   // ���� �浹ü�� ��� �浹������ �����ִ��� �Ǵ��ϱ� ���� ����.

public:
    const Vector3& GetMin() const
    {
        return m_Min;
    }

    const Vector3& GetMax() const
    {
        return m_Max;
    }

    ECollider_Type GetColliderType()    const
    {
        return m_ColliderType;
    }

public:
    void AddSectionIndex(int Index)
    {
        m_CurrentSectionList.push_back(Index);
    }

    void AddPrevCollisionCollider(CCollider* Collider)
    {
        m_PrevCollisionList.push_back(Collider);
    }

    void DeletePrevCollisionCollider(CCollider* Collider);

    // ���� �����ӿ� �浹�ߴ� �浹ü���� �ݺ��ϸ� ���� ���� ������ ��ġ���� �Ǵ��Ѵ�.
    void CheckPrevCollisionColliderSection();

    // ���� �����ӿ� �浹�Ǵ� ��ü�鿡�� �浹������ �뺸�Ѵ�
    void SendPrevCollisionEnd();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CCollider* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

