#include "Tile.h"

CTile::CTile()	:
	m_Owner(nullptr),
	m_Enable(true),
	m_TileOption(ETileOption::None),
	m_IndexX(0),
	m_IndexY(0),
	m_Index(0),
	m_Anim2DType(EAnimation2DType::Atlas),
	m_Frame(0),
	m_Time(0.f),
	m_FrameTime(0.f),
	m_PlayTime(1.f),
	m_PlayScale(1.f),
	m_Loop(true),
	m_Reverse(false),
	m_Opacity(1.f)
{
}

CTile::CTile(const CTile& Tile)
{
	*this = Tile;

	m_Owner = nullptr;
}

CTile::~CTile()
{
}
