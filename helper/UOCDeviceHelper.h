/*
 * UOCDeviceHelper.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#ifndef UOCDEVICEHELPER_H_
#define UOCDEVICEHELPER_H_

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "ns3/UOCNetDeviceRX.h"
#include "ns3/UOCNetDeviceTX.h"
#include "ns3/core-module.h"
#include "ns3/UOC-error-model.h"


namespace UOC {


class UOC_DeviceHelper : public Object{
public:
	UOC_DeviceHelper();

	~UOC_DeviceHelper();

	void CreateTransmitter(std::string TXName);

	void CreateReceiver(std::string RXName);

	ns3::Ptr<UOC_NetDeviceTX> GetTransmitter(std::string devName);

	ns3::Ptr<UOC_NetDeviceRX> GetReceiver(std::string devName);


	std::vector<double> GenerateSignal(int size,double dutyRatio,double bias, double VMax,double VMin);

	void SetTXSignal(std::string devName,int size,double dutyRatio,double bias, double VMax,double VMin);

	void SetTrasmitterParameter(std::string devName, std::string paramName, double value );

	void SetTrasmitterBoost(std::string devName);

	void SetTrasmitterPosition(std::string devName, double x, double y, double z);

	void SetReceiverPosition(std::string devName, double x, double y, double z);

	void SetReceiverParameter(std::string devName, std::string paramName, double value );

	double GetReceiverParameter(std::string devName,std::string paramName);

private:
	std::map<std::string, ns3::Ptr<UOC_NetDeviceTX> > m_TXDevices;
	std::map<std::string, ns3::Ptr<UOC_NetDeviceRX> > m_RXDevices;

};

} /* namespace UOC */

#endif /* UOCDEVICEHELPER_H_ */
