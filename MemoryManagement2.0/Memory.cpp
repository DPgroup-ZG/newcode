#include "stdafx.h"
#include "Memory.h"



// �����ڴ�ռ��ܴ�С����TotalSize��
void Memory::AllocateTotalSize(int tsize)
{
	TotalSize = tsize;
	// ����һ����ͷ���ķ�������
	PartitionList = new Node;//���������ͷ���
	PartitionList->next = NULL;
	PartitionList->pre = NULL;

	// ����һ���½���¼��ǰ�Ŀ��з�����Ϣ
	Node* p = new Node;
	p->size = TotalSize;			//�½��Ĵ�С��Ϊ�ڴ���ܴ�С		
	p->address = 0;					//�½�����ʼ��ַ��Ϊ0
	p->workNo = 0;					//�½����������Ϊ0��0��ʾ�÷����ǿ��з���
	p->next = PartitionList->next;	//��̽����ΪNULL
	p->pre = PartitionList;			//ǰ�����ָ��ͷ���
	PartitionList->next = p;	    //ͷ���ĺ�̽��ָ���½��
}

//�״���Ӧ�㷨
BOOL Memory::FirstFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//targetָ��ָ�򼴽�����ֵķ���
	Node* current = NULL;

	//���ҵ�һ������Ҫ��Ŀ��з���
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	if (target != NULL)
	{
		Node* p = new Node;//�½�p��㣬ָ�򼴽��������ҵ�ķ������                          
		p->size = size;//�ӿ��÷����л���size��С���ڴ�ռ�
		p->address = target->address;//ָʾ�ý��ĵ�ַΪ��ǰ���з�������ʼ��ַ
		target->size = target->size - size;//��ǰ���з����Ĵ�С����size
		target->address = target->address + size;//��ǰ���з�������ʼ��ַ����ƫ��size

												 //���·���Ľ�������н���ǰ��
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
		return FALSE;
	}
}

//�����Ӧ�㷨
BOOL Memory::BestFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//targetָ�򼴽�����ֵķ���
	Node* current = NULL;

	//���ҵ�һ�����з���
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	//���ҳ����з���Ҫ�������ڴ���С�Ŀ��з���
	while (current != NULL)
	{
		if (size< current->size && current->size< target->size && current->workNo == 0)
		{
			target = current;
		}
		current = current->next;
	}

	if (target != NULL)  //������δ������״���Ӧ�㷨һ��
	{

		Node* p = new Node;//�½�p��㣬ָʾ�����������ҵ�ķ������                   
		p->size = size;//�ӿ��÷����л���size��С���ڴ�ռ� 	
		p->address = target->address;//ָʾ�ý��ĵ�ַΪ��ǰ���з�������ʼ��ַ		
		target->size = target->size - size;//��ǰ���з����Ĵ�С����size		
		target->address = target->address + size;//��ǰ���з�������ʼ��ַ����ƫ��size

												 // ���·���Ľ�������н���ǰ��
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
		return FALSE;
	}
}

//���տռ��㷨
BOOL Memory::FreeMemory(int workNo)
{
	Node* current;
	//�ҵ�Ҫ�ͷſռ����ҵ
	current = PartitionList->next;
	while (current != NULL && current->workNo != workNo)
	{
		current = current->next;
	}

	//�ͷŸ���ҵ���ڴ�
	if (current)
	{
		// ���1������Ҫ�ͷ��ڴ�ķ���ǰ���ǿ��з���ʱ���������������ϲ�
		if (current->pre != PartitionList && current->pre->workNo == 0)
		{
			if (current->next != NULL && current->next->workNo == 0)
			{
				// ���ͷ��ڴ�ķ��������Ŀ��з����ϲ�
				current->size = current->size + current->next->size;
				current->workNo = 0;
				if (current->next->next != NULL)
				{
					current->next->next->pre = current;
				}
				current->next = current->next->next;
			}

			// ���ղźϲ���ķ���������ǰ��Ŀ��з����ٴκϲ���ʵ�����������ϲ�
			current->pre->size = current->pre->size + current->size;
			current->pre->next = current->next;
			if (current->next != NULL)
			{
				current->next->pre = current->pre;
			}
		}
		// ���2�������ǰ������Ƿǿ��з����������ķ����ǿ��з��������������ķ����ϲ�
		else if (current->pre->workNo != 0 && current->next != NULL && current->next->workNo == 0)
		{
			current->workNo = 0;
			current->size = current->size + current->next->size;
			if (current->next->next != NULL)
			{
				current->next->next->pre = current;
			}
			current->next = current->next->next;
		}
		// ���3����ǰ��û�п��з���������ͷű�����ڴ�
		else
		{
			current->workNo = 0;
		}
		return TRUE;
	}
	else
	{
		AfxMessageBox("�ͷ��ڴ�ʧ��!");
		return FALSE;
	}
}

//�ͷ�����ȫ���ڴ�
void Memory::Free()
{
	Node* current = PartitionList->next;
	while (current != NULL)
	{
		Node* p = current;
		current = current->next;
		delete p;
	}
	delete PartitionList;
}
