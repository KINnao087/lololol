#include<stdio.h>
#include<Windows.h>
#include<iostream>
#include<stdarg.h>
#include<stdlib.h>
#include<thread>
using namespace std; 
int is_infinitesun = -1;
int is_NOCD = -1;
int is_onehitkill = -1;
DWORD find_address(HANDLE processH, DWORD base_address,int add_count,...)
{
	va_list p; DWORD tmpbuffer;
	va_start(p, add_count);
	DWORD buffer=base_address;
	for (int i = 0; i < add_count; i++)//����ƫ�Ʋ���  ����Ϊ��ַ�������ټ���ƫ���������������buffer,ѭ��add_count��
	{
		ReadProcessMemory(processH, (LPCVOID)buffer, &tmpbuffer, sizeof(DWORD), NULL);
		DWORD tmp = va_arg(p, DWORD);//ȡ��ƫ����
		tmpbuffer += tmp;//����ƫ����
		buffer = tmpbuffer;
	}
	return buffer;
}
void infinitesun(HANDLE processH,DWORD address,int sun)
{
	while (true)
	{
		if (is_infinitesun == 1)
		{
			is_infinitesun = is_infinitesun;
			WriteProcessMemory(processH, (LPVOID)address, &sun, sizeof(DWORD), NULL);
			Sleep(500);
		} 
	}
}
void writememory(HANDLE processH, DWORD code_address, int add_count,...)//ר������д���룬���������޸�����
{
	va_list codes;
	va_start(codes, add_count);
	char buffer[1000];
	for(int i=0;i<add_count;i++)
	{
		buffer[i]=va_arg(codes, char);
	}
	//д�����
	WriteProcessMemory(processH, (LPVOID)code_address, buffer, add_count, NULL);
	//WriteProcessMemory(processH, (LPVOID)code_address, buffer, 9, NULL);
}
int main()
{
	int cion; DWORD cion_address;
	HWND h = FindWindow(NULL, L"Plants vs. Zombies");
	if (h == 0)
	{
		printf("ע��:����������Ϸ������ؿ����ٴ�\n");
		getchar();
		return 0;
	}
	DWORD pid;
	GetWindowThreadProcessId(h, &pid);
	printf("pid:%d\n", pid);
	HANDLE Hpvz = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);//��ȡpvz���
	DWORD sun_address = find_address(Hpvz, 0x00731C50, 2, 0x868, 0x5578);

	printf("1-��������\n2-����ȴ\n3-һ����ɱ\n4-�޸Ľ�Ǯ\n(����0����)\n");

	int index = 10;
	thread t1(infinitesun, Hpvz, sun_address, 9990);
	while(index)
	{
		scanf_s("%d", &index);
		switch (index)
		{
		case 0:
			break;
		case 1://��������
			is_infinitesun *= -1;
			if (is_infinitesun==1)
				printf("ע��:::::���������ѿ���:::::\n");
			else
				printf("ע��:::::���������ѹر�:::::\n");
			break;
		case 2://��CD
			is_NOCD *= -1;
			if (is_NOCD == 1)
			{
				printf("ע��:::::��CD�ѿ���:::::\n");
				writememory(Hpvz, 0x004958BC, 9, 0x81, 0x47, 0x24, 0x00, 0x10, 0x00, 0x00, 0x90, 0x90);
			}
			else
			{
				printf("ע��:::::��CD�ѹر�:::::\n");
				writememory(Hpvz, 0x004958BC, 9, 0xff, 0x47, 0x24, 0x8b, 0x47, 0x24, 0x3b, 0x47, 0x28);
			}
			break;
		case 3://��ɱ��ʬ
			is_onehitkill *= -1;
			if (is_onehitkill == 1)
			{
				writememory(Hpvz, 0x00545e04, 11, 0xc7, 0x87, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90);//��ɱ����(��)
				//writememory(Hpvz, 0x00545e04, 6, 0xe9, 0xf7, 0xa1, 0x57, 0x00, 0x90);//����ת
				//writememory(Hpvz, 0x00ac0000, 15, 0xc7, 0x87, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0xfb, 0x5d, 0xa8, 0xff);//ע����Ҫ����
				writememory(Hpvz, 0x00545b1a, 11, 0xc7, 0x85, 0xd0, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x90);//��ɱͷ�ϵķ���
				//writememory(Hpvz, 0x00545b1a, 6, 0xe9, 0xe1, 0xa4, 0x58, 0x00, 0x90);
				//writememory(Hpvz, 0x00ad0000, 15, 0xc7, 0x85, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0x11, 0x5b, 0xa7, 0xff);
				writememory(Hpvz, 0x00545781, 2, 0x90, 0x90);//��ɱ�������(��)
				//writememory(Hpvz, 0x00545771, 6, 0xe9, 0x8a, 0xa8, 0x59, 0x00, 0x90);
				//writememory(Hpvz, 0x00ae0000, 15, 0x81, 0xae, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0xe9, 0x68, 0x57, 0xa6, 0xff);
				printf("ע��:::::һ����ɱ�ѿ���:::::\n");
			}
			else//�ָ�
			{
				writememory(Hpvz, 0x00545e04, 11, 0x89, 0xaf, 0xc8, 0x00, 0x00, 0x00,0xe8,0x61,0xc3,0xff,0xff);//�ָ�����(��)
				writememory(Hpvz, 0x00545b1a, 11, 0x89, 0x8d, 0xd0, 0x00, 0x00, 0x00,0xf6,0xc3,0x04,0x74,0x09);//�ָ�ͷ�ϵķ���
				writememory(Hpvz, 0x00545781, 2, 0x75, 0x18);//�ָ��������(��)
				printf("ע��:::::һ����ɱ�ѹر�:::::\n");
			}
			break;
		case 4://�޸Ľ�Ǯ
			printf("��������Ҫ�޸ĵĽ�Ǯ��:");
			cin >> cion;
			cion_address=find_address(Hpvz, 0x00731C50, 2, 0x0000094c, 0x54);
			//writememory(Hpvz, cion_address, 1, cion);
			if (WriteProcessMemory(Hpvz, (LPVOID)cion_address, &cion, 4, NULL))cout << "�޸ĳɹ�!\n";
			else cout << "�޸�ʧ��!\n";
			break;
		}
	}
	t1.detach();
	return 0;
}