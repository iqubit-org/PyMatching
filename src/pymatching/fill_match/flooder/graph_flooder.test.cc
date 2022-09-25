#include "pymatching/fill_match/flooder/graph_flooder.h"

#include "gtest/gtest.h"

#include "pymatching/fill_match/flooder/graph_fill_region.h"
#include "pymatching/fill_match/flooder_matcher_interop/mwpm_event.h"
#include "pymatching/fill_match/ints.h"

using namespace pm;

TEST(GraphFlooder, PriorityQueue) {
    GraphFlooder flooder(MatchingGraph(10, 64));
    auto &graph = flooder.graph;
    graph.add_edge(0, 1, 10, 0);
    graph.add_edge(1, 2, 10, 0);
    graph.add_edge(2, 3, 10, 0);
    graph.add_edge(3, 4, 10, 0);
    graph.add_edge(4, 5, 10, 0);
    graph.add_edge(5, 0, 10, 0);

    auto qn = [&](int i, int t) {
        graph.nodes[i].node_event_tracker.set_desired_event({&graph.nodes[i], cyclic_time_int{t}}, flooder.queue);
    };

    qn(0, 10);
    qn(1, 8);
    qn(2, 5);

    GraphFillRegion gfr;
    gfr.shrink_event_tracker.set_desired_event({&gfr, cyclic_time_int{70}}, flooder.queue);

    qn(4, 100);
    auto e = flooder.dequeue_valid();
    ASSERT_EQ(e.time, 5);
    ASSERT_EQ(e.tentative_event_type, LOOK_AT_NODE);
    ASSERT_EQ(e.data_look_at_node, &graph.nodes[2]);
    ASSERT_EQ(flooder.dequeue_valid().time, 8);
    ASSERT_EQ(flooder.dequeue_valid().time, 10);
    auto e6 = flooder.dequeue_valid();
    ASSERT_EQ(e6.time, 70);
    ASSERT_EQ(e6.tentative_event_type, LOOK_AT_SHRINKING_REGION);
    ASSERT_EQ(e6.data_look_at_shrinking_region, &gfr);
    ASSERT_EQ(flooder.dequeue_valid().time, 100);
}
