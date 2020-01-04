#pragma once

#include <time.h>
#include "GMap.h"
#include <memory>
#define PLAYERSPEED 6	// ����ٶ�
#define ENERMYSPEED 4	// �����ٶ�
#define LEGCOUNTS 5		// �����ȵ�����
#define DISTANCE 10		// ͼ�η�Χ
#define BLUE_ALERT 8    // ��ɫ���䷶Χ
#define D_OFFSET 2		// ��ͼ���
#define RD (DISTANCE + D_OFFSET) //��ͼ��Χ

enum TWARDS
{//  �������� ��Ϸ����
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
		// ����λ��
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
	TWARDS m_cmd;	//ָ���
	POINT m_ptCenter;//��������
	int m_nRow;//�߼�������
	int m_nArray;//�߼�������
	int m_nSpeed;//�ٶ�
	TWARDS m_dir;//����
	int m_nFrame;//֡

	bool Achive();//�ж������Ƿ񵽴��߼�����λ��
	bool Collision();//�߼���ײ��⣬������ڷŵ������λ��
	int PtTransform(int k);//��ʵ������ת����Ϊ�߼�����
	virtual void AchiveCtrl();//�����߼�����������
	
};

class PacMan:public GObject
{
protected:
	virtual void AchiveCtrl() override;//��д�麯��

public:
	POINT GetPos();
	bool IsOver();	//��Ϸ�Ƿ����
	bool IsWin();	// ����Ƿ�Ӯ����Ϸ
	void Draw(HDC &hdc);//��������Լ�
	void SetTwCommand(TWARDS command);//���������һ��ָ��
	PacMan(int x, int y);
	void action();	//��ҵĶ�������
	void SetOver(); //������Ϸ��������
};


class Enermy:public GObject
{
protected:
	void Catch();	//�Ƿ�ץס���
	void virtual MakeDecision(bool b) = 0;
	COLORREF color;
public:
	static std::shared_ptr<PacMan> player;
	void virtual  Draw(HDC &hdc);//	��������Լ�
	Enermy(int x,int y):GObject(x,y)
	{
		this->m_nSpeed = ENERMYSPEED;
		m_dir = LEFT;
		m_cmd = UP;
	}
	void virtual action();//������Ϊ
};


// ���ֵ���
class RedOne:public Enermy //����ƶ�S
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

class BlueOne :public RedOne //������
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


class YellowOne :public RedOne //������
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