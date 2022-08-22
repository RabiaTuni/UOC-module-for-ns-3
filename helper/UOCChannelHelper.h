/*
 * UOCChannelHelper.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#ifndef UOCCHANNELHELPER_H_
#define UOCCHANNELHELPER_H_

#include <map>
#include <iostream>
#include <string>
#include "ns3/core-module.h"
#include "ns3/UOCchannel.h"
#include "ns3/UOCDeviceHelper.h"
#include "ns3/net-device-container.h"
#include "ns3/queue.h"
#include "ns3/UOCNetDevice.h"
#include "ns3/UOCNetDeviceRX.h"
#include "ns3/UOCNetDeviceTX.h"
#include "ns3/object-factory.h"




namespace UOC {

class UOCChannelHelper : public Object {
public:
	UOCChannelHelper();

	void CreateChannel(std::string channelName);

	void SetChannelWavelength(std::string channelName, int lower, int upper);

	void SetPropagationLoss(std::string channelName, std::string propagationLossType);

	void SetPropagationDelay(std::string channelName, double value);

	void AttachTransmitter(std::string chName,std::string TXDevName, ns3::Ptr<UOC_DeviceHelper> devHelper);

	void AttachReceiver(std::string chName,std::string RXDevName, ns3::Ptr<UOC_DeviceHelper> devHelper);

	double GetChannelSNR(std::string chName);

	void SetChannelParameter(std::string chName,std::string paramName, double value);

	ns3::Ptr<UOC_channel> GetChannel(std::string chName);

	ns3::Ptr< UOC_NetDevice > GetDevice(std::string chName,uint32_t idx);

	//ns3::NetDeviceContainer Install(std::string chName,Ptr<Node> a, Ptr<Node> b);
	ns3::NetDeviceContainer Install (NodeContainer c);
	ns3::NetDeviceContainer InstallSimplex(std::string chName,Ptr<Node> a, Ptr<Node> b);
	ns3::NetDeviceContainer InstallDuplex(std::string chName,Ptr<Node> c, Ptr<Node> d);


	virtual ~UOCChannelHelper();

private:

	std::map< std::string, ns3::Ptr<UOC_channel> > m_channel;

	ObjectFactory m_queueFactory;

};

} /* namespace UOC */

#endif /* UOCCHANNELHELPER_H_ */
