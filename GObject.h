#pragma once

#include <time.h>
#include "GMap.h"
#include <memory>
#define PLAYERSPEED 6	// 玩家速度
#define ENERMYSPEED 4	// 敌人速度
#define LEGCOUNTS 5		// 敌人腿的数量
#define DISTANCE 10		// 图形范围
#define BLUE_ALERT 8    // 蓝色警戒范围
#define D_OFFSET 2		// 绘图误差
#define RD (DISTANCE + D_OFFSET) //绘图范围

enum TWARDS
{//  上下左右 游戏结束
	UP,
	DOWN,
	LEFT,
	RIGHT,
	OVER,
};


class GObject
{
public:
	GObject(int Row, int Array)
	{
		m_nFrame = 1;
		pStage = NULL;
		this->m_nRow = Row;
		this->m_nArray = Array;
		// 中心位置
		this->m_ptCenter.y = m_nRow * pStage->LD + pStage->LD / 2;
		this->m_ptCenter.x = m_nArray * pStage->LD + pStage->LD / 2;

		this->m_nX = m_ptCenter.x;
		this->m_nY = m_ptCenter.y;
	}

	void SetPosition(int Row, int Array);
	void DrawBlank(HDC &hdc);
	void virtual  Draw(HDC &hdc);
	void virtual action();

	int GetRow();
	int GetArray();
	
	~GObject();

	static GMap *pStage;
protected:
	int m_nX;
	int m_nY;
	TWARDS m_cmd;	//指令缓存
	POINT m_ptCenter;//中心坐标
	int m_nRow;//逻辑横坐标
	int m_nArray;//逻辑纵坐标
	int m_nSpeed;//速度
	TWARDS m_dir;//朝向
	int m_nFrame;//帧

	bool Achive();//判断物体是否到达逻辑坐标位置
	bool Collision();//逻辑碰撞检测，将物体摆放到合理的位置
	int PtTransform(int k);//将实际坐标转换成为逻辑坐标
	virtual void AchiveCtrl();//到达逻辑点后更新数据
	
};

class PacMan:public GObject
{
protected:
	virtual void AchiveCtrl() override;//重写虚函数

public:
	POINT GetPos();
	bool IsOver();	//游戏是否结束
	bool IsWin();	// 玩家是否赢得游戏
	void Draw(HDC &hdc);//负责绘制自己
	void SetTwCommand(TWARDS command);//设置玩家下一步指令
	PacMan(int x, int y);
	void action();	//玩家的动作函数
	void SetOver(); //设置游戏结束函数
};


class Enermy:public GObject
{
protected:
	void Catch();	//是否抓住玩家
	void virtual MakeDecision(bool b) = 0;
	COLORREF color;
public:
	static std::shared_ptr<PacMan> player;
	void virtual  Draw(HDC &hdc);//	负责绘制自己
	Enermy(int x,int y):GObject(x,y)
	{
		this->m_nSpeed = ENERMYSPEED;
		m_dir = LEFT;
		m_cmd = UP;
	}
	void virtual action();//负责行为
};


// 三种敌人
class RedOne:public Enermy //随机移动S
{
protected:
	void virtual  MakeDecision(bool b) override;
public:
	void Draw(HDC& hdc) override;
	RedOne(int x,int y):Enermy(x,y)
	{
		color = RGB(255, 0, 0);
	}
};

class BlueOne :public RedOne //守卫者
{
protected:
	void virtual  MakeDecision(bool b) override;
public:
	void Draw(HDC& hdc) override;
	BlueOne(int x, int y) :RedOne(x, y)
	{
		color = RGB(0, 0, 255);
	}
};


class YellowOne :public RedOne //守卫者
{
protected:
	void virtual  MakeDecision(bool b) override;
public:
	void Draw(HDC& hdc) override;
	YellowOne(int x, int y) :RedOne(x, y)
	{
		color = RGB(200, 200, 100);
	}
};