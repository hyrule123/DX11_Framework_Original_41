#pragma once

#include "../Component/TileMapComponent.h"

enum class ENodeDir
{
	T,
	RT,
	R,
	RB,
	B,
	LB,
	L,
	LT,
	End
};

enum class ENavNodeType
{
	None,
	Open,
	Close
};

struct NavNode
{
	NavNode*		Parent;
	ENavNodeType	NodeType;
	ETileOption		TileOption;
	Vector2			Pos;
	Vector2			Size;
	Vector2			Center;
	int				IndexX;
	int				IndexY;
	int				Index;
	float			Cost;
	float			Dist;
	float			Total;
	std::list<ENodeDir>	SearchDirList;

	NavNode()	:
		Parent(nullptr),
		NodeType(ENavNodeType::None),
		TileOption(ETileOption::None),
		IndexX(-1),
		IndexY(-1),
		Index(-1),
		Cost(FLT_MAX),
		Dist(FLT_MAX),
		Total(FLT_MAX)
	{
	}
};

class CNavigation
{
	friend class CNavigationThread;

private:
	CNavigation();
	~CNavigation();

private:
	ETileShape	m_Shape;
	std::vector<NavNode*>	m_vecNode;
	int		m_CountX;
	int		m_CountY;
	Vector2	m_TileSize;
	CSharedPtr<class CTileMapComponent>	m_TileMap;
	std::vector<NavNode*>			m_vecOpen;
	std::vector<NavNode*>			m_vecUseNode;

public:
	void CreateNavigation(class CTileMapComponent* TileMap);
};

