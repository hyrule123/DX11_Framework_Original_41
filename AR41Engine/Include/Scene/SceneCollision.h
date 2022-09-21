#pragma once

#include "../EngineInfo.h"

struct Section2D
{
	std::vector<class CCollisionSection2D*>	vecSection;
	int		CountX;
	int		CountY;
	int		Count;
	Vector2	WorldStart;
	Vector2	SectionSize;
	Vector2	WorldSize;
};

struct Section3D
{
	std::vector<class CCollisionSection3D*>	vecSection;
	int		CountX;
	int		CountY;
	int		CountZ;
	int		Count;
	Vector3	WorldStart;
	Vector3	SectionSize;
	Vector3	WorldSize;
};

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_Owner;
	Section2D	m_Section2D;
	Section3D	m_Section3D;
	std::list<CSharedPtr<class CCollider>>	m_ColliderList;

public:
	void AddCollider(class CCollider* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
	void CreateSection2D(int CountX, int CountY, const Vector2& WorldStart,
		const Vector2& SectionSize);
	void CreateSection3D(int CountX, int CountY, int CountZ, const Vector3& WorldStart,
		const Vector3& SectionSize);
	void Save(FILE* File);
	void Load(FILE* File);

private:
	void CheckSection(class CCollider* Collider);
};

