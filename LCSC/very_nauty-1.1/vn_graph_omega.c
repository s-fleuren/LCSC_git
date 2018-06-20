// KMB 2006 Jul 18
// process geng output (graph6 or sparse6) and compute clique number
// e.g.
//   geng 8 | ./graph_omega
//   genrang -P200/1000 20 1000 | ./graph_omega

#include "vn_graph.h"

inline int chi(graph_t g) {
  return graph_clique_number(g);
}

void graph_complement(graph_t gc, graph_t g){
	//gc = graph_new(nnodes(g));
	for (int i = 0; i < nnodes(g); i++)
	{
		for (int j = i + 1; j < nnodes(g); j++)
		{
			if (!graph_has_edge(g, i, j))
			{
				graph_add_edge(gc, i, j);
			}
		}
	}
}



int main() {
  FILE *fp;
  fp = fopen("reg82.g6", "r");
  graph_t g = geng_stringtograph(geng_getline(fp));
  graph_show(g);
  graph_t gc = graph_new(nnodes(g));
  graph_complement(gc, g);
  printf("%d\n", graph_clique_number(gc));
  //printf("mean=%g\n",histogram_mean(h));
  printf("press any key to exit.");
  getchar();
  return 0;
}
