#ifndef __CLOADGAMEOBJECT_H__
#define __CLOADGAMEOBJECT_H__

#include "CGlobal.h"
#include "CGameObject.h"
#include "CQuadTree.h"
#include "CSingleton.h"

#define __Map_Path__ "..\\Resource\\File\\Map\\LevelMap.csv"
#define __QuadTree_Path__ "..\\Resource\\File\\Map\\LevelQuadTree.csv"

class CLoadGameObject : public CSingleton<CLoadGameObject> 
{
	friend class CSingleton<CLoadGameObject> ;
public:
	CLoadGameObject();
	~CLoadGameObject();
	std::hash_map<int, CGameObject*>* GetListGameObjectOnScreen(){return this->m_listGameObject;};
	void CreateObjectOnScreen();
	void Draw();
	void LoadReSourceFromFile();
	void Update();
	void ChangeMap(const int& );
protected:
	//Luu danh sach doi tuong khi xen viewport
	std::hash_map<int, CGameObject*>* m_listGameObject;
	std::hash_map<int, CQuadTree*>* m_listQuadTree;
	std::hash_map<int, std::hash_map<int, std::vector<int>>>* m_listInfoOfGameObject;
	std::vector<int> m_listIdObject;
	//Luu quad tree hien tai
	CQuadTree* m_quadTree;
	std::hash_map<int, std::vector<int>> m_listInfoCurr;
	void LoadQuadTreeFromFile(const std::string&);
	void LoadGameObjectFromFile(const std::string&);
	void DeleteObjectOutScreen();
	CGameObject* CreateObject(const std::vector<int>&);
	std::hash_map<int, std::vector<int>> LoadGameObjectInfo(const std::string&);

};

#endif // !__CLOADGAMEOBJECT_H__
