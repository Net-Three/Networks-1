#pragma once
#include<iostream>
#include<fstream>
#include<string.h>
#include"Graph.h"
using namespace std;
//�����ǹ����࣬���������Ҫ������
//1.���������ӹ�ϵ
//2.����ͼ��������Ե���Graph�ࣩ
//3.�����С������
//4.���·�ɱ�
//5.��ӵ�ͱ߹�ϵ�����ֻ��ӵ㣬��Ҫ���һ���飬��һ���㲻�ɴ�ʱ���������Ӧ��Ӧ��
//��������������ǵĴ���
//�����Ľӿ��������и���
class Manage
{
public:
	Graph Route;
	int *path;//���·��
	bool GetInformation();//��Ҫ�����Ҷ�����Ϣ�Ƿ�ɹ�
	bool shortestpath();//���·��
	bool addVertex();//�½���㣬ҲҪ��д�ļ�Ŷ~
	bool addEdge();//���ﲻ�������Graph�ĺ�����ͬʱҲҪ��д�ļ�
};

void print(Graph& G, int v,int dist[], int path[])
{
		cout <<endl<< "·����" << G.getvalue(v) << "��·�ɱ�" << endl;
		cout << "Ŀ�ĵ�ַ      ��һ��"<<endl;
		int i, j, k;
		int n = G.NumberOfVertices();
		int *d = new int[n];
		for (i = 0; i < n; i++)
		{
			if (i != v)
			{
				j = i;
				k = 0;
				while (j != v)
				{
					d[k++] = j;
					j = path[j];
				}
				cout << "·����" << G.getvalue(i) << "        ";
				if (k > 0)
				{
					cout << G.getvalue(d[--k]) << " "<<endl;
				}
//				cout << "���·������Ϊ��" << dist[i] << endl;
			}
		}
		delete[] d;
}
//dijstra�㷨�����·��
void ShortestPath(Graph& G, int v, int dist[], int path[])
{//Graph��һ����Ȩ����ͼ�����㷨����һ�����飬dist[j],0<=j<n;�ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path����󵽵����·��

	int n = G.NumberOfVertices();
	bool *S = new bool[n];
	int i, j, k;
	int w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] <G.maxWeight)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = G.maxWeight;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w <G.maxWeight && dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	print(G, v,dist, path);
}

bool Manage::GetInformation()
{
	Vertex vertex;
	Edge edge;
//�����
	ifstream out("Vertex.txt",ios::in);
	if (!out)
	{
		cout << "fail to open the vertex file!" << endl;
		return false;
	}
	while (!out.eof())
	{
		out >> vertex.name >> vertex.id;
		vertex.adj = NULL;
		if (Route.insertVertex(vertex) == false)
		{
			cout << "fail to insert the vertex" << endl;
			return false;
		}
	}
	out.close();
//����
	ifstream OUT("Edge.txt", ios::in);
	if (!out)
	{
		cout << "fail to open the edge file!" << endl;
		return false;
	}
	while (!OUT.eof())
	{
		int v1, v2, cost;
		OUT >> v1 >> v2 >>cost ;
		if (Route.insertEdge(v1,v2,cost,0) == false)
		{
			cout << "fail to insert the vertex" << endl;
			return false;
		}
	}
	OUT.close();
	cout << "load data successfully!"<<endl;
	return true;
}

bool Manage::shortestpath()
{
	int num = Route.NumberOfVertices();
	if (num == -1)
	{
		cout << "û�������㣡" << endl;
		return false;
	}
	int *distance = new int[1000];
	int *path = new int[1000];
	for (int i = 0; i < num; i++)
	{
		ShortestPath(Route, i, distance, path);
	}
	return true;
}
