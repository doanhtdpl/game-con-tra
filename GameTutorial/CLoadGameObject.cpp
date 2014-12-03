#include "CLoadGameObject.h"
#include "CFileUtil.h"
#include "CCamera.h"
#include "CDrawObject.h"
#include "CFactoryDynamicObject.h"
#include "CFactoryStaticObject.h"

CLoadGameObject::CLoadGameObject()
{
	this->m_listGameObject = new std::hash_map<int, CGameObject*>();
	this->m_listQuadTree = new std::hash_map<int, CQuadTree*>();
	this->m_listInfoOfGameObject = new std::hash_map<int, std::hash_map<int, std::vector<int>>>();
	this->m_quadTree = new CQuadTree();
}

void CLoadGameObject::LoadReSourceFromFile()
{
	LoadQuadTreeFromFile(__QuadTree_Path__);
	LoadGameObjectFromFile(__Map_Path__);
}

void CLoadGameObject::LoadQuadTreeFromFile(const std::string& filePath)
{
	int mapID;
	std::string pathItem;
	typedef pair<int, CQuadTree*> Pair;
	std::vector<std::string> result = CFileUtil::GetInstance()->LoadFromFile(filePath); //Load tat ca cac duong dan tu nguon
	std::vector<std::string> item; //Lay tung item trong result
	for (int i = 0; i < result.size(); i++)
	{
		item = CFileUtil::GetInstance()->Split(result.at(i).c_str(), ',');
		mapID = atoi(item.at(0).c_str());
		pathItem = item.at(1).c_str();
		//Tao CTexture
		this->m_quadTree->ReBuildQuadTree(pathItem);
		this->m_listQuadTree->insert(Pair(mapID, this->m_quadTree));
	}
}

//Xen trong quadtree va khoi tao doi tuong
void CLoadGameObject::CreateObjectOnScreen()
{
	if(this->m_quadTree)
	{ 
		this->m_listIdObject.clear();
		this->m_quadTree->GetListObjectOnScreen(CCamera::GetInstance()->GetBound(), 
													this->m_quadTree->GetRoot(),
													m_listIdObject); 
		if(!m_listIdObject.empty())
		{
			int size = m_listIdObject.size();
			int id; //Id cua doi tuong trong map
			typedef pair<int, CGameObject*> Pair;
			std::vector<int> objectInfo;
			for (int i = 0; i < size; i++)
			{
				//Kiem tra da ton tai doi tuong do trong list chua
				id = m_listIdObject.at(i);
				if(this->m_listGameObject)
				{
					CGameObject* gameObj;
					if(this->m_listGameObject->size() != 0)
					{
						std::hash_map<int, CGameObject*>::iterator it = this->m_listGameObject->find(id);
						if(it == this->m_listGameObject->end())
						{
							//Neu chua ton tai doi tuong thi khoi tao doi tuong, roi add vao list
							//Can lay thong tin cua doi tuong do
							if(!this->m_listInfoCurr.empty())
							{
								objectInfo = this->m_listInfoCurr.find(id)->second;
								//Lop factory se tao doi tuong
								gameObj = this->CreateObject(objectInfo);
								this->m_listGameObject->insert(Pair(id, gameObj));
							}
						}
					}
					else
					{
						//Neu chua ton tai doi tuong thi khoi tao doi tuong, roi add vao list
						//Can lay thong tin cua doi tuong do
						if(!this->m_listInfoCurr.empty())
						{
							objectInfo = this->m_listInfoCurr.find(id)->second;
							//Lop factory se tao doi tuong
							gameObj = this->CreateObject(objectInfo);
							this->m_listGameObject->insert(Pair(id, gameObj));
						}
					}
				}
			}
		}
	}
}

CGameObject* CLoadGameObject::CreateObject(const std::vector<int>& info)
{
	if(!info.empty())
	{
		int idObj = info.at(0);
		int idTypeObj = idObj / 1000;
		switch (idTypeObj)
		{
		case 10: case 11: case 12:
			{
				return CFactoryDynamicObject::GetInstance()->CreateObject(info);
				break;
			}
		case 13: case 14:
			{
				return CFactoryStaticObject::GetInstance()->CreateObject(info);
				break;
			}
		default:
			break;
		}
	}
}

//Kiem tra neu doi tuong nao trong list ko ton tai trong man hinh thi xoa di
//Update lai cac doi tuong hien tai trong quadtree
//Neu doi tuong di chuyen duoc, thi xoa roi add lai
//Update lai trang thai cua doi tuong
void CLoadGameObject::UpdateQuadTree(float deltaTime)
{
	if(this->m_listGameObject)
	{
		CGameObject* gameObj;
		for (std::hash_map<int, CGameObject*>::iterator it = this->m_listGameObject->begin(); 
				it != this->m_listGameObject->end();
				++it)
		{
			it->second->Update(deltaTime);
			this->m_quadTree->DeleteGameObjectFromQuadTree(new CQuadObject(it->first, it->second));
			this->m_quadTree->AddGameObjectToQuadTree(new CQuadObject(it->first, it->second));
			typedef pair<int, vector<int>> Pair;
			//this->m_listInfoCurr->insert(Pair());
		}
	}
}

void CLoadGameObject::Draw()
{
	if(this->m_listGameObject)
	{
		for (std::hash_map<int, CGameObject*>::iterator it = this->m_listGameObject->begin(); 
				it != this->m_listGameObject->end();
				++it)
		{
			CGameObject* gameObj = it->second;
			if(gameObj->GetIDType() != 14)
			{
				CDrawObject::GetInstance()->Draw(gameObj);
			}
		}
	}
}

//
void CLoadGameObject::Update(float deltaTime)
{
	this->CreateObjectOnScreen();
	//this->UpdateQuadTree(deltaTime);
	//this->DeleteObjectOutScreen(deltaTime);
	//Update doi tuong
	//if(this->m_listGameObject)
	//{
	//	for (std::hash_map<int, CGameObject*>::iterator it = this->m_listGameObject->begin(); 
	//			it != this->m_listGameObject->end();
	//			++it)
	//	{
	//		CGameObject* gameObj = it->second;
	//		if(gameObj->GetIDType() != 14)
	//		{
	//			gameObj->Update(deltaTime);
	//		}
	//	}
	//}
}

void CLoadGameObject::LoadGameObjectFromFile(const std::string& filePath) 
{
	int mapID;
	std::string pathItem;
	typedef pair<int, std::hash_map<int, std::vector<int>>> Pair;
	std::vector<std::string> result = CFileUtil::GetInstance()->LoadFromFile(filePath); //Load tat ca cac duong dan tu nguon
	std::vector<std::string> item; //Lay tung item trong result
	std::vector<std::string> data; //Luu du lieu lay len tu mot file
	for (int i = 0; i < result.size(); i++)
	{
		item = CFileUtil::GetInstance()->Split(result.at(i).c_str(), ',');
		mapID = atoi(item.at(0).c_str());
		pathItem = item.at(1).c_str();
		//Load thong tin info
		std::hash_map<int, std::vector<int>> listInfo = this->LoadGameObjectInfo(pathItem);
		this->m_listInfoOfGameObject->insert(Pair(mapID, listInfo));
	}
}

std::hash_map<int, std::vector<int>> CLoadGameObject::LoadGameObjectInfo(const std::string& filePath)
{
	std::hash_map<int, std::vector<int>> listInfo;
	std::vector<std::string> data = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> item;
	typedef pair<int, std::vector<int>> Pair;
	if(!data.empty())
	{
		int size = data.size();
		int iDObjectInMap;
		for (int i = 0; i < size; i++)
		{
			std::vector<int> info;
			item = CFileUtil::GetInstance()->Split(data.at(i).c_str(), '\t');
			if(!item.empty())
			{
				int sizeItem = item.size();
				int temp;
				iDObjectInMap = atoi(item.at(0).c_str());
				for (int j = 1; j < sizeItem; j++)
				{
 					info.push_back(atoi(item.at(j).c_str()));
				}
				listInfo.insert(Pair(iDObjectInMap, info));
			}
			
		}
	}
	return listInfo;
}

void CLoadGameObject::ChangeMap(const int& idMap)
{
	if(this->m_listQuadTree)
	{
		this->m_quadTree = this->m_listQuadTree->find(idMap)->second;
	}
	if(this->m_listInfoOfGameObject)
	{
		this->m_listInfoCurr = this->m_listInfoOfGameObject->find(idMap)->second;
		std::hash_map<int, std::vector<int>>::iterator it = this->m_listInfoCurr.end();
		it--;
		this->m_quadTree->SetMaxID(it->first);
	}
}

CLoadGameObject::~CLoadGameObject()
{
	if(this->m_listGameObject)
		delete m_listGameObject;
	if(this->m_listInfoOfGameObject)
		delete m_listInfoOfGameObject;
	if(this->m_listQuadTree)
		delete m_listQuadTree;
}