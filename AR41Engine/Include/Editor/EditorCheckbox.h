#pragma once
#include "EditorWidget.h"

class CEditorCheckbox :
    public CEditorWidget
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CEditorCheckbox();
    virtual ~CEditorCheckbox();

private:
    bool m_ReadOnly;
    bool m_Checked;
    std::function<void(bool&)> m_CheckCallbackFunc;

public:
    virtual bool Init();
    virtual void Render();

public:
    inline void SetReadOnly(const bool& B);
    inline void SetChecked(const bool& B);

    template <typename T>
    void SetCheckCallbackFunc(T* Obj, void(T::* func)(bool&));
};


template <typename T>
inline void CEditorCheckbox::SetCheckCallbackFunc(T* Obj, void(T::* func)(bool&))
{
    m_CheckCallbackFunc = std::bind(func, Obj, std::placeholders::_1);
} 

inline void CEditorCheckbox::SetReadOnly(const bool& B)
{
    m_ReadOnly = B;
}

inline void CEditorCheckbox::SetChecked(const bool& B)
{
    m_Checked = B;
}