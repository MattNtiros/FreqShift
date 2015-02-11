#!/usr/bin/env python
import unittest
import ossie.utils.testing
from ossie.utils import sb
import os
from time import sleep
from omniORB import any
import math
from scipy.odr.odrpack import Output


class ResourceTests(ossie.utils.testing.ScaComponentTestCase):
    """Test for all resource implementations in FreqShift"""
    
    def setUp(self):
        #set up 
        ossie.utils.testing.ScaComponentTestCase.setUp(self)
        self.src = sb.DataSource()
        self.sink = sb.DataSink()
        
        #connect 
        self.startComponent()
        self.src.connect(self.comp)
        self.comp.connect(self.sink)
        
        #starts sandbox
        sb.start()
        
        #variables
        
    def tearDown(self):
        #######################################################################
        # Simulate regular resource shutdown
        self.comp.releaseObject()
        
        self.comp.stop()
        sb.reset()
        sb.stop()
        ossie.utils.testing.ScaComponentTestCase.tearDown(self);
        
    def startComponent(self):
        #######################################################################
        # Launch the resource with the default execparams
        execparams = self.getPropertySet(kinds=("execparam",), modes=("readwrite", "writeonly"), includeNil=False)
        execparams = dict([(x.id, any.from_any(x.value)) for x in execparams])
        self.launch(execparams)

        #######################################################################
        # Verify the basic state of the resource
        self.assertNotEqual(self.comp, None)
        self.assertEqual(self.comp.ref._non_existent(), False)

        self.assertEqual(self.comp.ref._is_a("IDL:CF/Resource:1.0"), True)

        #######################################################################
        # Validate that query returns all expected parameters
        # Query of '[]' should return the following set of properties
        expectedProps = []
        expectedProps.extend(self.getPropertySet(kinds=("configure", "execparam"), modes=("readwrite", "readonly"), includeNil=True))
        expectedProps.extend(self.getPropertySet(kinds=("allocate",), action="external", includeNil=True))
        props = self.comp.query([])
        props = dict((x.id, any.from_any(x.value)) for x in props)
        # Query may return more than expected, but not less
        for expectedProp in expectedProps:
            self.assertEquals(props.has_key(expectedProp.id), True)

        #######################################################################
        # Verify that all expected ports are available
        for port in self.scd.get_componentfeatures().get_ports().get_uses():
            port_obj = self.comp.getPort(str(port.get_usesname()))
            self.assertNotEqual(port_obj, None)
            self.assertEqual(port_obj._non_existent(), False)
            self.assertEqual(port_obj._is_a("IDL:CF/Port:1.0"),  True)

        for port in self.scd.get_componentfeatures().get_ports().get_provides():
            port_obj = self.comp.getPort(str(port.get_providesname()))
            self.assertNotEqual(port_obj, None)
            self.assertEqual(port_obj._non_existent(), False)
            self.assertEqual(port_obj._is_a(port.get_repid()),  True)

        #######################################################################
        # Make sure start and stop can be called without throwing exceptions
        
    # TODO Add additional tests here
    #
    # See:
    #   ossie.utils.bulkio.bulkio_helpers,
    #   ossie.utils.bluefile.bluefile_helpers
    # for modules that will assist with testing resource with BULKIO ports
    
    def testFreqShiftReal(self):
        print "Testing functionality of FreqShift with real input"
        inputData = [float(x) for x in xrange(50)]
        self.comp.frequency_shift = 200
        self.src.push(inputData, complexData = False, sampleRate = 1000.0)
        
        outData = []
        count = 0
        while True:
            outData = self.sink.getData()
            if outData:
                break
            if count == 2000:
                break;
            sleep(.01)
            count+=1
            
        #need to add portion for time in between samples

        self.assertEqual(len(inputData)*2, len(outData))

        for x in range(len(inputData)):
            print x
            outData[2*x] = round(outData[2*x], 3)
            outData[2*x+1] = round(outData[2*x+1], 3)
            
            realPartExponential = math.cos(2.0*math.pi*x*self.comp.frequency_shift/1000.0)
            imagPartExponential = math.sin(2.0*math.pi*x*self.comp.frequency_shift/1000.0)
            print "Exponential: (", realPartExponential, ",", imagPartExponential, ")"
            
            resultReal = inputData[x] * realPartExponential
            resultImag = inputData[x] * imagPartExponential
            
            resultReal = round(resultReal, 3)
            resultImag = round(resultImag, 3)
            
            print "Computed Result: (", resultReal, ",", resultImag, ")"
            print "Actual Result: (", outData[2*x], ",", outData[2*x+1], ")" 
            print ""
            self.assertEqual(outData[2*x], resultReal)
            self.assertEqual(outData[2*x+1], resultImag)
            
    def testFreqShiftComplex(self):
        print "Testing functionality of FreqShift with complex input"
        inputData = [float(x) for x in xrange(50)]
        self.comp.frequency_shift = 400
        self.src.push(inputData, complexData = True, sampleRate = 1000.0)
        
        outData = []
        count = 0
        while True:
            outData = self.sink.getData()
            if outData:
                break
            if count == 1000:
                break;
            sleep(.01)
            count+=1
            
        #need to add portion for time in between samples

        self.assertEqual(len(inputData), len(outData))
        for x in range(len(inputData)/2):
            realPartExponential = math.cos(2*math.pi*x*self.comp.frequency_shift/1000.0)
            imagPartExponential = math.sin(2*math.pi*x*self.comp.frequency_shift/1000.0)
            outData[x] = round(outData[2*x], 3)
            outData[2*x+1] = round(outData[2*x+1], 3)
            
            print x
            print "Exponential: (", realPartExponential, ",", imagPartExponential, ")"
            
            resultReal = (inputData[2*x]*realPartExponential)-(inputData[2*x+1]*imagPartExponential)
            resultImag = (inputData[2*x+1]*realPartExponential)+(inputData[2*x]*imagPartExponential)
            
            resultReal = round(resultReal, 3)
            resultImag = round(resultImag, 3)
            
            print "Computed Result: (", resultReal, ",", resultImag, ")"
            print "Actual Result: (", round(outData[2*x], 3), ",", outData[2*x+1], ")" 
            print ""
            
            self.assertEqual(round(outData[2*x], 3), resultReal)
            self.assertEqual(round(outData[2*x+1], 3), resultImag)
        
if __name__ == "__main__":
    ossie.utils.testing.main("../FreqShift.spd.xml") # By default tests all implementations
