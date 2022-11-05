#include "Navigation.h"
#include "../Component/TileMapComponent.h"

CNavigation::CNavigation()
{
}

CNavigation::~CNavigation()
{
	size_t	Size = m_vecNode.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecNode[i]);
	}
}

void CNavigation::CreateNavigation(CTileMapComponent* TileMap)
{
	m_TileMap = TileMap;

	m_Shape = m_TileMap->GetShape();
	m_CountX = m_TileMap->GetCountX();
	m_CountY = m_TileMap->GetCountY();

	m_TileSize = m_TileMap->GetTileSize();

	int	Count = m_CountX * m_CountY;

	for (int i = 0; i < Count; ++i)
	{
		NavNode* Node = new NavNode;

		Node->TileOption = m_TileMap->GetTile(i)->GetTileOption();
		Node->Pos = m_TileMap->GetTile(i)->GetPos();
		Node->Size = m_TileMap->GetTileSize();
		Node->Center = Node->Pos + Node->Size * 0.5f;
		Node->IndexX = m_TileMap->GetTile(i)->GetIndexX();
		Node->IndexY = m_TileMap->GetTile(i)->GetIndexY();
		Node->Index = m_TileMap->GetTile(i)->GetIndex();

		m_vecNode.push_back(Node);
	}
}
