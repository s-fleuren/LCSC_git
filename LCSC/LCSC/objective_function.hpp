#pragma once

namespace lcsc {
	double objective_trivial(std::vector<uint64_t> bits, graph g);
	double objective_max_degree(std::vector<uint64_t> bits, graph g);
	double objective_degree(std::vector<uint64_t> bits, graph g);
	double objective_degree_plus(std::vector<uint64_t> bits, graph g);
}