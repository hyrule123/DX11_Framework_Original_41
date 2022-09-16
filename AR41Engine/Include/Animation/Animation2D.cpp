#include "Animation2D.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"

std::unordered_map<std::string, CAnimation2D*> CAnimation2D::m_mapAnimationCDO;

CAnimation2D::CAnimation2D()	:
	m_Owner(nullptr)
{
	m_ClassName = "Animation2D";
}

CAnimation2D::CAnimation2D(const CAnimation2D& Anim)	:
	CRef(Anim)
{
	m_mapAnimation.clear();

	auto	iter = Anim.m_mapAnimation.begin();
	auto	iterEnd = Anim.m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		CAnimation2DData* Data = iter->second->Clone();

		if (Data->GetName() == Anim.m_CurAnimation->GetName())
		{
			m_CurAnimation = Data;
		}
	}
}

CAnimation2D::~CAnimation2D()
{
	auto	iter = m_mapAnimation.begin();
	auto	iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CAnimation2D::Init()
{
	return true;
}

void CAnimation2D::Update(float DeltaTime)
{

}

bool CAnimation2D::AddAnimation(const std::string& Name, 
	const std::string& SequenceName, float PlayTime, float PlayScale, 
	bool Loop, bool Reverse)
{
	CAnimation2DData* Anim = FindAnimation(Name);

	if (Anim)
		return false;

	CAnimationSequence2D* Sequence = nullptr;

	if (m_Owner->GetScene())
		Sequence = m_Owner->GetScene()->GetResource()->FindAnimationSequence2D(SequenceName);

	else
		Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);

	Anim = new CAnimation2DData;

	Anim->m_Sequence = Sequence;
	Anim->m_SequenceName = SequenceName;
	Anim->m_Name = Name;
	Anim->m_PlayTime = PlayTime;
	Anim->m_PlayScale = PlayScale;
	Anim->m_Loop = Loop;
	Anim->m_Reverse = Reverse;
	Anim->m_FrameTime = PlayTime / Sequence->GetFrameCount();

	if (m_mapAnimation.empty())
	{
		m_CurAnimation = Anim;

		if (m_Owner)
		{
			m_Owner->SetTexture(m_CurAnimation->m_Sequence->GetTexture());
		}
	}

	m_mapAnimation.insert(std::make_pair(Name, Anim));

	return true;
}

bool CAnimation2D::AddAnimation(const std::string& Name, 
	CAnimationSequence2D* Sequence,
	float PlayTime, float PlayScale, bool Loop, bool Reverse)
{
	CAnimation2DData* Anim = FindAnimation(Name);

	if (Anim)
		return false;

	Anim = new CAnimation2DData;

	Anim->m_Sequence = Sequence;
	Anim->m_SequenceName = Sequence->GetName();
	Anim->m_Name = Name;
	Anim->m_PlayTime = PlayTime;
	Anim->m_PlayScale = PlayScale;
	Anim->m_Loop = Loop;
	Anim->m_Reverse = Reverse;
	Anim->m_FrameTime = PlayTime / Sequence->GetFrameCount();

	if (m_mapAnimation.empty())
	{
		m_CurAnimation = Anim;

		if (m_Owner)
		{
			m_Owner->SetTexture(m_CurAnimation->m_Sequence->GetTexture());
		}
	}

	m_mapAnimation.insert(std::make_pair(Name, Anim));

	return true;
}

void CAnimation2D::SetPlayTime(const std::string& Name, float PlayTime)
{
}

void CAnimation2D::SetPlayScale(const std::string& Name, float PlayTime)
{
}

void CAnimation2D::SetLoop(const std::string& Name, bool Loop)
{
}

void CAnimation2D::SetReverse(const std::string& Name, bool Reverse)
{
}

void CAnimation2D::SetCurrentAnimation(const std::string& Name)
{
	CAnimation2DData* Anim = FindAnimation(Name);

	if (!Anim)
		return;

	m_CurAnimation = Anim;

	m_CurAnimation->m_Frame = 0;
	m_CurAnimation->m_Time = 0.f;

	size_t	Size = m_CurAnimation->m_vecNotify.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_CurAnimation->m_vecNotify[i]->Call = false;
	}

	if (m_Owner)
	{
		m_Owner->SetTexture(m_CurAnimation->m_Sequence->GetTexture());
	}
}

void CAnimation2D::ChangeAnimation(const std::string& Name)
{
	if (m_CurAnimation->GetName() == Name)
		return;

	m_CurAnimation->m_Frame = 0;
	m_CurAnimation->m_Time = 0.f;

	size_t	Size = m_CurAnimation->m_vecNotify.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_CurAnimation->m_vecNotify[i]->Call = false;
	}

	m_CurAnimation = FindAnimation(Name);

	m_CurAnimation->m_Frame = 0;
	m_CurAnimation->m_Time = 0.f;

	if (m_Owner)
	{
		m_Owner->SetTexture(m_CurAnimation->m_Sequence->GetTexture());
	}
}

void CAnimation2D::Save(FILE* File)
{
	CRef::Save(File);

	int	Count = (int)m_mapAnimation.size();

	fwrite(&Count, 4, 1, File);

	auto	iter = m_mapAnimation.begin();
	auto	iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Save(File);
	}

	int	Length = (int)m_CurAnimation->GetName().length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_CurAnimation->GetName().c_str(), 1, Length, File);
}

void CAnimation2D::Load(FILE* File)
{
	CRef::Load(File);

	auto	iter = m_mapAnimation.begin();
	auto	iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_mapAnimation.clear();

	m_CurAnimation = nullptr;


	int	Count = 0;

	fread(&Count, 4, 1, File);

	for (int i = 0; i < Count; ++i)
	{
		CAnimation2DData* Data = new CAnimation2DData;

		Data->Load(File);

		m_mapAnimation.insert(std::make_pair(Data->GetName(), Data));
	}

	int	Length = 0;
	char	CurName[256] = {};

	fread(&Length, 4, 1, File);
	fread(CurName, 1, Length, File);

	m_CurAnimation = FindAnimation(CurName);
}

CAnimation2D* CAnimation2D::Clone()
{
	return new CAnimation2D(*this);
}

CAnimation2DData* CAnimation2D::FindAnimation(const std::string& Name)
{
	auto	iter = m_mapAnimation.find(Name);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}
