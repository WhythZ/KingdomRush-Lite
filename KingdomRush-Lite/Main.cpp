/*ע������
* 1������Ŀ����ѡ������Ч�ʽϺõ�Releaseģʽ������Ϣ��ӡ������̨���е��ԣ����ַ�ʽҲ��������С����Ϸ����
* 2������������"C/C++"��"��������"�µ�"���п�"����Ӧ��Ϊ"���߳�(/MT)"����ȷ����̬��������ʱ��
*/

#pragma region FileProcess
//�ļ���д
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//���ڽ���JSON�ļ�
#include <cJSON.h>
#pragma endregion

//���˺궨�壬����main������Ԥ����׶λᱻdefineΪSDL_main
#define SDL_MAIN_HANDLED

//��Ϸ��������
#include "Game_Manager.h"

int main(int _argc, char** _argv)
{
	//������Ϸ��������
	GameManager* gameManager = GameManager::GetInstance();
	//������Ϸ��ѭ��������ȡ����ֵ
	return gameManager->Run(_argc, _argv);
}