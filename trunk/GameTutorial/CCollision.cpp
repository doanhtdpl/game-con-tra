#include "CCollision.h"
#include <algorithm>

CCollision::CCollision()
{

}

CCollision::~CCollision()
{

}

//Toa do truyen vao la toa do trung tam
//first.x, first.y là toa do tai diem trung tam cua box
float CCollision::SweptAABB(Box first, Box second, float& normalx, float& normaly, float deltaTime)
{
	float xInvEntry, yInvEntry;
    float xInvExit, yInvExit;

    // find the distance between the objects on the near and far sides for both x and y
    if (first.vx > 0.0f)
    {
		xInvEntry = (second.x - second.w/2) - (first.x + first.w/2);
        xInvExit = (second.x + second.w/2) - (first.x - first.w/2);
    }
    else 
    {
        xInvEntry = (second.x + second.w/2) - (first.x - first.w/2);
        xInvExit = (second.x - second.w/2) - (first.x + first.w/2);
    }

    if (first.vy > 0.0f)
    {
        yInvEntry = (first.y - first.h/2) - (second.y + second.h/2);
        yInvExit =  (first.y + first.h/2) - (second.y - second.h/2);
    }
    else
    {
        yInvEntry = (first.y + first.h/2) - (second.y - second.h/2);
        yInvExit = (first.y - first.h/2) - (second.y + second.h/2);
    }

	 // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
    float xEntry, yEntry;
    float xExit, yExit;

    if (first.vx == 0.0f)
    {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    }
    else
    {
		xEntry = xInvEntry / first.vx * deltaTime;
        xExit = xInvExit / first.vx * deltaTime;
    }

    if (first.vy == 0.0f)
    {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        yEntry = yInvEntry / first.vy * deltaTime;
        yExit = yInvExit / first.vy * deltaTime;
    }

	// find the earliest/latest times of collision
    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

	// if there was no collision
    if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
    {
        normalx = 0.0f;
        normaly = 0.0f;
        return 1.0f;
    }
	else // if there was a collision
    {        		
        // calculate normal of collided surface
        if (xEntry > yEntry)
        {
            if (xInvEntry < 0.0f)
            {
                normalx = 1.0f;
                normaly = 0.0f;
            }
	        else
            {
                normalx = -1.0f;
                normaly = 0.0f;
            }
        }
        else
        {
            if (yInvEntry < 0.0f)
            {
                normalx = 0.0f;
                normaly = 1.0f;
            }
	        else
            {
                normalx = 0.0f;
		        normaly = -1.0f;
            }
        }

        // return the time of collision
        return entryTime;
    }
}

Box CCollision::GetSweptBroadphaseBox(Box b, float deltaTime)
{
    Box broadphasebox;
    broadphasebox.x = b.vx > 0 ? (b.x - b.w/2) : (b.x - b.w/2) + b.vx * deltaTime;
    broadphasebox.y = b.vy > 0 ? (b.y - b.h/2) : (b.y - b.h/2) + b.vy * deltaTime;
    broadphasebox.w = b.vx > 0 ? b.vx * deltaTime + b.w : b.w - b.vx * deltaTime;
    broadphasebox.h = b.vy > 0 ? b.vy * deltaTime + b.h : b.h - b.vy * deltaTime;

    return broadphasebox;
}

bool CCollision::AABBCheck(Box first, Box second, float& moveX, float& moveY)
{
	float l = (second.x - second.w / 2) - (first.x + first.w / 2);
	float r = (second.x + second.w / 2) - (first.x - first.w / 2);
	float t = (second.y + second.h / 2) - (first.y - first.h / 2);
	float b = (second.y - second.h / 2) - (first.y + first.h / 2);
	//Khong va cham
	if(l > 0 || r < 0 || t < 0 || b > 0)
		return false;
	moveX = (abs(l) < r) ? l : r;
	moveY = (abs(b) < t) ? b : t;
	if(abs(moveX) < abs(moveY))
	{
		moveY = 0.0f;
	}
	else
	{
		moveX = 0.0f;
	}
	return true;
}

bool CCollision::AABBCheck(Box first, Box second)
{
    return !((first.x + first.w / 2 < second.x - second.w / 2)||
			(first.x - first.w / 2) > (second.x + second.w / 2) ||
			(first.y + first.h / 2) < (second.y - second.h / 2) || 
			(first.y - first.h / 2) > (second.y + second.h / 2));
}


float CCollision::Collision(CGameObject* objectA, CGameObject* objectB, float& normalx, float& normaly, float deltaTime)
{
	Box first = objectA->GetBox();
	Box second = objectB->GetBox();
	Box broadphaseBox = this->GetSweptBroadphaseBox(first, deltaTime);
	float collisiontime;
	if(this->AABBCheck(first, second))
	{
		return 0.0f;
	}
	if(this->AABBCheck(broadphaseBox, second))
	{
		collisiontime = CCollision::GetInstance()->SweptAABB(first, second, normalx, normaly, deltaTime);
		//first.x += first.vx * collisiontime;
		//first.y += first.vy * collisiontime;
		if (collisiontime < 1.0f && collisiontime > 0.0f)
		{
			if(collisiontime <= deltaTime)
			{
				return deltaTime; 
			}
			else
			{
				return collisiontime;
			}
			//CContra::GetInstance()->SetVelocityY(0);
		}
	}
	else
	{
		return 1.0f;
	}
}
