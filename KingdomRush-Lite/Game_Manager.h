#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "Manager.h"
class GameManager : public Manager<GameManager>
{
	//��������GetInstance����Ȩ���Ե���GameManager��ı����Ĺ��캯��
	friend class Manager<GameManager>;
public:
protected:
	GameManager()
	{
	}
	~GameManager()
	{
	}
};

#endif // !_GAME_MANAGER_H_
