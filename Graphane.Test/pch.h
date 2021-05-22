// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
// add headers that you want to pre-compile here

#include "../Graphane/node.h"
#include "../Graphane/edge.h"

#include "../Graphane/graph.h"
#include "../Graphane/graph_builder.h"

#include "../Graphane/dijkstra.h"
#include "../Graphane/dijkstra_result.h"

#include "../Graphane/prim.h"
#include "../Graphane/prim_result.h"

#include "../Graphane/string_utils.h"

#endif //PCH_H
