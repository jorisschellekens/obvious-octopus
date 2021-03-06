#include "graph/adjecencylistgraph.hpp"
#include "graph_ui/randomgraphlayout.hpp"

#include "xml/defaultelementimpl.hpp"
#include "xml/graphml.hpp"

#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <tuple>

using namespace std;
using namespace XML;
using namespace graph;
using namespace graph_ui;

int main()
{
    ifstream ifs;
    ifs.open ("/home/joris/g0.xml", ifstream::in);

    // read graph
    auto graphPtr = std::unique_ptr<IGraph<string>>(new AdjecencyListGraph<string>());
    ifs >> *graphPtr;

    // set preferences for pixel size of vertices
    auto vertexSize = 30;
    auto boundingBox = [vertexSize](const string &vertexId)
    {
        return make_tuple(vertexSize, vertexSize);
    };

    // setup layout parameters
    auto margin = 50;
    auto layoutMgr0 = unique_ptr<RandomGraphLayout<string>>(new RandomGraphLayout<string>());
    layoutMgr0.get()->setMaxXMargin(margin);
    layoutMgr0.get()->setMinXMargin(margin);
    layoutMgr0.get()->setMaxYMargin(margin);
    layoutMgr0.get()->setMinYMargin(margin);

    auto layout = layoutMgr0->layout(*graphPtr, boundingBox);

    return 0;
}
