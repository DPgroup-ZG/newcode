#pragma once

//内存中作业的分配结构
typedef struct Node
{
	Node *pre;            //前趋结点
	Node *next;           //后继结点	
	int size;	          //分区的内存空间大小
	int address;	      //分区首地址
	int workNo;		      //该分区分配给的作业编号
};

class Memory
{
public:

	Memory() { TotalSize = 0; }//初始化虚拟空间为0
	~Memory() { Free(); }	//释放链表结构

	BOOL FirstFit(int workNo, int size);	//首次适应算法
	BOOL BestFit(int workNo, int size);	    //最佳适应算法
	BOOL FreeMemory(int workNo);	        //回收空间算法
	void AllocateTotalSize(int tsize);	    //设置内存空间总大小
	Node* GetPartitionList() { return PartitionList; }  //获取分区链表
	void Free();	                        //释放链表全部内存

private:
	int TotalSize;        //内存空间的总大小
	Node* PartitionList;  //分区链表
};
