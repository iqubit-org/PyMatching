#ifndef PYMATCHING2_QUICK_UPDATER_PYBIND_H
#define PYMATCHING2_QUICK_UPDATER_PYBIND_H

#include "pybind11/pybind11.h"
#include "pymatching/sparse_blossom/contrib/quick_updater.h"

namespace py = pybind11;

namespace pm_pybind {

py::class_<pm::QuickUpdater> pybind_quick_updater(py::module &m);

void pybind_quick_updater_methods(py::module &m, py::class_<pm::QuickUpdater> &g);

}  // namespace pm_pybind

#endif  // PYMATCHING2_QUICK_UPDATER_PYBIND_H
