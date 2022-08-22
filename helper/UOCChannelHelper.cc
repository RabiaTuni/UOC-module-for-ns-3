/*
 * UOCChannelHelper.cc
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "UOCChannelHelper.h"

namespace UOC {

UOCChannelHelper::UOCChannelHelper() {
	//NS_LOG_FUNCTION(this);
}

void UOCChannelHelper::CreateChannel(std::string channelName){
	//NS_LOG_FUNCTION(this);
	this->m_channel[channelName] = CreateObject<UOC_channel>();
}

void UOCChannelHelper::SetChannelParameter(std::string chName,std::string paramName, double value){
	if(paramName=="TEMP"){
		this->m_channel[chName]->SetTemperature(value);
	}
	else if(paramName=="ElectricNoiseBandWidth"){
		this->m_channel[chName]->SetElectricNoiseBandWidth(value);
	}
}

void UOCChannelHelper::SetPropagationLoss(std::string channelName, std::string propagationLossType){
	//NS_LOG_FUNCTION(this);
	if(propagationLossType=="UOCPropagationLoss"){
		this->m_channel[channelName]->SetPropagationLossModel(CreateObject<UOCPropagationLossModel>());
	}
}

void UOCChannelHelper::SetPropagationDelay(std::string channelName, double value){
	//NS_LOG_FUNCTION(this);
	this->m_channel[channelName]->SetPropagationDelay(value);

}

double UOCChannelHelper::GetChannelSNR(std::string chName){
	ns3::Ptr<UOC_NetDeviceRX> rx = DynamicCast<UOC_NetDeviceRX>(m_channel[chName]->GetDevice(1));
	this->m_channel[chName]->DoCalcPropagationLossForSignal(0);
	this->m_channel[chName]->CalculateNoiseVar();
	double snr =  this->m_channel[chName]->GetSNR();
	rx->SetSNRForErrorModel(snr);
	return snr;
}

void UOCChannelHelper::SetChannelWavelength(std::string channelName, int lower, int upper){
	this->m_channel[channelName]->SetWavelength(lower,upper);
}

void UOCChannelHelper::AttachTransmitter(std::string chName,std::string TXDevName, ns3::Ptr<UOC_DeviceHelper> devHelper){
	//NS_LOG_FUNCTION(this);
	this->m_channel[chName]->Attach(devHelper->GetTransmitter(TXDevName));
	this->m_channel[chName]->SetPorpagationLossParametersFromTX();
}

void UOCChannelHelper::AttachReceiver(std::string chName,std::string RXDevName, ns3::Ptr<UOC_DeviceHelper> devHelper){
	//NS_LOG_FUNCTION(this);
	this->m_channel[chName]->Attach(devHelper->GetReceiver(RXDevName));
	this->m_channel[chName]->SetPorpagationLossParametersFromRX();
}

ns3::Ptr<UOC_channel> UOCChannelHelper::GetChannel(std::string chName){
	//NS_LOG_FUNCTION(this);
	return m_channel[chName];
}

ns3::Ptr< UOC_NetDevice > UOCChannelHelper::GetDevice(std::string chName,uint32_t idx){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDevice> ans = DynamicCast<UOC_NetDevice>(m_channel[chName]->GetDevice(idx));

	return ans;
}

NetDeviceContainer UOCChannelHelper::InstallSimplex(std::string chName,Ptr<Node> a, Ptr<Node> b){

	//NS_LOG_FUNCTION(this);

	NetDeviceContainer container_1;

	Ptr<UOC_channel> ch = this->m_channel[chName];

//	std::cout<<ch->GetDevice(0)<<std::endl;
//	std::cout<<ch->GetDevice(1)<<std::endl;

//	std::cout<<ch->GetNDevices()<<std::endl;

	Ptr<UOC_NetDevice> devTX1 =  DynamicCast<UOC_NetDevice>(ch->GetDevice(0) );
	Ptr<UOC_NetDevice> devRX1 =  DynamicCast<UOC_NetDevice>(ch->GetDevice(1) );
//	Ptr<UOC_NetDevice> devTX1 =  ch->GetDevice(0);
//	Ptr<UOC_NetDevice> devRX1 =  ch->GetDevice(1);



	a->AddDevice(devTX1);
	//Ptr < Queue > queueA = m_queueFactory.Create<Queue>();
	//Ptr < DropTailQueue > queueA = CreateObject<DropTailQueue>();
	//devTX->SetQueue(queueA);

	b->AddDevice(devRX1);
	//Ptr < Queue > queueB = m_queueFactory.Create<Queue>();
	//devRX->SetQueue(queueB);

	/*bool useNormalChannel = true;
	ch = 0;

	if (MpiInterface::IsEnabled()) {
		uint32_t n1SystemId = a->GetSystemId();
		uint32_t n2SystemId = b->GetSystemId();
		uint32_t currSystemId = MpiInterface::GetSystemId();

		if (n1SystemId != currSystemId || n2SystemId != currSystemId) {
			useNormalChannel = false;
		}
	}*/

	container_1.Add(devTX1);
	container_1.Add(devRX1);

	return container_1;
}

//NetDeviceContainer UOCChannelHelper::Install (NodeContainer c)
//{
//  NS_ASSERT (c.GetN () == 2);
//  return Install (c.Get (0), c.Get (1));
//}
NetDeviceContainer UOCChannelHelper::InstallDuplex(std::string chName,Ptr<Node> c, Ptr<Node> d){

	NetDeviceContainer Container_2;

	Ptr<UOC_channel> ch = this->m_channel[chName];


		Ptr<UOC_NetDevice> devTX2 =  DynamicCast<UOC_NetDevice>(ch->GetDevice(1) );
		Ptr<UOC_NetDevice> devRX2 =  DynamicCast<UOC_NetDevice>(ch->GetDevice(0) );


	c->AddDevice(devTX2);
	d->AddDevice(devRX2);

	Container_2.Add(devTX2);
	Container_2.Add(devRX2);


		return Container_2;

	}

UOCChannelHelper::~UOCChannelHelper() {

}

}/* namespace UOC */
