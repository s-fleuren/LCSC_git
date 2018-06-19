#pragma once

namespace lcsc {
	double objective_trivial(std::vector<uint64_t> bits, graph g);
	double objective_g_degree(std::vector<uint64_t> bits, graph g);
	double objective_f_degree_W(std::vector<uint64_t> bits, graph g);
	double objective_g_degree_W(std::vector<uint64_t> bits, graph g, std::vector<int> degree);
}