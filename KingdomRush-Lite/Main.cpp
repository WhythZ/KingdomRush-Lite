/*ע������
* 1���˴�����ѡ������Ч�ʽϺõ�Releaseģʽ������Ϣ��ӡ������̨���е��ԣ����ַ�ʽҲ��������С����Ϸ����
* 2������������"C/C++"��"��������"�µ�"���п�"����Ӧ��Ϊ"���߳�(/MT)"����ȷ����̬��������ʱ��
*/

#pragma region Preprocessing
//���˺궨�壬����main������Ԥ����׶λᱻdefineΪSDL_main
#define SDL_MAIN_HANDLED
//����SDL��
#include <SDL.h>
//ͼ��֧��
#include <SDL_image.h>
//����֧��
#include <SDL_mixer.h>
//����֧��
#include <SDL_ttf.h>
//ͼ��֧��
#include <SDL2_gfxPrimitives.h>
//�ļ���д
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//���ڽ���JSON�ļ�
#include <cJSON.h>
//������
#include "Game_Manager.h"
#pragma endregion

int main()
{
	#pragma region Initialize
	//��ʼ��SDL���������ϵͳ
	SDL_Init(SDL_INIT_EVERYTHING);
	//����Ļ������ʾһ������Ϊ"WhythZ"��1280x720��һ����ʽ�Ĵ��� 
	SDL_Window* window = SDL_CreateWindow(u8"WhythZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	//������Ⱦ����ʹ��GPU���м��٣����ոմ����Ĵ�����
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//��ʼ��SDL_image��ĸ�֧�ָ�ʽ
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	
	//��ʼ��SDL_ttf��
	TTF_Init();
	
	//��ʼ��SDL_mixer���֧�ָ�ʽ
	Mix_Init(MIX_INIT_MP3);
	//�򿪻�������������Mix_OpenAudio(��Ƶ������, ������Ƶ��ʽ, ������, ��Ƶ���뻺������С)
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	#pragma endregion
	
	#pragma region ControlFPS
	//��Ҫά�ֵ���Ϸ֡�ʣ�frame per second��������ÿ��ˢ�µ�֡��
	int fps = 60;
	//�˺�����ȡһ�������ܣ����Ƚϸߣ���ʱ�����������ص�ֵ����ʱ��������������Ϊ��ʱ������㣬ͨ����������Ƶ�ʲ�������
	Uint64 lastCounter = SDL_GetPerformanceCounter();
	//Ƶ�ʼ�ÿһ��˼�ʱ���������ٴ�
	Uint64 counterFreq = SDL_GetPerformanceFrequency();
	#pragma endregion

	#pragma region Managers
	//��Ϸ������ָ��ʵ��
	GameManager* gameManager = GameManager::GetInstance();
	#pragma endregion

	#pragma region GameCircle
	//������Ϸ��ѭ���Ƿ����
	bool isQuit = false;
	//���ڵ���SDL�¼������ݲ�ͬ���¼�����������Ӧ�ķ�Ӧ
	SDL_Event event;
	//�洢���ָ��λ��
	SDL_Point cursorPos = { 0,0 };

	//��Ϸ��ѭ��
	while (!isQuit)
	{
		/*�����¼��Ա�֤������������*/
		while (SDL_PollEvent(&event))
		{
			//������ڵ��˳���ʱ������SDL_QUIT�¼�
			if (event.type == SDL_QUIT)
				isQuit = true;
			//���ָ���ƶ��¼�
			if (event.type == SDL_MOUSEMOTION)
			{
				//��ȡ���ָ������
				cursorPos.x = event.motion.x;
				cursorPos.y = event.motion.y;
			}
		}

		#pragma region ControlFPS
		/*��ʱ��*/
		//��ȡ��ǰ�ļ�ʱ��������������������ѭ��ǰ�õ��ļ�ʱ����������
		Uint64 currentCounter = SDL_GetPerformanceCounter();
		//�����ת��Ϊ˫���ȸ��㣬����Ƶ�ʵõ�ÿ��ѭ����ʱ��������λΪ�룩
		double delta = (double)(currentCounter - lastCounter) / counterFreq;
		//����ǰ�Ĵ�����Ϊ��㣬������һ��ѭ��
		lastCounter = currentCounter;
		//����֡�ʳ������޶�ֵ����ô�ͽ������ʱ���ӳٵ���ֹ��ѭ��Ƶ�ʹ��죻����1000�ǽ���ת��Ϊ���룬��Ϊ�������λ̫������Ȳ���
		if (delta * 1000 < 1000.0 / fps)
			SDL_Delay((Uint32)(1000.0 / fps - delta * 1000));
		#pragma endregion

		#pragma region Draw&Render
		/*��Ⱦ��ͼ*/
		//ȷ����Ⱦ����ɫΪ���ڣ���͸����������RGB��ɫ��Alpha����¼ͼ���͸������Ϣ��256���Ҷȣ�
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//ʹ���趨�Ĳ�͸����ɫ����������ڴﵽ������Ч��
		SDL_RenderClear(renderer);
		//�����ָ�봦����һ����ɫ��Բ�����Ĳ���λΪ�뾶��������ΪRGB��Alpha
		filledCircleRGBA(renderer, cursorPos.x, cursorPos.y, 55, 255, 0, 0, 200);
		//����Ⱦ�����ݸ��µ����ڻ�������
		SDL_RenderPresent(renderer);
		#pragma endregion
	}
	#pragma endregion
}