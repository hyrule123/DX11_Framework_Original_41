#pragma once

#include "../EngineInfo.h"

class CTile
{
	friend class CTileMapComponent;

private:
	CTile();
	CTile(const CTile& Tile);
	~CTile();

private:
	bool		m_Enable;
	class CTileMapComponent* m_Owner;
	ETileOption		m_TileOption;
	Vector3			m_Pos;
	Vector3			m_Size;
	Vector3			m_Center;
	Matrix			m_matWorld;
	int				m_IndexX;
	int				m_IndexY;
	int				m_Index;
	std::vector<Animation2DFrameData>   m_vecFrameData;
	EAnimation2DType    m_Anim2DType;
	int					m_Frame;
	float				m_Time;
	float				m_FrameTime;
	float				m_PlayTime;
	float				m_PlayScale;
	bool				m_Loop;
	bool				m_Reverse;
	float				m_Opacity;

public:
	bool GetEnable()	const
	{
		return m_Enable;
	}

	float GetOpacity()	const
	{
		return m_Opacity;
	}

	ETileOption GetTileOption()	const
	{
		return m_TileOption;
	}

	const Vector3& GetPos()	const
	{
		return m_Pos;
	}

	const Vector3& GetCenter()	const
	{
		return m_Center;
	}

	const Matrix& GetWorldMatrix()	const
	{
		return m_matWorld;
	}

	int GetIndexX()	const
	{
		return m_IndexX;
	}

	int GetIndexY()	const
	{
		return m_IndexY;
	}

	int GetIndex()	const
	{
		return m_Index;
	}

public:
	void Update(float DeltaTime);
	CTile* Clone();
};

