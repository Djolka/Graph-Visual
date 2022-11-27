#include "Headers/Graph.h"


bool Graph::isWeighted() const {
    return _weighted;
}

bool Graph::isUnweighted() const {
    return !_weighted;
}

bool Graph::isDirected() const {
    return _directed;
}

bool Graph::isUndirected() const {
    return !_directed;
}
