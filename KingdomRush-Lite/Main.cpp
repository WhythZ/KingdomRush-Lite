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
#pragma endregion

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

	//�洢���ָ��λ��
	SDL_Point cursorPos = { 0,0 };

	//������Ϸ��ѭ���Ƿ����
	bool isQuit = false;
	//���ڵ���SDL�¼������ݲ�ͬ���¼�����������Ӧ�ķ�Ӧ
	SDL_Event event;

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