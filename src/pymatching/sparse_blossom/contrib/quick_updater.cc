#include "pymatching/sparse_blossom/contrib/quick_updater.h"

pm::QuickUpdater::QuickUpdater(pm::UserGraph& user_graph)
    : mwpm(user_graph.get_mwpm_with_search_graph()),
      normalising_constant(user_graph.get_edge_weight_normalising_constant(pm::NUM_DISTINCT_WEIGHTS)) {
}

void pm::QuickUpdater::update_edge_weight(int u, int v, double weight) {
    auto& mg = mwpm.flooder.graph;
    auto& sg = mwpm.search_flooder.graph;
    assert(weight >= 0);
    weight *= normalising_constant;
    // Clamp the new weight to avoid changing the normalising constant.
    pm::weight_int max_half_edge_weight = pm::NUM_DISTINCT_WEIGHTS - 1;
    pm::signed_weight_int w = weight > max_half_edge_weight ? max_half_edge_weight : (pm::signed_weight_int)round(weight);
    w *= 2;

    auto mn_u = &(mg.nodes[u]), mn_v = v < 0 ? nullptr : &(mg.nodes[v]);
    mn_u->neighbor_weights[mn_u->index_of_neighbor(mn_v)] = w;
    if (mn_v)
        mn_v->neighbor_weights[mn_v->index_of_neighbor(mn_u)] = w;

    auto sn_u = &(sg.nodes[u]), sn_v = v < 0 ? nullptr : &(sg.nodes[v]);
    sn_u->neighbor_weights[sn_u->index_of_neighbor(sn_v)] = w;
    if (sn_v)
        sn_v->neighbor_weights[sn_v->index_of_neighbor(sn_u)] = w;
}
