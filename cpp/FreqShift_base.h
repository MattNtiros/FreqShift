#ifndef FREQSHIFT_IMPL_BASE_H
#define FREQSHIFT_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Resource_impl.h>
#include <ossie/ThreadedComponent.h>

#include <bulkio/bulkio.h>

class FreqShift_base : public Resource_impl, protected ThreadedComponent
{
    public:
        FreqShift_base(const char *uuid, const char *label);
        ~FreqShift_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:
        // Member variables exposed as properties
        float frequency_shift;

        // Ports
        bulkio::InFloatPort *dataFloat_in;
        bulkio::OutFloatPort *dataFloat_out;

    private:
};
#endif // FREQSHIFT_IMPL_BASE_H
