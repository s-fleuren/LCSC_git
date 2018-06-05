#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace lcsc {

	class graph {
	public:
		graph(std::string filename);
		std::unordered_map<std::string, size_t> vertex_dict;
		std::vector<std::vector<size_t>*> neighbours;
		size_t size_V;
		std::vector<size_t> degree;
	};
}