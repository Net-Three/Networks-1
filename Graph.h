#pragma once
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct Edge
{
	int dest;//边的另一点
	double cost;
	Edge*link;//连向下一个
	Edge() :link(NULL) {};
	Edge(int num, double weight) :dest(num), cost(weight), link(NULL) {};
	bool operator !=(Edge &a)const
	{
		return (dest != a.dest) ? true : false;
	}
};
struct Vertex
{
	int id;//国家给的统一的编号车站的
	string name;
	Edge*adj;
};
class Graph
{
public:
	const int maxWeight = 0x7fffffff;
	Vertex *NodeTable;
	Graph();
	~Graph();
	bool GraphEmpty()const
	{
		if (numEdges == 0)return true;
		else return false;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}
	double getWeight(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const Vertex& vertex);
	int NumberOfVertices()
	{
		return numVertices;
	}
	bool insertEdge(int v1, int v2, double cost, int sign);
	int getvalue(int id);
protected:
	int maxVertices = 0x7fffffff;//最多顶点数目，无意义
	int numEdges;//边数
	int numVertices;//目前顶点数目
public:
	int getVertexPos(int vertex)
{
	for (int i = 0; i < numVertices; i++)
	{
		if (NodeTable[i].id == vertex)
			return i;//这个结点在第几排
	}

}
	   int getVertexPos(const Vertex vertex)
	   {
		   for (int i = 0; i < numVertices; i++)
		   {
			   if (NodeTable[i].id == vertex.id)
				   return i;//这个结点在第几排
		   }
		   return -1;
	   }
};
Graph::Graph()
{
	maxVertices = 1000;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex[1000];
	if (NodeTable == NULL)
	{
		cerr << "存储分配错误" << endl; exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}
Graph::~Graph()
{
	for (int i = 0; i < numVertices; i++)
	{
		for (int i = 0; i < numVertices; i++)
		{
			Edge *p = NodeTable[i].adj;
			while (p != NULL)
			{
				NodeTable[i].adj = p->link;
				delete p;
				p = NodeTable[i].adj;
			}
		}
	}
}
int Graph::getFirstNeighbor(int v)//这个v表示该结点在图中第几排
{
	if (v != -1)
	{
		Edge *p = NodeTable[v].adj;
		return p->dest;
	}
	else return -1;
}
int Graph::getNextNeighbor(int v, int w)
{
	if (v != -1)
	{
		Edge*p = NodeTable[v].adj;
		while (p != NULL&&p->dest != w)
			p = p->link;
		if (p != NULL&&p->link != NULL)
			return p->link->dest;//返回的是结点的真实编号而非序号
	}
}
double Graph::getWeight(int v1, int v2)//先在函数外面找到了两个结点所对应的序号
{
	if (v1 != -1 && v2 != -1)
	{
		Edge*p = NodeTable[v1].adj;
		while (p != NULL&&p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)return p->cost;
	}
	return maxWeight;
}
bool Graph::insertVertex(const Vertex& vertex)
{
	for (int i = 0; i < numVertices; i++)
	{
		if (NodeTable[i].id == vertex.id)
			return false;//该结点已然存在
	}
	if (numVertices == maxVertices)return false;
	else
	{
		NodeTable[numVertices].id = vertex.id;
		NodeTable[numVertices].name = vertex.name;
		NodeTable[numVertices].adj = NULL;
		numVertices++;
		return true;
	}
}
bool Graph::insertEdge(int v1, int v2, double weight, int sign)//这里的v1 v2是实际的编号
{
	v1 = getVertexPos(v1);
	v2 = getVertexPos(v2);
	if (v1 >= 0 && v1 < numVertices&&v2 >= 0 && v2 < numVertices)
	{
		Edge*q, *p = NodeTable[v1].adj;
		while (p != NULL&&p->dest != v2)
		{
			p = p->link;
		}
		if (p!=NULL)
		{
			return false;
		}
		p = new Edge;
		q = new Edge;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
}
int Graph::getvalue(int num)
{//获取真实的id
	if (num >= 0 && num < NumberOfVertices())
		return NodeTable[num].id;
	else
		return -1;
}