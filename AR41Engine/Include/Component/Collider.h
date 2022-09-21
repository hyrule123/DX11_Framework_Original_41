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
    std::list<CCollider*>   m_PrevCollisionList;    // 이전 프레임에 충돌하고 있던 물체들
    std::list<int>          m_CurrentSectionList;   // 현재 충돌체가 어느 충돌영역에 속해있는지 판단하기 위한 정보.

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

    // 이전 프레임에 충돌했던 충돌체들을 반복하며 현재 나의 영역과 겹치는지 판단한다.
    void CheckPrevCollisionColliderSection();

    // 이전 프레임에 충돌되던 물체들에게 충돌해제를 통보한다
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

