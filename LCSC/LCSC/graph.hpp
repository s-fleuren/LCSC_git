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

	};
}