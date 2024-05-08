import pymatching._cpp_pymatching as _cpp_pm


def QuickUpdater(matching):
    return _cpp_pm.QuickUpdater(matching._matching_graph)
