#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

//�궨��ÿ����Ƭ�����ش�С��48������
#define TILE_SIZE 48

//��ͼש��Ľṹ�壨�޷����Ĵ����ݽṹϰ���ýṹ�壩��ÿ��ש�����ĸ�ͼ�������ֵȷ����������
struct Tile
{
	enum class TileDir
	{
		None = 0,
		Up = 1,
		Down = 2,
		Left = 3,
		Right = 4
	};

	//ש����ײ�ĵ�����Ⱦͼ�㣻
	int terrainLayer = 0;

	//ש��ڶ����װ����Ⱦͼ�㣻
	int decorationLayer = 0;
	
	//ש�������Ĺ����н�·����Ⱦͼ�㣻None��ʾ��ש�첻�ǹ�����н�·��ש��
	TileDir directionLayer = TileDir::None;
	
	//ש�����ϲ������������Ⱦͼ�㣻-1�����������0�Ǽң�1��2��3�������ֱ��ʾ��ͬ��ˢ�ֵ�
	int specialLayer = -1;
};

//�Զ�����������TileMap����һ���洢TileԪ�صĶ�άvector��������
typedef std::vector<std::vector<Tile>> TileMap;

#endif