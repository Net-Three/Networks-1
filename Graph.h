#pragma once
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct Edge
{
	int dest;//�ߵ���һ��
	double cost;
	Edge*link;//������һ��
	Edge() :link(NULL) {};
	Edge(int num, double weight) :dest(num), cost(weight), link(NULL) {};
	bool operator !=(Edge &a)const
	{
		return (dest != a.dest) ? true : false;
	}
};
struct Vertex
{
	int id;//���Ҹ���ͳһ�ı�ų�վ��
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
	int maxVertices = 0x7fffffff;//��ඥ����Ŀ��������
	int numEdges;//����
	int numVertices;//Ŀǰ������Ŀ
public:
	int getVertexPos(int vertex)
{
	for (int i = 0; i < numVertices; i++)
	{
		if (NodeTable[i].id == vertex)
			return i;//�������ڵڼ���
	}

}
	   int getVertexPos(const Vertex vertex)
	   {
		   for (int i = 0; i < numVertices; i++)
		   {
			   if (NodeTable[i].id == vertex.id)
				   return i;//�������ڵڼ���
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
		cerr << "�洢�������" << endl; exit(1);
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
int Graph::getFirstNeighbor(int v)//���v��ʾ�ý����ͼ�еڼ���
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
			return p->link->dest;//���ص��ǽ�����ʵ��Ŷ������
	}
}
double Graph::getWeight(int v1, int v2)//���ں��������ҵ��������������Ӧ�����
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
			return false;//�ý����Ȼ����
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
bool Graph::insertEdge(int v1, int v2, double weight, int sign)//�����v1 v2��ʵ�ʵı��
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
{//��ȡ��ʵ��id
	if (num >= 0 && num < NumberOfVertices())
		return NodeTable[num].id;
	else
		return -1;
}