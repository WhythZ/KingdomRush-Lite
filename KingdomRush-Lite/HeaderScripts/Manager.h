//�ɼ̳е���ģ����ʵ�֣���#ifndefԤ�����ֹ�ڲ����뱻��α���
#ifndef _MANAGER_H_
#define _MANAGER_H_
class Manager
{
public:
	//��̬�ĺ��������ڻ�ȡManager���Ψһʵ��ָ��
	static Manager* GetInstance()
	{
		//��managerδ��������Ϊ��ָ�룩�����ڶ�������һ��
		if (!manager)
		{
			manager = new Manager();
		}

		//�������ǾͿ������ⲿͨ��Manager* xxxx = Manager::GetInstance();��ȡ�ڲ����Manager����ĵ�ַ�������Ǵ���һ���µ�Manager
		return manager;
	}

	//��������
	~Manager() = default;

private:
	//��̬��ΨһManager������ָ�룬���ⲿ��ʼ����Manager* Manager::manager = nullptr;
	static Manager* manager;

private:
	//˽�еĹ��캯��������ģʽ���಻Ӧ���ܱ����ⲿ��������
	Manager() = default;
};
#endif // !_MANAGER_H_
