

#include "ParticleComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/PArticle/Particle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Shader/ParticleConstantBuffer.h"
#include "../Resource/Shader/ParticleRenderShader.h"
#include "../Resource/Shader/ParticleUpdateShader.h"
#include "../Resource/Shader/StructuredBuffer.h"

CParticleComponent::CParticleComponent()
{
	SetTypeID<CParticleComponent>();

	m_ComponentTypeName = "ParticleComponent";

	SetRenderLayerName("Particle");

	m_SpawnTime = 0.f;
	m_SpawnCountMax = 100;
	m_CBuffer = nullptr;

	m_SpawnTimeMax = 0.01f;
}

CParticleComponent::CParticleComponent(const CParticleComponent& component) :
	CPrimitiveComponent(component)
{
	m_SpawnTime = 0.f;
	m_SpawnCountMax = component.m_SpawnCountMax;
	m_Particle = component.m_Particle;
	m_SpawnTimeMax = component.m_SpawnTimeMax;

	if (m_Particle)
	{
		m_Particle->CloneStructuredBuffer(m_vecStructuredBuffer);

		m_CBuffer = m_Particle->CloneCBuffer();
	}
}

CParticleComponent::~CParticleComponent()
{
	size_t	Count = m_vecStructuredBuffer.size();

	for (size_t i = 0; i < Count; ++i)
	{
		SAFE_DELETE(m_vecStructuredBuffer[i]);
	}

	SAFE_DELETE(m_CBuffer);
}

void CParticleComponent::SetPawnTime(float Time)
{
	m_SpawnTimeMax = Time;
}

void CParticleComponent::SetSpawnCountMax(int Count)
{
	if (m_CBuffer)
		m_CBuffer->SetParticleSpawnCountMax(Count);

	m_SpawnCountMax = Count;

	m_vecStructuredBuffer[0]->Init("ParticleInfo", sizeof(ParticleInfo),
		Count, 0);
}

void CParticleComponent::SetParticle(const std::string& Name)
{
	CParticle* Particle = nullptr;

	if (m_Scene)
		Particle = m_Scene->GetResource()->FindParticle(Name);

	else
		Particle = CResourceManager::GetInst()->FindParticle(Name);

	SetParticle(Particle);
}

void CParticleComponent::SetParticle(CParticle* Particle)
{
	m_Particle = Particle;

	if (m_Particle)
	{
		size_t	Count = m_vecStructuredBuffer.size();

		for (size_t i = 0; i < Count; ++i)
		{
			SAFE_DELETE(m_vecStructuredBuffer[i]);
		}

		SAFE_DELETE(m_CBuffer);

		m_Particle->CloneStructuredBuffer(m_vecStructuredBuffer);

		m_CBuffer = m_Particle->CloneCBuffer();

		m_SpawnTimeMax = m_Particle->m_SpawnTime;
		m_SpawnCountMax = m_Particle->m_CBuffer->m_BufferData.ParticleSpawnCountMax;
	}
}

void CParticleComponent::SetMaterial(int Slot, const std::string& Name)
{
	CPrimitiveComponent::SetMaterial(Slot, Name);
}

void CParticleComponent::SetMaterial(int Slot, CMaterial* Material)
{
	CPrimitiveComponent::SetMaterial(Slot, Material);
}

void CParticleComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_vecMaterial.empty() && m_Particle && m_Particle->m_Material)
		AddMaterial(m_Particle->m_Material);
}

bool CParticleComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("ParticlePoint");
	//SetRelativeScale(500.f, 500.f, 1.f);

	return true;
}

void CParticleComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	if (m_Particle)
	{
		m_SpawnTime += DeltaTime;

		if (m_SpawnTime >= m_SpawnTimeMax)
		{
			m_SpawnTime -= m_SpawnTimeMax;
			m_CBuffer->SetParticleEnable(true);
		}

		else
			m_CBuffer->SetParticleEnable(false);
	}
}

void CParticleComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);

	if (m_Particle)
	{
		Vector3	StartMin, StartMax;

		StartMin = GetWorldPos() + m_Particle->m_CBuffer->m_BufferData.ParticleStartMin;
		StartMax = GetWorldPos() + m_Particle->m_CBuffer->m_BufferData.ParticleStartMax;

		m_CBuffer->SetParticleStartMin(StartMin);
		m_CBuffer->SetParticleStartMax(StartMax);

		m_CBuffer->UpdateBuffer();

		size_t	Count = m_vecStructuredBuffer.size();

		for (size_t i = 0; i < Count; ++i)
		{
			m_vecStructuredBuffer[i]->SetShader();
		}

		unsigned int	GroupCount = m_CBuffer->m_BufferData.ParticleSpawnCountMax / 64 + 1;
		m_Particle->m_UpdateShader->Excute(GroupCount, 1, 1);

		for (size_t i = 0; i < Count; ++i)
		{
			m_vecStructuredBuffer[i]->ResetShader();
		}
	}
}

void CParticleComponent::Render()
{
	if (m_Particle)
	{
		CSceneComponent::Render();

		m_vecMaterial[0]->SetMaterial();

		size_t	Count = m_vecStructuredBuffer.size();

		for (size_t i = 0; i < Count; ++i)
		{
			m_vecStructuredBuffer[i]->SetShader(30 + (int)i, (int)EShaderBufferType::Geometry);
		}

		m_Particle->m_RenderShader->SetShader();

		m_Mesh->RenderInstancing(m_CBuffer->m_BufferData.ParticleSpawnCountMax);

		m_vecMaterial[0]->ResetMaterial();


		Count = m_vecStructuredBuffer.size();

		for (size_t i = 0; i < Count; ++i)
		{
			m_vecStructuredBuffer[i]->ResetShader(30 + (int)i, (int)EShaderBufferType::Geometry);
		}
	}
}

CParticleComponent* CParticleComponent::Clone() const
{
	return new CParticleComponent(*this);
}

void CParticleComponent::Save(FILE* File)
{
	CPrimitiveComponent::Save(File);
}

void CParticleComponent::Load(FILE* File)
{
	CPrimitiveComponent::Load(File);
}
