#pragma once

//�ڴ�����ҵ�ķ���ṹ
typedef struct Node
{
	Node *pre;            //ǰ�����
	Node *next;           //��̽��	
	int size;	          //�������ڴ�ռ��С
	int address;	      //�����׵�ַ
	int workNo;		      //�÷������������ҵ���
};

class Memory
{
public:

	Memory() { TotalSize = 0; }//��ʼ������ռ�Ϊ0
	~Memory() { Free(); }	//�ͷ�����ṹ

	BOOL FirstFit(int workNo, int size);	//�״���Ӧ�㷨
	BOOL BestFit(int workNo, int size);	    //�����Ӧ�㷨
	BOOL FreeMemory(int workNo);	        //���տռ��㷨
	void AllocateTotalSize(int tsize);	    //�����ڴ�ռ��ܴ�С
	Node* GetPartitionList() { return PartitionList; }  //��ȡ��������
	void Free();	                        //�ͷ�����ȫ���ڴ�

private:
	int TotalSize;        //�ڴ�ռ���ܴ�С
	Node* PartitionList;  //��������
};
