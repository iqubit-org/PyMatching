#include "pymatching/sparse_blossom/contrib/quick_updater.pybind.h"

#include "pybind11/numpy.h"
#include "pybind11/pybind11.h"

using namespace py::literals;

py::class_<pm::QuickUpdater> pm_pybind::pybind_quick_updater(py::module &m) {
    auto g = py::class_<pm::QuickUpdater>(m, "QuickUpdater");
    return g;
}

void pm_pybind::pybind_quick_updater_methods(py::module &m, py::class_<pm::QuickUpdater> &g) {
    g.def(py::init<pm::UserGraph&>(), "user_graph"_a);
    g.def("update_edge_weight", &pm::QuickUpdater::update_edge_weight, "u"_a, "v"_a, "weight"_a);
}
