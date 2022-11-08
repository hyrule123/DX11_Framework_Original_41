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

bool CNavigation::FindPath(const Vector2& Start, const Vector2& End, 
	std::list<Vector2>& PathList)
{
	PathList.clear();

	int	StartIndex = m_TileMap->GetTileIndex(Start);

	if (StartIndex == -1)
		return false;

	int EndIndex = m_TileMap->GetTileIndex(End);

	if (EndIndex == -1)
		return false;

	NavNode* StartNode = m_vecUseNode[StartIndex];
	NavNode* EndNode = m_vecUseNode[EndIndex];

	if (EndNode->TileOption == ETileOption::Wall)
		return false;

	else if (EndNode == StartNode)
	{
		PathList.push_back(End);
		return true;
	}

	size_t Size = m_vecUseNode.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecUseNode[i]->NodeType = ENavNodeType::None;
		m_vecUseNode[i]->Cost = FLT_MAX;
		m_vecUseNode[i]->Dist = FLT_MAX;
		m_vecUseNode[i]->Total = FLT_MAX;
		m_vecUseNode[i]->Parent = nullptr;
		m_vecUseNode[i]->SearchDirList.clear();
	}

	m_vecUseNode.clear();

	StartNode->NodeType = ENavNodeType::Open;
	StartNode->Cost = 0.f;
	StartNode->Dist = StartNode->Center.Distance(End);
	StartNode->Total = StartNode->Dist;

	for (int i = 0; i < (int)ENodeDir::End; ++i)
	{
		StartNode->SearchDirList.push_back((ENodeDir)i);
	}

	m_vecOpen.push_back(StartNode);

	m_vecUseNode.push_back(StartNode);

	while (!m_vecOpen.empty())
	{
		// 열린 목록에서 노드를 가져온다.
		NavNode* Node = m_vecOpen.back();
		m_vecOpen.pop_back();

		Node->NodeType = ENavNodeType::Close;

		// 현재 노드가 검사해야할 방향의 타일을 검사하여 코너를 열린목록에 넣어준다.
		if (FindNode(Node, EndNode, End, PathList))
			break;

		// 열린 목록에 있는 노드를 비용이 큰 노드에서 작은 노드 순서로 정렬해준다.
		if (m_vecOpen.size() >= 2)
			std::sort(m_vecOpen.begin(), m_vecOpen.end(), CNavigation::SortNode);

	}

	return false;
}

bool CNavigation::FindNode(NavNode* Node, NavNode* EndNode, const Vector2& End, 
	std::list<Vector2>& PathList)
{
	auto	iter = Node->SearchDirList.begin();
	auto	iterEnd = Node->SearchDirList.end();

	for (; iter != iterEnd; ++iter)
	{
		NavNode* Corner = GetCorner(*iter, Node, EndNode, End);

		if (!Corner)
			continue;
	}

	return false;
}

NavNode* CNavigation::GetCorner(ENodeDir Dir, NavNode* Node, NavNode* EndNode,
	const Vector2& End)
{
	switch (m_Shape)
	{
	case ETileShape::Rect:
		switch (Dir)
		{
		case ENodeDir::T:
			return GetCornerRectTop(Node, EndNode);
		case ENodeDir::RT:
			return GetCornerRectRT(Node, EndNode);
		case ENodeDir::R:
			return GetCornerRectRight(Node, EndNode);
		case ENodeDir::RB:
			return GetCornerRectRB(Node, EndNode);
		case ENodeDir::B:
			return GetCornerRectBottom(Node, EndNode);
		case ENodeDir::LB:
			return GetCornerRectLB(Node, EndNode);
		case ENodeDir::L:
			return GetCornerRectLeft(Node, EndNode);
		case ENodeDir::LT:
			return GetCornerRectLT(Node, EndNode);
		}
		break;
	case ETileShape::Isometric:
		switch (Dir)
		{
		case ENodeDir::T:
			return GetCornerIsometricTop(Node, EndNode);
		case ENodeDir::RT:
			return GetCornerIsometricRT(Node, EndNode);
		case ENodeDir::R:
			return GetCornerIsometricRight(Node, EndNode);
		case ENodeDir::RB:
			return GetCornerIsometricRB(Node, EndNode);
		case ENodeDir::B:
			return GetCornerIsometricBottom(Node, EndNode);
		case ENodeDir::LB:
			return GetCornerIsometricLB(Node, EndNode);
		case ENodeDir::L:
			return GetCornerIsometricLeft(Node, EndNode);
		case ENodeDir::LT:
			return GetCornerIsometricLT(Node, EndNode);
		}
		break;
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectTop(NavNode* Node, NavNode* EndNode)
{
	// 한칸씩 위로 올라가며 오른쪽이 막혀있고 오른쪽 위가 뚫려있을 경우나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;

	while (true)
	{
		++IndexY;

		if (IndexY >= m_CountY)
			return nullptr;

		NavNode* CornerNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CornerNode == EndNode)
			return CornerNode;

		else if (CornerNode->NodeType == ENavNodeType::Close)
			return nullptr;

		else if (CornerNode->TileOption == ETileOption::Wall)
			return nullptr;

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX && CornerY + 1 < m_CountY)
		{
			// 오른쪽이 벽이고 오른쪽 위가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileOption == ETileOption::None)
				return CornerNode;
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0 && CornerY + 1 < m_CountY)
		{
			// 왼쪽이 벽이고 왼쪽 위가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileOption == ETileOption::None)
				return CornerNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectBottom(NavNode* Node, NavNode* EndNode)
{
	// 한칸씩 아래로 내려가며 오른쪽이 막혀있고 오른쪽 아래가 뚫려있을 경우나
	// 왼쪽이 막혀있고 왼쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;

	while (true)
	{
		--IndexY;

		if (IndexY < 0)
			return nullptr;

		NavNode* CornerNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CornerNode == EndNode)
			return CornerNode;

		else if (CornerNode->NodeType == ENavNodeType::Close)
			return nullptr;

		else if (CornerNode->TileOption == ETileOption::Wall)
			return nullptr;

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX && CornerY - 1 >= 0)
		{
			// 오른쪽이 벽이고 오른쪽 아래가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileOption == ETileOption::None)
				return CornerNode;
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0 && CornerY - 1 >= 0)
		{
			// 왼쪽이 벽이고 왼쪽 아래가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileOption == ETileOption::None)
				return CornerNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectLeft(NavNode* Node, NavNode* EndNode)
{
	// 한칸씩 왼쪽으로 가며 위가 막혀있고 왼쪽 위가 뚫려있을 경우나
	// 아래가 막혀있고 왼쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexX = Node->IndexX;

	while (true)
	{
		--IndexX;

		if (IndexX < 0)
			return nullptr;

		NavNode* CornerNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CornerNode == EndNode)
			return CornerNode;

		else if (CornerNode->NodeType == ENavNodeType::Close)
			return nullptr;

		else if (CornerNode->TileOption == ETileOption::Wall)
			return nullptr;

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerX - 1 >= 0 && CornerY < m_CountY)
		{
			// 위쪽이 벽이고 왼쪽 위가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileOption == ETileOption::None)
				return CornerNode;
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerX - 1 >= 0 && CornerY >= 0)
		{
			// 아래쪽이 벽이고 왼쪽 아래가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileOption == ETileOption::None)
				return CornerNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectRight(NavNode* Node, NavNode* EndNode)
{
	// 한칸씩 오른쪽으로 가며 위가 막혀있고 오른쪽 위가 뚫려있을 경우나
	// 아래가 막혀있고 오른쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexX = Node->IndexX;

	while (true)
	{
		++IndexX;

		if (IndexX >= m_CountX)
			return nullptr;

		NavNode* CornerNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CornerNode == EndNode)
			return CornerNode;

		else if (CornerNode->NodeType == ENavNodeType::Close)
			return nullptr;

		else if (CornerNode->TileOption == ETileOption::Wall)
			return nullptr;

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerX + 1 < m_CountX && CornerY < m_CountY)
		{
			// 위쪽이 벽이고 오른쪽 위가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileOption == ETileOption::None)
				return CornerNode;
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerX + 1 < m_CountX && CornerY >= 0)
		{
			// 아래쪽이 벽이고 오른쪽 아래가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileOption == ETileOption::None)
				return CornerNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectLT(NavNode* Node, NavNode* EndNode)
{
	// 한칸씩 왼쪽 위로 가며 오른쪽이 막혀있고 오른쪽 위가 뚫려있을 경우나
	// 아래가 막혀있고 왼쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexX = Node->IndexX;
	int	IndexY = Node->IndexY;

	while (true)
	{
		--IndexX;
		++IndexY;

		if (IndexX < 0 || IndexY >= m_CountY)
			return nullptr;

		NavNode* CornerNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CornerNode == EndNode)
			return CornerNode;

		else if (CornerNode->NodeType == ENavNodeType::Close)
			return nullptr;

		else if (CornerNode->TileOption == ETileOption::Wall)
			return nullptr;

		int	CornerX = IndexX;
		int	CornerY = IndexY - 1;

		if (CornerX - 1 >= 0 && CornerY >= 0)
		{
			// 아래쪽이 벽이고 왼쪽 아래가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileOption == ETileOption::None)
				return CornerNode;
		}

		CornerX = IndexX + 1;
		CornerY = IndexY;

		if (CornerX < m_CountX && CornerY + 1 < m_CountY)
		{
			// 오른쪽이 벽이고 오른쪽 위가 일반일 경우
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileOption == ETileOption::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileOption == ETileOption::None)
				return CornerNode;
		}

		// 대각선 코너가 아니라면 왼쪽 위로 진행이 되므로 왼쪽, 그리고 위쪽으로
		// 코너가 있는지를 판단하여 코너가 있다면 현재 노드를 코너드로 판단하도록
		// 한다.
		NavNode* Find = GetCornerRectTop(CornerNode, EndNode);
		
		// 위쪽으로 검사하던 중 코너가 있다면 이 노드를 코너로 인식한다.
		if (Find)
			return CornerNode;

		Find = GetCornerRectLeft(CornerNode, EndNode);

		if (Find)
			return CornerNode;
	}

	return nullptr;
}

NavNode* CNavigation::GetCornerRectRT(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerRectLB(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerRectRB(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricTop(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricBottom(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricLeft(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricRight(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricLT(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricRT(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricLB(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

NavNode* CNavigation::GetCornerIsometricRB(NavNode* Node, NavNode* EndNode)
{
	return nullptr;
}

bool CNavigation::SortNode(NavNode* Src, NavNode* Dest)
{
	return Src->Total > Dest->Total;
}
