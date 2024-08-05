/*ע������
* 1���˴�����ѡ������Ч�ʽϺõ�Releaseģʽ������Ϣ��ӡ������̨���е��ԣ����ַ�ʽҲ��������С����Ϸ����
* 2������������"C/C++"��"��������"�µ�"���п�"����Ӧ��Ϊ"���߳�(/MT)"����ȷ����̬��������ʱ��
*/

#pragma region Preprocessing
//���˺궨�壬����main������Ԥ����׶λᱻdefineΪSDL_main
#define SDL_MAIN_HANDLED

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
#pragma endregion

void Test_CSV()
{
	//����·���µ��ļ�
	std::ifstream testFile("GameData/test.CSV");
	//����Ƿ�ɹ�����
	if (!testFile.good())
	{
		std::cout << "CSV File Note Found" << std::endl;
		return;
	}

	//CSV��Ҫ���ж�ȡ���ñ�����ѭ���д洢ÿһ�е�����
	std::string lineBuf;
	//ͨ��ѭ��������ÿ�����ݣ�getline������һ����λ���ձ���ȡ���ļ����ڶ�����λ�Ǵ�Ŷ�ȡ�����ݵĶ��󣬵�������λĬ�����Ի��з������ȡ
	while (std::getline(testFile, lineBuf))
	{
		//ʹ��ÿ�е�������������������������lineStream��������Ϊgetline�����ĵ�һ��������lineBuf����ֱ�ӷ������λ�ã���Ϊû������������
		std::stringstream lineStream(lineBuf);
		//�ñ������ڴ洢�Էָ����������ֶ�
		std::string gridBuf;
		//�ڲ�ѭ���������е�ÿ���ֶε����ݣ�ʶ�𶺺��ַ���Ϊ�ָ���
		while (std::getline(lineStream, gridBuf, ','))
		{
			//չʾ��ȡ����ÿ���ֶ�
			std::cout << gridBuf << ", ";
		}
		std::cout << std::endl;
	}
	//1, 2, 3,
	//4, 5, 6,
	//7, 8, 9,

	//�ص��ļ�
	testFile.close();
}

int main()
{
	#pragma region Initialize
	//��ʼ��SDL���������ϵͳ
	SDL_Init(SDL_INIT_EVERYTHING);
	//��ʼ��SDL_image��ĸ�֧�ָ�ʽ
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	//��ʼ��SDL_ttf��
	TTF_Init();
	//��ʼ��SDL_mixer���֧�ָ�ʽ
	Mix_Init(MIX_INIT_MP3);
	//�򿪻�������������Mix_OpenAudio(��Ƶ������, ������Ƶ��ʽ, ������, ��Ƶ���뻺������С)
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	#pragma endregion
	
	#pragma region Window&Render
	//����Ļ������ʾһ������Ϊ"WhythZ"��1280x720��һ����ʽ�Ĵ��� 
	SDL_Window* window = SDL_CreateWindow(u8"WhythZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	//������Ⱦ����ʹ��GPU���м��٣����ոմ����Ĵ�����
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	#pragma endregion

	#pragma region ControlFPS
	//��Ҫά�ֵ���Ϸ֡�ʣ�frame per second��������ÿ��ˢ�µ�֡��
	int fps = 60;
	//�˺�����ȡһ�������ܣ����Ƚϸߣ���ʱ�����������ص�ֵ����ʱ��������������Ϊ��ʱ������㣬ͨ����������Ƶ�ʲ�������
	Uint64 lastCounter = SDL_GetPerformanceCounter();
	//Ƶ�ʼ�ÿһ��˼�ʱ���������ٴ�
	Uint64 counterFreq = SDL_GetPerformanceFrequency();
	#pragma endregion

	//������Ϸ��ѭ���Ƿ����
	bool isQuit = false;
	//���ڵ���SDL�¼������ݲ�ͬ���¼�����������Ӧ�ķ�Ӧ
	SDL_Event event;
	//�洢���ָ��λ��
	SDL_Point cursorPos = { 0,0 };

	Test_CSV();

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

		/*��Ⱦ��ͼ*/
		//ȷ����Ⱦ����ɫΪ���ڣ���͸����������RGB��ɫ��Alpha����¼ͼ���͸������Ϣ��256���Ҷȣ�
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//ʹ���趨�Ĳ�͸����ɫ����������ڴﵽ������Ч��
		SDL_RenderClear(renderer);
		//�����ָ�봦����һ����ɫ��Բ�����Ĳ���λΪ�뾶��������ΪRGB��Alpha
		filledCircleRGBA(renderer, cursorPos.x, cursorPos.y, 55, 255, 0, 0, 200);
		//����Ⱦ�����ݸ��µ����ڻ�������
		SDL_RenderPresent(renderer);
	}
}