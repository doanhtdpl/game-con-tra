#include "CQuadTree.h"
#include "CQuadObject.h"
#include "CFileUtil.h"

CQuadTree::CQuadTree()
{
	this->m_maxID = 0;
	this->m_nodeRoot = nullptr;
}

//Kiem tra neu doi tuong nao da die thi xoa no khoi quatree
void CQuadTree::ReBuildQuadTree(std::vector<CQuadObject*>& listQuadObj)
{
	if(!listQuadObj.empty())
	{
		int size = listQuadObj.size();
		CQuadObject* quadObj;
		for (int i = 0; i < size; i++)
		{
			quadObj = listQuadObj.at(i);
			if(quadObj)
			{
				if(!quadObj->GetGameObject()->IsAlive())
				{
					this->m_nodeRoot->DeleteObjectFromQuadNode(quadObj);
					delete listQuadObj.at(i);
					listQuadObj.erase(listQuadObj.begin() + i);
				}
			}
		}
	}
}

void CQuadTree::ReBuildQuadTree(const std::string& filePath)
{
	//Thong tin co ban cua mot node
	int iDNode;
	float posX;
	float posY;
	float width;
	float height;
	std::vector<int>* listIDObject;
	//Can mot bien con tro de giu node goc hien tai
	CQuadNode* rootCurr;
	//
	std::vector<std::string> result = CFileUtil::GetInstance()->LoadFromFile(filePath);
	int size = result.size();
	if(size > 0)
	{
		std::string line;
		std::vector<std::string> dataInfo;
		for (int i = 0; i < size; i++)
		{
			line = result.at(i);
			dataInfo = CFileUtil::GetInstance()->Split(line, '\t');
			if(!dataInfo.empty())
			{
				int size = dataInfo.size();
				iDNode = std::atoi(dataInfo.at(0).c_str());
				//Kiem tra neu iDNode khong phai la node cha
				if(!this->m_nodeRoot)
				{
					this->m_nodeRoot = new CQuadNode();
					this->m_nodeRoot->SetID(iDNode);
				}else
				{
					posX = std::atof(dataInfo.at(1).c_str());
					posY = std::atof(dataInfo.at(2).c_str());
					width =  std::atof(dataInfo.at(3).c_str());
					height = std::atof(dataInfo.at(4).c_str());
					if(size > 4)
					{
						listIDObject->clear();
						delete listIDObject;
						listIDObject = new std::vector<int>();
						for (int j = 5; j < size; j++)
						{
							listIDObject->push_back(std::atoi(dataInfo.at(i).c_str()));
						}
					}
					CQuadNode* node = new CQuadNode(iDNode, posX, posY, width, height);
					node->SetListObject(listIDObject);
					this->AddNode(node);
				}
			}
		}
	}
}

void CQuadTree::AddNode(CQuadNode*& node)
{
	if(node != this->m_nodeRoot)
	{
		//Tim node cha cua no, neu node cha chua duoc tao thi khoi tao
		int IDParent = node->GetID() / 8;
		if(IDParent < this->m_nodeRoot->GetID())
		{
			CQuadNode* nodeParent = this->m_nodeRoot;
			this->m_nodeRoot = new CQuadNode();
			this->m_nodeRoot->SetID(IDParent);
			delete nodeParent;
		}else //Neu no khong phai node cha
		{
			CQuadNode* nodeParent = this->SearchNode(IDParent, this->m_nodeRoot);
			if(nodeParent)
			{
				switch(node->GetID() % 8)
				{
				case 1:
					{
						nodeParent->SetNodeTL(node);
						break;
					}
				case 2:
					{
						nodeParent->SetNodeTR(node);
						break;
					}
				case 3:
					{
						nodeParent->SetNodeBL(node);
						break;
					}
				case 4:
					{
						nodeParent->SetNodeBR(node);
						break;
					}
				}
			}
		}
	}
}

//Xen viewPort
std::vector<int> CQuadTree::GetListObjectOnScreen(RECT*& viewBox, CQuadNode*& node)
{
	std::vector<int> listIDObj;
	if(viewBox && node)
	{
		if(this->m_nodeRoot->IntersectRect(viewBox, node->GetBox()))
		{
			if(this->m_nodeRoot->GetNodeTL())
			{
				this->GetListObjectOnScreen(viewBox, node->GetNodeTL());
				this->GetListObjectOnScreen(viewBox, node->GetNodeTR());
				this->GetListObjectOnScreen(viewBox, node->GetNodeBL());
				this->GetListObjectOnScreen(viewBox, node->GetNodeBR());
			}else
			{
				std::vector<int>* listItem = node->GetListObject();
				if(listItem)
				{
					int size = listItem->size();
					int id;
					for (int i = 0; i < size; i++)
					{
						id = listItem->at(i);
						if(!this->Contains(id, listIDObj))
						{  
							listIDObj.push_back(id);
						}
					}
				}
			}
		}
	}
}

bool CQuadTree::Contains(int ID,const std::vector<int>& list)
{
	if(!list.empty())
	{
		int size = list.size();
		for (int i = 0; i < size; i++)
		{
			if(list.at(i) == ID)
			{
				return true;
			}
		}
	}
	return false;
}

//node: Node goc, co the node goc khong phai la root
CQuadNode*& CQuadTree::SearchNode(int iDNode, CQuadNode*& node)
{
	CQuadNode* result = nullptr;
	if(iDNode == node->GetID())
	{
		result = node;
	}
	if(node ->GetNodeTL())
	{
		this->SearchNode(iDNode, node->GetNodeTL());
		this->SearchNode(iDNode, node->GetNodeTR());
		this->SearchNode(iDNode, node->GetNodeBL());
		this->SearchNode(iDNode, node->GetNodeBR());
	}
	return result;
}

void CQuadTree::BuildQuadTree()
{

}

void CQuadTree::AddGameObjectToQuadTree(CGameObject*& gameObj)
{
	CQuadObject* quadObj = new CQuadObject(++this->m_maxID, gameObj);
	if(this->m_nodeRoot && gameObj)
	{
		this->m_nodeRoot->ClipObject(quadObj);
	}
}

CQuadTree::~CQuadTree()
{
	this->m_nodeRoot->~CQuadNode();
}