#include "stdafx.h"
#include <iterator>

namespace lcsc {
	graph::graph(std::string filename)
	{
		std::ifstream graph_file;
		graph_file.open(filename);
		std::string line, size_V_str, size_E_str, key1, key2;
		int word_number;
		size_V = 0;
		int u, v;
		if (graph_file.is_open())
		{
			while (getline(graph_file, line))
			{
				word_number = 0;
				if (line[0] == 'p')
				{
					for (auto c : line)
					{
						if (c == ' ')
						{
							word_number++;
						}
						else if (word_number == 2)
						{
							size_V_str += c;
						}
						else if (word_number == 3)
						{
							size_E_str += c;
						}
					}
					size_V = std::stoi(size_V_str);
					size_E = std::stoi(size_E_str);
					for (int i = 0; i < size_V; i++)
					{
						neighbours.push_back(new std::vector<int>(0));
						degree.push_back(0);
						neighbours_outer.push_back(new std::vector<int>(0));
						neighbours_bits.push_back(new std::vector<uint64_t>(0));
						is_node.push_back(1);
					}
				}
				else if (line[0] == 'e')
				{
					key1 = "";
					key2 = "";
					for (auto c : line)
					{
						if (c == ' ')
						{
							word_number++;
						}
						else if (word_number == 1)
						{
							key1 += c;
						}
						else if (word_number == 2)
						{
							key2 += c;
						}
					}
					u = std::stoi(key1);
					v = std::stoi(key2);
					neighbours[u]->push_back(v);
					neighbours[v]->push_back(u);
					degree[u]++;
					degree[v]++;
				}
			}
			graph_file.close();
			int v_inner, v_outer;
			uint64_t index;
			for (u = 0; u < size_V; u++)
			{
				for (auto v : *neighbours[u])
				{
					v_inner = v % 64;
					v_outer = (v >> 6);
					index = std::distance(neighbours_outer[u]->begin(),
						find(neighbours_outer[u]->begin(), neighbours_outer[u]->end(), v_outer));
					if (index == neighbours_outer[u]->size())
					{
						neighbours_outer[u]->push_back(v_outer);
						neighbours_bits[u]->push_back((uint64_t)1 << v_inner);
					}
					else
					{
						neighbours_bits[u]->at(index) += ((uint64_t)1 << v_inner);
					}
				}
			}
			bits = one_bits_vector(size_V);
		}
		else
		{
			std::cout << "Unable to open file";
			exit(1);
		}
	}

	graph::graph(std::vector<uint64_t> bitstring_bits, graph supergraph)
	{
		*this = supergraph;
		bits = bitstring_bits;
		int inner, outer;
		for (int u = 0; u < supergraph.size_V; u++)
		{
			inner = u % 64;
			outer = (u >> 6);
			if ((bits[outer] & ((uint64_t)1 << inner)) == 0)
			{
				remove_node(u);
			}
		}
	}

	void graph::remove_node(int u)
	{
		int inner = u % 64;
		int outer = (u >> 6);
		uint64_t bit = ((uint64_t)1 << inner);
		uint64_t index;
		for (auto v : *neighbours[u]) {
			neighbours[v]->erase(find(neighbours[v]->begin(), neighbours[v]->end(), u));
			degree[v]--;
			index = std::distance(neighbours_outer[v]->begin(),
				find(neighbours_outer[v]->begin(), neighbours_outer[v]->end(), outer));
			neighbours_bits[v]->at(index) -= bit;
			if (neighbours_bits[v]->at(index) == 0)
			{
				neighbours_bits[v]->erase(neighbours_bits[v]->begin() + index);
				neighbours_outer[v]->erase(neighbours_outer[v]->begin() + index);
			}
		}
		size_E -= degree[u];
		size_V -= 1;
		is_node[u] = 0;
		neighbours[u]->clear();
		degree[u] = 0;
		neighbours_outer[u]->clear();
		neighbours_bits[u]->clear();
	}
}
