#pragma once
#include<iostream>
#include<fstream>
#include<string.h>
#include"Graph.h"
using namespace std;
//这里是管理类，管理类的主要功能有
//1.读入结点链接关系
//2.生成图（这里可以调用Graph类）
//3.完成最小生成树
//4.输出路由表
//5.添加点和边关系（如果只添加点，需要完成一件情，当一个点不可达时，请给出相应回应）
//请在下面添加你们的代码
//函数的接口请你自行给出
class Manage
{
public:
	Graph Route;
	int *path;//最短路径
	bool GetInformation();//你要告诉我读入信息是否成功
	bool shortestpath();//最短路径
	bool addVertex();//新建结点，也要改写文件哦~
	bool addEdge();//这里不仅会调用Graph的函数，同时也要改写文件
};

void print(Graph& G, int v,int dist[], int path[])
{
		cout <<endl<< "路由器" << G.getvalue(v) << "的路由表：" << endl;
		cout << "目的地址      下一跳"<<endl;
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
				cout << "路由器" << G.getvalue(i) << "        ";
				if (k > 0)
				{
					cout << G.getvalue(d[--k]) << " "<<endl;
				}
//				cout << "最短路径长度为：" << dist[i] << endl;
			}
		}
		delete[] d;
}
//dijstra算法求最短路径
void ShortestPath(Graph& G, int v, int dist[], int path[])
{//Graph是一个带权有向图，本算法建立一个数组，dist[j],0<=j<n;是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path存放求到的最短路径

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
//读结点
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
//读边
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
		cout << "没有这个结点！" << endl;
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
