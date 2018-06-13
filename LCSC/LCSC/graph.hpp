#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace lcsc {

	class graph {
	public:
		graph(std::string filename);
		graph(std::vector<uint64_t> bitstring, graph supergraph);
		void remove_node(int u);

		std::vector<char> is_node;
		std::vector<std::vector<int>*> neighbours;
		int size_V;
		int size_E;
		std::vector<int> degree;
		std::vector<std::vector<int>*> neighbours_outer;
		std::vector<std::vector<uint64_t>*> neighbours_bits;
		std::vector<uint64_t> bits;

		graph& operator=(const graph& other)
		{
			is_node = other.is_node;
			size_V = other.size_V;
			size_E = other.size_E;
			degree = other.degree;
			bits = other.bits;
			neighbours.clear();
			neighbours_outer.clear();
			neighbours_bits.clear();
			for (int i = 0; i < size_V; i++)
			{
				neighbours.push_back(new std::vector<int>(0));
				*neighbours[i] = *other.neighbours[i];
				neighbours_outer.push_back(new std::vector<int>(0));
				*neighbours_outer[i] = *other.neighbours_outer[i];
				neighbours_bits.push_back(new std::vector<uint64_t>(0));
				*neighbours_bits[i] = *other.neighbours_bits[i];
			}
			return *this;
		}
	};
}