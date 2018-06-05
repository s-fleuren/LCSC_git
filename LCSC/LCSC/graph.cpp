#include "stdafx.h"

namespace lcsc {
	graph::graph(std::string filename)
	{
		std::ifstream graph_file;
		graph_file.open(filename);
		std::string line, key1, key2;
		bool key1_is_complete;
		size_V = 0;
		size_t u, v;
		bool edge_found;
		if (graph_file.is_open())
		{
			while (getline(graph_file, line))
			{
				key1 = "";
				key2 = "";
				key1_is_complete = false;
				for (auto c : line)
				{
					if (c != ' ')
					{
						if (!key1_is_complete) key1 += c;
						else key2 += c;
					}
					else key1_is_complete = true;
				}
				if (vertex_dict.find(key1) == vertex_dict.end())
				{
					vertex_dict[key1] = size_V;
					neighbours.push_back(new std::vector<size_t>(0));
					degree.push_back(0);
					size_V++;
				}
				if (vertex_dict.find(key2) == vertex_dict.end())
				{
					vertex_dict[key2] = size_V;
					neighbours.push_back(new std::vector<size_t>(0));
					degree.push_back(0);
					size_V++;
				}
				u = vertex_dict[key1];
				v = vertex_dict[key2];
				edge_found = false;
				for (auto a : *neighbours[u])
				{
					if (a == v) edge_found = true;
				}
				if (!edge_found)
				{
					neighbours[u]->push_back(v);
					neighbours[v]->push_back(u);
					degree[u]++;
					degree[v]++;
				}
			}
			graph_file.close();
		}
		else
		{
			std::cout << "Unable to open file";
			exit(1);
		}
	}
}
