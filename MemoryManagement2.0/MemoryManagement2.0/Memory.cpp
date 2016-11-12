#include "stdafx.h"
#include "Memory.h"



// 设置内存空间总大小（即TotalSize）
void Memory::AllocateTotalSize(int tsize)
{
	TotalSize = tsize;
	// 建立一个带头结点的分区链表
	PartitionList = new Node;//分区链表的头结点
	PartitionList->next = NULL;
	PartitionList->pre = NULL;

	// 生成一个新结点记录当前的空闲分区信息
	Node* p = new Node;
	p->size = TotalSize;			//新结点的大小设为内存的总大小		
	p->address = 0;					//新结点的起始地址设为0
	p->workNo = 0;					//新结点的任务号设为0，0表示该分区是空闲分区
	p->next = PartitionList->next;	//后继结点设为NULL
	p->pre = PartitionList;			//前趋结点指向头结点
	PartitionList->next = p;	    //头结点的后继结点指向新结点
}

//首次适应算法
BOOL Memory::FirstFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//target指针指向即将被拆分的分区
	Node* current = NULL;

	//查找第一个满足要求的空闲分区
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	if (target != NULL)
	{
		Node* p = new Node;//新建p结点，指向即将分配给作业的分区结点                          
		p->size = size;//从可用分区中划出size大小的内存空间
		p->address = target->address;//指示该结点的地址为当前空闲分区的起始地址
		target->size = target->size - size;//当前空闲分区的大小减少size
		target->address = target->address + size;//当前空闲分区的起始地址往后偏移size

												 //将新分配的结点插向空闲结点的前面
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("申请内存失败!");
		return FALSE;
	}
}

//最佳适应算法
BOOL Memory::BestFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//target指向即将被拆分的分区
	Node* current = NULL;

	//查找第一个空闲分区
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	//查找出所有符合要求结点中内存最小的空闲分区
	while (current != NULL)
	{
		if (size< current->size && current->size< target->size && current->workNo == 0)
		{
			target = current;
		}
		current = current->next;
	}

	if (target != NULL)  //下面这段代码与首次适应算法一样
	{

		Node* p = new Node;//新建p结点，指示即将分配给作业的分区结点                   
		p->size = size;//从可用分区中划出size大小的内存空间 	
		p->address = target->address;//指示该结点的地址为当前空闲分区的起始地址		
		target->size = target->size - size;//当前空闲分区的大小减少size		
		target->address = target->address + size;//当前空闲分区的起始地址往后偏移size

												 // 将新分配的结点插向空闲结点的前面
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("申请内存失败!");
		return FALSE;
	}
}

//回收空间算法
BOOL Memory::FreeMemory(int workNo)
{
	Node* current;
	//找到要释放空间的作业
	current = PartitionList->next;
	while (current != NULL && current->workNo != workNo)
	{
		current = current->next;
	}

	//释放该作业的内存
	if (current)
	{
		// 情况1：当需要释放内存的分区前后都是空闲分区时，将这三个分区合并
		if (current->pre != PartitionList && current->pre->workNo == 0)
		{
			if (current->next != NULL && current->next->workNo == 0)
			{
				// 将释放内存的分区与其后的空闲分区合并
				current->size = current->size + current->next->size;
				current->workNo = 0;
				if (current->next->next != NULL)
				{
					current->next->next->pre = current;
				}
				current->next = current->next->next;
			}

			// 将刚才合并后的分区，与其前面的空闲分区再次合并，实现三个分区合并
			current->pre->size = current->pre->size + current->size;
			current->pre->next = current->next;
			if (current->next != NULL)
			{
				current->next->pre = current->pre;
			}
		}
		// 情况2：如果其前面分区是非空闲分区，而其后的分区是空闲分区，则将其与后面的分区合并
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
		// 情况3：其前后没有空闲分区，则仅释放本身的内存
		else
		{
			current->workNo = 0;
		}
		return TRUE;
	}
	else
	{
		AfxMessageBox("释放内存失败!");
		return FALSE;
	}
}

//释放链表全部内存
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
