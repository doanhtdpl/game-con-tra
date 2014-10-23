#include "CLoadBackGround.h"
#include "CFileUtil.h"
#include "CCamera.h"

CLoadBackGround::CLoadBackGround()
{
	this->m_listBackGroundImage = new std::hash_map<int, CTexture*>();
	this->m_listBackGroundMatrix = new std::hash_map<int, int**>();
	this->m_listQuadTree = new std::hash_map<int, CQuadTree*>();
	this->m_imageCurr = new CTexture();
	this->m_drawImg = new CSprite();
	this->m_quadTree = new CQuadTree();
	this->m_matrix = nullptr;
	this->m_cols = 0;
	this->m_rows = 0;
	this->m_idCurrent = 10;
}

CLoadBackGround::~CLoadBackGround()
{
	this->DeleteMatrix();
}

void CLoadBackGround::Draw()
{
	RECT rectRS;
	D3DXVECTOR3 pos;
	if(this->m_listBackGroundMatrix)
		this->m_matrix = this->m_listBackGroundMatrix->find(this->m_idCurrent)->second;
	if(this->m_matrix != nullptr)
	{
		std::vector<int> listIDObj;
		this->m_quadTree->GetListObjectOnScreen(
																				CCamera::GetInstance()->GetBox(),
																				this->m_quadTree->GetRoot(),
																				listIDObj
																			);
		if(!listIDObj.empty())
		{
			int size = listIDObj.size();
			int row;
			int col;
			for (int i = 0; i < size; i++)
			{
				row = listIDObj.at(i) / this->m_cols;
				col = listIDObj.at(i) % this->m_cols;
				//Ve tung tile len man hinh
				rectRS.left = (this->m_matrix[row][col] % this->m_tileCols) * this->m_tileWidth;
				rectRS.right = rectRS.left + this->m_tileWidth;
				rectRS.top = (this->m_matrix[row][col] / this->m_tileCols) * this->m_tileHeight;
				rectRS.bottom = rectRS.top + this->m_tileHeight;
				pos.x = col * this->m_tileHeight;
				pos.y = (this->m_rows - row) * this->m_tileWidth;
				pos.z = 0;
				pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
				this->m_drawImg->draw(this->m_imageCurr, &rectRS, pos, D3DCOLOR_XRGB(255,255,225), false);
			}
		}
		//for (int i = 0; i < this->m_rows; i++)
		//{
		//	for (int j = 0; j < this->m_cols; j++)
		//	{
		//		//Ve tung tile len man hinh
		//		rectRS.left = (this->m_matrix[i][j] % this->m_tileCols) * this->m_tileWidth;
		//		rectRS.right = rectRS.left + this->m_tileWidth;
		//		rectRS.top = (this->m_matrix[i][j] / this->m_tileCols) * this->m_tileHeight;
		//		rectRS.bottom = rectRS.top + this->m_tileHeight;
		//		pos.x = j * this->m_tileHeight;
		//		pos.y = (this->m_rows - i) * this->m_tileWidth;
		//		pos.z = 0;
		//		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		//		this->m_drawImg->draw(this->m_imageCurr, &rectRS, pos, D3DCOLOR_XRGB(255,255,225), false);
		//	}
		//}
	}
}

void CLoadBackGround::LoadAllResourceFromFile()
{
	LoadAllTextureFromFile(__Level_Image__);
	LoadAllMatrixFromFile(__Level_Map__);
	LoadAllQuadTreeFromFile(__Level_QuadTree__);
}

void CLoadBackGround::LoadAllTextureFromFile(std::string filePath)
{
	int mapID;
	std::string pathItem;
	typedef pair<int, CTexture*> Pair;
	std::vector<std::string> result = CFileUtil::GetInstance()->LoadFromFile(filePath); //Load tat ca cac duong dan tu nguon
	std::vector<std::string> item; //Lay tung item trong result
	for (int i = 0; i < result.size(); i++)
	{
		item = CFileUtil::GetInstance()->Split(result.at(i).c_str(), ',');
		mapID = atoi(item.at(0).c_str());
		pathItem = item.at(1).c_str();
		//Tao CTexture
		m_imageCurr = new CTexture();
		if((m_imageCurr->LoadImageFromFile(pathItem, NULL)));
		{
			this->m_listBackGroundImage->insert(Pair(mapID, m_imageCurr));
		}
	}
}

void CLoadBackGround::LoadAllMatrixFromFile(std::string filePath)
{
	int mapID;
	std::string pathItem;
	typedef pair<int, int**> Pair;
	std::vector<std::string> result = CFileUtil::GetInstance()->LoadFromFile(filePath); //Load tat ca cac duong dan tu nguon
	std::vector<std::string> item; //Lay tung item trong result
	for (int i = 0; i < result.size(); i++)
	{
		item = CFileUtil::GetInstance()->Split(result.at(i).c_str(), ',');
		mapID = atoi(item.at(0).c_str());
		pathItem = item.at(1).c_str();
		//Tao CTexture
		this->LoadMatrix(pathItem);
		this->m_listBackGroundMatrix->insert(Pair(mapID, this->m_matrix));
	}
}

//Load tat ca cac QuadTree tu file
void CLoadBackGround::LoadAllQuadTreeFromFile(std::string filePath)
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

void CLoadBackGround::ChangeBackGround(int idBackGround)
{
	//this->LoadMatrix(filePath); //Load lai noi dung cua matrix
	this->m_idCurrent = idBackGround;
	if(this->m_listBackGroundImage != nullptr)
	{
		this->m_imageCurr = this->m_listBackGroundImage->find(idBackGround)->second;
		if(this->m_imageCurr)
		{
			this->m_tileCols = this->m_imageCurr->GetImageWidth() / this->m_tileWidth;
			this->m_tileRows = this->m_imageCurr->GetImageHeight() / this->m_tileHeight;
		}
	}
	if(this->m_listQuadTree)
	{
		this->m_quadTree = this->m_listQuadTree->find(idBackGround)->second;
	}
}

bool CLoadBackGround::InitMatrix()
{
	if(this->m_cols != 0 && this->m_rows != 0)
	{
		this->m_matrix = new int*[this->m_rows];
		for (int i = 0; i < this->m_rows; i++)
		{
			this->m_matrix[i] = new int[this->m_cols]; 
		}
		return true;
	}
	return false;
}

void CLoadBackGround::LoadMatrix(std::string filePath)
{
	this->DeleteMatrix();
	std::vector<std::string> value = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> result; //Luu chuoi sau khi duoc cat
	for (int i = 0; i < value.size(); i++)
	{
		result = CFileUtil::GetInstance()->Split(value.at(i).c_str(), '\t');
		if(i == 0)
		{
			this->m_rows = std::atoi(result.at(0).c_str());
			this->m_cols = std::atoi(result.at(1).c_str());
			this->InitMatrix();
		}else if(i == 1)
		{
			this->m_tileWidth = std::atoi(result.at(0).c_str());
			this->m_tileHeight = std::atoi(result.at(1).c_str());
		}else
		{
			for (int j = 0; j < result.size(); j++)
			{
				this->m_matrix[i-2][j] = atoi(result.at(j).c_str());
			}
		}
	}
}

void CLoadBackGround::DeleteMatrix()
{
	if(this->m_matrix != nullptr)
	{
		for (int i = 0; i < this->m_rows; i++)
		{
			delete this->m_matrix[i];
		}
		delete this->m_matrix;
	}
}