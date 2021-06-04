#include<iostream>
#include<vector>
#include<fstream>
#include<windows.h>
using namespace std;
vector<vector<int>> graph;
vector<int> path;
vector<int> nodes;//сюда записываем посещенные и просмотренные вершины из dfs
bool flag=false;


//получение графа из файла с путем path
void get_graph(const char* Path)
{
	ifstream fin;
	fin.open(Path);
	if (!fin.is_open())
	{
		cout << "Файл \"" << Path << "\" не удалось открыть";
		return;
	}
	int size;
	fin >> size;
	graph.resize(size);
	for (int i = 0; i < size; i++)
	{
		int count;
		fin >> count;
		for (int j = 0; j < count; j++)
		{
			int vertex;
			fin >> vertex;
			graph[i].push_back(vertex);
		}
		nodes.push_back(0);
	}
}

//Вывод графа
void print_graph()
{
	for (int i = 0; i < graph.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}

}

//Поиск в глубину
void dfs(int vertex)
{
	if (flag)
	{
		return;
	}
	nodes[vertex] = 1;
	path.push_back(vertex);
	for (int i = 0; i < graph[vertex].size(); i++)
	{
		if (nodes[graph[vertex][i]]==0)
		{
			dfs(graph[vertex][i]);
		}
		if (nodes[graph[vertex][i]] == 1)
		{
			path.push_back(graph[vertex][i]);
			flag = true;
			while(path.front()!=path.back())
			path.erase(path.begin());
			break;
		}
	}
	nodes[vertex] = 2;
	if (flag)
	{
		return;
	}
	else
	path.pop_back();
}

//перебираем все вершины(не пройденные) и запускаем для них dfs(для невзязных графов)
bool is_acyclic()
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (nodes[i]==0)
		{
			dfs(i);
			if (flag)
			{
				return false;
			}
		}
	}
	return true;
}
void myfunc(const char *Path)
{	
	cout << "Файл: " << Path << "\n";
	if (is_acyclic())
	{
		cout << "Граф ацикличен";
	}
	else
	{
		cout << "Граф не ацикличен, так как есть цикл:\n";
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << "\t";
		}
	}
	cout << "\n\n";
	graph.clear();
	path.clear();
	nodes.clear();
	flag = false;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	get_graph("graph1.txt");
	myfunc("graph1.txt");
	get_graph("graph2.txt");
	myfunc("graph2.txt");
	get_graph("graph3.txt");
	myfunc("graph3.txt");
	get_graph("graph4.txt");
	myfunc("graph4.txt");
	get_graph("graph5.txt");
	myfunc("graph5.txt");
	system("pause");
	return 0;
}
