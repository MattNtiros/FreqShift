#include <iostream>
#include "ossie/ossieSupport.h"

#include "FreqShift.h"
int main(int argc, char* argv[])
{
    FreqShift_i* FreqShift_servant;
    Resource_impl::start_component(FreqShift_servant, argc, argv);
    return 0;
}

