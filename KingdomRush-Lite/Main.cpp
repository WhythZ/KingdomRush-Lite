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

void Test_JSON()
{
	//����·���µ��ļ�
	std::ifstream testFile("GameData/test.json");
	//����Ƿ�ɹ�����
	if (!testFile.good())
	{
		std::cout << "JSON File Note Found" << std::endl;
		return;
	}

	//���ڴ洢����ȡ�ļ�������
	std::stringstream fileData;
	//�����ж�ȡ�������ݷ������������
	fileData << testFile.rdbuf();
	//�ص�����ȡ�ļ�
	testFile.close();

	//���ַ������ݣ���JSON����Ȧ�Ļ����ż�����������ݣ�������jsonRoot������
	cJSON* jsonRoot = cJSON_Parse(fileData.str().c_str());

	//��jsonRoot���Լ�����ȡ��Ӧ��ֵ
	cJSON* json_alive = cJSON_GetObjectItem(jsonRoot, "alive");
	cJSON* json_name = cJSON_GetObjectItem(jsonRoot, "name");
	cJSON* json_age = cJSON_GetObjectItem(jsonRoot, "age");
	cJSON* json_hobby = cJSON_GetObjectItem(jsonRoot, "hobby");
	cJSON* json_friend = cJSON_GetObjectItem(jsonRoot, "friend");

	/*չʾ���ɹ���ȡ�����ݵļ�ֵ��*/
	//չʾ��ȡ�Ĳ���ֵ
	std::cout << json_alive->string << " : " << json_alive->valueint << std::endl;
	//չʾ��ȡ���ַ���
	std::cout << json_name->string << " : " << json_name->valuestring << std::endl;
	//չʾ��ȡ�����ͣ������Ͷ�Ӧvaluedouble��
	std::cout << json_age->string << " : " << json_age->valueint << std::endl;
	//չʾ��ȡ������
	std::cout << json_hobby->string << " : " << std::endl;
	cJSON* item_ptr = nullptr;
	cJSON_ArrayForEach(item_ptr, json_hobby)
	{
		//�����Ǹ������һ����ʱ�Ĺ��߿�ָ�����Ҫ������JSONԪ�ض���������ִ��һ��forѭ�������������е�Ԫ��
		std::cout << "\t" << item_ptr->valuestring << std::endl;
	}
	//��֪����ô����Ƕ��JSON���о�û��Ҫд��ô����
	//std::cout << json_friend->string << " : " << json_friend->type << std::endl;
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

	Test_JSON();

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