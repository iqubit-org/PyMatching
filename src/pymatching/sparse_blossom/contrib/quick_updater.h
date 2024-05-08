#ifndef PYMATCHING2_QUICK_UPDATER_H
#define PYMATCHING2_QUICK_UPDATER_H

#include <cmath>

#include "pymatching/sparse_blossom/driver/user_graph.h"

namespace pm {

class QuickUpdater {
   public:
    pm::Mwpm& mwpm;
    double normalising_constant;

    QuickUpdater(pm::UserGraph& user_graph);
    void update_edge_weight(int u, int v, double weight);
};

}

#endif  // PYMATCHING2_QUICK_UPDATER_H
