#include "stdafx.h"

namespace lcsc {
	double lcsc::objective_trivial(std::vector<uint64_t> bits, graph g)
	{
		double sum = 0;
		size_t vertex;
		bool has_edge;
		for (int outer = 0; outer < (g.size_V >> 6); outer++)
		{
			for (int inner = 0; inner < 64; inner++)
			{
				vertex = 64 * outer + inner;
				if ((bits[outer] & ((uint64_t)1 << inner)) != 0)
				{
					has_edge = false;
					for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
					{
						if ((bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i)) != 0)
						{
							has_edge = true;
							break;
						}
					}
					if (!has_edge) sum += 1;
				}
			}
		}
		for (int inner = 0; inner < g.size_V % 64; inner++)
		{
			vertex = (g.size_V >> 6) * 64 + inner;
			if ((bits.back() & ((uint64_t)1 << inner)) != 0)
			{
				has_edge = false;
				for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
				{
					if ((bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i)) != 0)
					{
						has_edge = true;
						break;
					}
				}
				if (!has_edge) sum += 1;
			}
		}
		return sum;
	}

	double objective_max_degree(std::vector<uint64_t> bits, graph g)
	{
		double sum = 0;
		size_t vertex;
		bool has_edge;
		for (int outer = 0; outer < (g.size_V >> 6); outer++)
		{
			for (int inner = 0; inner < 64; inner++)
			{
				vertex = 64 * outer + inner;
				if ((bits[outer] & ((uint64_t)1 << inner)) != 0)
				{
					has_edge = false;
					for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
					{
						if ((bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i)) != 0)
						{
							has_edge = true;
							break;
						}
					}
					if (!has_edge) sum += 1;
					else sum += (double)1 / (g.degree[vertex] + 1);
				}
			}
		}
		for (int inner = 0; inner < g.size_V % 64; inner++)
		{
			vertex = (g.size_V >> 6) * 64 + inner;
			if ((bits.back() & ((uint64_t)1 << inner)) != 0)
			{
				has_edge = false;
				for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
				{
					if ((bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i)) != 0)
					{
						has_edge = true;
						break;
					}
				}
				if (!has_edge) sum += 1;
				else sum += (double)1 / (g.degree[vertex] + 1);
			}
		}
		return sum;
	}

	double objective_degree(std::vector<uint64_t> bits, graph g)
	{
		double sum = 0;
		uint64_t common_bits;
		size_t inner, outer;
		double degree;
		for (int vertex = 0; vertex < g.size_V; vertex++)
		{
			inner = vertex % 64;
			outer = (vertex >> 6);
			if ((bits[outer] & ((uint64_t)1 << inner)) != 0)
			{
				degree = 0;
				for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
				{
					common_bits = bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i);
					for (int j = 0; j < 64; j++)
					{
						degree += common_bits % 2;
						common_bits >>= 1;
					}
				}
				sum += (double)1 / (1 + degree);
			}
		}
		return sum;
	}

	double objective_degree_plus(std::vector<uint64_t> bits, graph g)
	{
		double sum = 0;
		uint64_t common_bits;
		int inner, outer, value;
		std::vector<int> degree = std::vector<int>(g.size_V);
		for (int vertex = 0; vertex < g.size_V; vertex++)
		{
			inner = vertex % 64;
			outer = (vertex >> 6);
			if ((bits[outer] & ((uint64_t)1 << inner)) != 0)
			{
				degree[vertex] = 0;
				for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
				{
					common_bits = bits[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i);
					for (int j = 0; j < 64; j++)
					{
						degree[vertex] += common_bits % 2;
						common_bits >>= 1;
					}
				}
			}
		}
		for (int u = 0; u < g.size_V; u++)
		{
			inner = u % 64;
			outer = (u >> 6);
			if ((bits[outer] & ((uint64_t)1 << inner)) != 0)
			{
				value = -1;
				for (auto v : *g.neighbours[u])
				{
					if (degree[v] != 0 && degree[v] <= degree[u] && degree[v] > value)
					{
						value = degree[v];
					}
				}
				if (value == -1) value = degree[u];
				sum += (double)1 / (value + 1);
			}
		}
		return sum;
	}


}
