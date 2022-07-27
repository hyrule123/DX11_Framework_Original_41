#pragma once

#include "Component/SceneComponent.h"
#include "Component/ObjectComponent.h"

class CGameObject :
    public CRef
{
    friend class CScene;

protected:
    CGameObject();
    CGameObject(const CGameObject& Obj);
    virtual ~CGameObject();

protected:
    class CScene* m_Scene;

public:
    class CScene* GetScene()    const
    {
        return m_Scene;
    }

    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

public:
    // 여기에 재정의하는 이유는 이 오브젝트가 제거될때 가지고 있는 모든 컴포넌트들도 제거를 해주기
    // 위해서이다.
    virtual void Destroy();

protected:
    CSharedPtr<CSceneComponent> m_RootComponent;
    std::list<CSceneComponent*> m_SceneComponentList;
    std::vector<CSharedPtr<CObjectComponent>>   m_vecObjectComponent;

    CGameObject* m_Parent;
    std::vector<CSharedPtr<CGameObject>>    m_vecChildObject;
    float       m_LifeTime;

public:
    void SetLifeTime(float LifeTime)
    {
        m_LifeTime = LifeTime;
    }

    void SetRootComponent(CSceneComponent* Component)
    {
        m_RootComponent = Component;
    }

    CSceneComponent* GetRootComponent() const
    {
        return m_RootComponent;
    }

    const std::list<CSceneComponent*>& GetSceneComponents() const
    {
        return m_SceneComponentList;
    }

    CComponent* FindComponent(const std::string& Name);

    template <typename T>
    T* FindComponentFromType()  const
    {
        auto    iter = m_SceneComponentList.begin();
        auto    iterEnd = m_SceneComponentList.end();

        for (; iter != iterEnd; ++iter)
        {
            if ((*iter)->CheckTypeID<T>())
                return (T*)*iter;
        }

        auto    iter1 = m_vecObjectComponent.begin();
        auto    iter1End = m_vecObjectComponent.end();

        for (; iter1 != iter1End; ++iter1)
        {
            if ((*iter1)->CheckTypeID<T>())
                return (T*)(*iter1).Get();
        }

        return nullptr;
    }


public:
    void Start();
    bool Init();
    void Update(float DeltaTime);
    void PostUpdate(float DeltaTime);
    CGameObject* Clone()    const;


public:
    template <typename T>
    T* CreateComponent(const std::string& Name)
    {
        T* Component = new T;

        Component->SetName(Name);
        Component->SetScene(m_Scene);
        Component->SetOwner(this);

        if(!Component->Init())
        {
            SAFE_RELEASE(Component);
            return nullptr;
        }

        if (Component->GetComponentType() == ComponentType::Object)
        {
            m_vecObjectComponent.push_back((CObjectComponent*)Component);
        }

        else
        {
            m_SceneComponentList.push_back((CObjectComponent*)Component);

            if (!m_RootComponent)
                m_RootComponent = Component;
        }

        return Component;
    }
};

