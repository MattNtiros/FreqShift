#include "FreqShift_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

FreqShift_base::FreqShift_base(const char *uuid, const char *label) :
    Resource_impl(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    float_in = new bulkio::InFloatPort("float_in");
    addPort("float_in", float_in);
    float_out = new bulkio::OutFloatPort("float_out");
    addPort("float_out", float_out);
}

FreqShift_base::~FreqShift_base()
{
    delete float_in;
    float_in = 0;
    delete float_out;
    float_out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void FreqShift_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Resource_impl::start();
    ThreadedComponent::startThread();
}

void FreqShift_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Resource_impl::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void FreqShift_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Resource_impl::releaseObject();
}

void FreqShift_base::loadProperties()
{
    addProperty(frequency_shift,
                0,
                "frequency_shift",
                "",
                "readwrite",
                "",
                "external",
                "configure");

}


