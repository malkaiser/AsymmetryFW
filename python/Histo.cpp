#include <iostream>
#include <string>
#include "CLoop.h"
#include "TFile.h"
#include "TTree.h"

#include <boost/python.hpp>
#include "AnalysisWrapper.h"
#include "CLoopConfig.h"
using namespace boost::python;

BOOST_PYTHON_MODULE(Adder)
{
    class_<RootAdderWrapper>("Adder", init<std::string, std::string>())
        .def("AddTrees", &RootAdderWrapper::AddTrees)
    ;
}