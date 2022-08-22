# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

def configure(conf):
    conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('uocnew', ['core','network', 'mpi', 'mobility', 'propagation','point-to-point'])
    module.source = [
        'model/UOCnew.cc',
        'helper/UOCnew-helper.cc',
        'helper/UOCChannelHelper.cc',
        'helper/UOCDeviceHelper.cc',
        'model/UOCNetDevice.cc',
        'model/UOCchannel.cc',
        'model/UOCMobilityModel.cc',
        'model/UOCPropagationLoss.cc',
        'model/UOCNetDeviceRX.cc',
        'model/UOCNetDeviceTX.cc',
        'model/UOC_SNR.cc' ,
        'model/UOC-error-model.cc' ,
        ]

    module_test = bld.create_ns3_module_test_library('uocnew')
    module_test.source = [
        'test/UOC-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'uocnew'
    headers.source = [
        'model/UOCnew.h',
        'helper/UOCnew-helper.h',
        'helper/UOCChannelHelper.h',
        'helper/UOCDeviceHelper.h',
        'model/UOCNetDevice.h',
        'model/UOCchannel.h',
        'model/UOCMobilityModel.h',
        'model/UOCPropagationLoss.h',
        'model/UOCNetDeviceRX.h',
        'model/UOCNetDeviceTX.h',
        'model/UOC_SNR.h' ,
        'model/UOC-error-model.h' ,
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

