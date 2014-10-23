#ifndef __CLOAD_BACK_GROUND_H__
#define __CLOAD_BACK_GROUND_H__

#include "CGlobal.h"
#include "CSingleton.h"
#include "CTexture.h"
#include "CSprite.h"
#include <hash_map>
#include "CQuadTree.h"

#define __Level_Map__ "..\\Resource\\BackGround\\MapBackGround.csv"
#define __Level_Image__ "..\\Resource\\BackGround\\ImageBackGround.csv"
#define __Level_QuadTree__ "..\\Resource\\BackGround\\QuadTreeBackGround.csv"

class CLoadBackGround : public CSingleton<CLoadBackGround> 
{
	friend class CSingleton<CLoadBackGround>;
public:
	~CLoadBackGround();
	void LoadAllResourceFromFile();
	void ChangeBackGround(int idBackGround);
	void Draw(); //
protected:
	int m_idCurrent; //BackGround hien tai
	int** m_matrix; //Dung de luu lai ma tran
	int m_cols; //So cot ma tran
	int m_rows; //So dong ma tran
	int m_tileHeight; // Chieu rong cua tile
	int m_tileWidth; // Chieu dai cua tile
	int m_tileCols; //So luong tile tren chieu dai cua Image
	int m_tileRows; //So luong tile tren chieu rong cua Image
	CTexture* m_imageCurr; //Lay texture trong bo dem, can dung lop managertexture
	CSprite* m_drawImg; //Dung de ve anh len man hinh, can dung lop managerSprite
	CQuadTree* m_quadTree; // Luu quadtree hien tai
	std::hash_map<int, CQuadTree*>* m_listQuadTree; //Su dung de luu danh sach quadtree
	std::hash_map<int, CTexture*>* m_listBackGroundImage; //Su dung de luu tat ca cac tileMap Image
	std::hash_map<int, int**>* m_listBackGroundMatrix; //Su dung de luu tat ca cac tileMap Matrix
	void LoadAllTextureFromFile(std::string);
	void LoadAllQuadTreeFromFile(std::string);
	void LoadAllMatrixFromFile(std::string);
	bool InitMatrix();
	void LoadMatrix(std::string filePath);
	void DeleteMatrix();
	CLoadBackGround();
};

#endif // !__CLOAD_BACK_GROUND_H__
