#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <string.h>

using namespace std;

typedef pair<int, int> int_pair;

struct arc
{
	int surs;
	int dest;
	int pond;
};

class Graf
{

public:

	int V, E;
	vector<arc> arce;
	vector<int_pair>* adj;

	Graf(int V, int E);
	~Graf();

	//vector<int> bellman_ford(int s);

	void jhonson_alg();
};

Graf::Graf(int V, int E)
{
	this->V = V;
	this->E = E;
	adj = new vector<int_pair>[V + 1];
}

Graf::~Graf()
{
	delete[] this->adj;
}

vector<int> bellman_ford(int V, vector<arc> arce, int s)
{
	vector<int> dist(V + 1, INT_MAX);
	dist[s] = 0;

	for (int i = 1; i < V; i++)
	{
		for (auto& arc_ : arce)
		{
			int u = arc_.surs;
			int v = arc_.dest;
			int w = arc_.pond;
			if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
			}
		}
	}

	for (auto& arc_ : arce)
	{
		int u = arc_.surs;
		int v = arc_.dest;
		int w = arc_.pond;
		if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
		{
			return {};
		}
	}

	/*for (int i = 0; i < V; i++)
		cout << i << " -> " << dist[i] << " " << endl;*/
	return dist;
}

/*
0 -> 2147483647 -1
1 -> 0 - 1
2 -> 2 3
3 -> 4 4
4 -> 7 1
5 -> - 2 2
*/

vector<int> dijkstra(int V, vector<int_pair>* adj, int s)
{
	// indexare de la 0 la varfuri

	vector<int> dist(V + 1, INT_MAX);
	vector<int> parinte(V + 1, -1);

	dist[s] = 0;

	priority_queue<int_pair, vector<int_pair>, greater<int_pair>> PQ;
	PQ.push(make_pair(0, s));

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();

		//list<int_pair>::iterator it;
		for (auto& pereche : adj[u])
		{
			int v = pereche.first;
			int w = pereche.second;

			//cout << PQ.size() << " ";

			if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				parinte[v] = u;
				PQ.push(make_pair(dist[v], v));
			}
		}
	}

	return dist;
}


void Graf::jhonson_alg()
{
	// Adaugam noul nod si muchiile sale
	vector<arc> arce_nou = this->arce;

	for (int i = 0; i < V - 1; i++)
	{
		arc arc_nou;
		arc_nou.surs = V;
		arc_nou.dest = i;
		arc_nou.pond = 0;
		arce_nou.push_back(arc_nou);
	}

	// BELLMAN_FORD pe noul graf pt determinare ponderi noi
	vector<int> pond_noi = bellman_ford(V+1, arce_nou, V);
	vector<int> pond{3,1,5,0};

	// Daca avem circuite de pondere negativa
	if (pond_noi.size() == 0)
	{
		cout << "Graful contine circuite de pondere negativa.\n";
		return;
	}

	// Calcul ponderi noi
	for (int i = 0; i < V; i++)
	{
		for (auto& pereche : adj[i])
		{
			pereche.second = pereche.second + pond_noi[i] - pond_noi[pereche.first];
		}
	}

	for(int i = 0;i < this->arce.size(); i++)
        cout << this->arce[i].surs << " " << this->arce[i].dest << " " << pond[i] << endl;


	// Dijkstra pentru fiecare nod
	for (int i = 0; i < this->V; i++)
	{
		vector<int> dist = dijkstra(V, adj, i);
		for (int j =0; j < this->V; j++)
		{
			dist[j] = dist[j] - pond_noi[i] + pond_noi[j];
			cout << dist[j] << " ";
		}
		cout << endl;
	}
}


int main(int argc, char** argv)
{
    /// citire
	int V, E;
	ifstream fin("a.in");
	fin >> V >> E;
	Graf g(V, E);

	arc arc_nou;
	for (int i = 0; i < E; i++)
	{
		fin >> arc_nou.surs;
		fin >> arc_nou.dest;
		fin >> arc_nou.pond;
		g.arce.push_back(arc_nou);
		g.adj[arc_nou.surs].push_back(make_pair(arc_nou.dest, arc_nou.pond));
	}

	g.jhonson_alg();
	//vector<arc> asd = g.arce;
	//vector<int> a = bellman_ford(g.V, asd, 0);
	return 0;
}
