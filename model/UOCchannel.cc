/*
 * UOCchannel.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "ns3/UOCchannel.h"
#include "ns3/log.h"

namespace UOC {

UOC_channel::UOC_channel():m_distanceBWTXandRX(0) {
	//NS_LOG_FUNCTION(this);
	this->m_loss = CreateObject< UOC::UOCPropagationLossModel > ();
	m_AvgPower = 0;
	this->m_SNR = CreateObject<UOC_SNR> ();
}

void UOC_channel::SetPropagationLossModel(ns3::Ptr<ns3::PropagationLossModel> loss){
	//NS_LOG_FUNCTION(this<<loss);
	this->m_loss = loss;
}

ns3::Ptr<ns3::PropagationLossModel> UOC_channel::GetPropagationLossModel(){
	//NS_LOG_FUNCTION(this);
	return this->m_loss;
}

void UOC_channel::SetPropagationDelayModel(ns3::Ptr<ns3::PropagationDelayModel> delay){
	//NS_LOG_FUNCTION(this<<delay);
	this->m_delay = delay;
}
ns3::Ptr<ns3::PropagationDelayModel> UOC_channel::GetPropagationDelayModel(){
	//NS_LOG_FUNCTION(this);
	return this->m_delay;
}

double UOC_channel::GetDistance(){
	//NS_LOG_FUNCTION(this);
	return this->m_distanceBWTXandRX;
}

void UOC_channel::SetDistance(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDevice> first =  ns3::DynamicCast< UOC_NetDevice >( this->GetDevice(0));
	ns3::Ptr<UOC_NetDevice> second =  ns3::DynamicCast< UOC_NetDevice >( this->GetDevice(1));

	ns3::Ptr<UOCPropagationLossModel>  l = ns3::DynamicCast< UOCPropagationLossModel >(this->m_loss);
	this->m_distanceBWTXandRX = l->GetDistance(first->GetMobilityModel(),second->GetMobilityModel());
}

void UOC_channel::DoCalcPropagationLoss(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDeviceTX> first =  ns3::DynamicCast<UOC_NetDeviceTX> ( this->GetDevice(0) );
	ns3::Ptr<UOC_NetDeviceRX> second =  ns3::DynamicCast<UOC_NetDeviceRX>( this->GetDevice(1) );
	double loss = 0;

	for(unsigned int i=0; i<first->GetTXOpticalPowerSignal().size();i++){
		loss = m_loss->CalcRxPower(first->GetTXOpticalPowerSignal().at(i) , first->GetMobilityModel(), second->GetMobilityModel());
		second->GetRXOpticalPowerSignal().at(i) = loss ;
	}

}

void UOC_channel::SetPropagationDelay(double delay){
	//NS_LOG_FUNCTION(this<<delay);
	//this->m_delay->set
}

double UOC_channel::DoCalcPropagationLossForSignal(int timeInstant){
	//NS_LOG_FUNCTION(this);
//	std::cout<<"timeInstant"<<timeInstant<<std::endl;
	ns3::Ptr<UOC_NetDeviceTX> first =  ns3::DynamicCast<UOC_NetDeviceTX> ( this->GetDevice(0));
	ns3::Ptr<UOC_NetDeviceRX> second =  ns3::DynamicCast<UOC_NetDeviceRX>( this->GetDevice(1));
	double loss = m_loss->CalcRxPower(first->GetTXOpticalPowerSignal().at(timeInstant), first->GetMobilityModel(), second->GetMobilityModel() );
	m_SNR->SetReceivedPower(loss);
std::cout<<"loss = "<<loss<<std::endl;
std::cout<<"GetTXOpticalPowerSignal = "<<first->GetTXOpticalPowerSignal().at(timeInstant)<<std::endl;
	return loss;
}

void UOC_channel::SetPorpagationLossParametersFromTX(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDeviceTX> tx =  ns3::DynamicCast< UOC_NetDeviceTX >( this->GetDevice(0));
	ns3::Ptr<UOC::UOCPropagationLossModel> loss =  ns3::DynamicCast< UOC::UOCPropagationLossModel >( this->m_loss);
	loss->SetTxPowerMAX(tx->GetTXPowerMax());
	loss->SetTXGain(tx->GetTXGain());
	//std::cout<<"m_TxPowerMAX (2) = "<<tx->GetTXPowerMax()<<std::endl;
}

void UOC_channel::SetPorpagationLossParametersFromRX(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDeviceRX> rx =  ns3::DynamicCast< UOC_NetDeviceRX >( this->GetDevice(1));
	ns3::Ptr<UOC::UOCPropagationLossModel> loss =  ns3::DynamicCast< UOC::UOCPropagationLossModel >( this->m_loss);
	loss->SetFilterGain(rx->GetFilterGain());
	loss->SetConcentratorGain(rx->GetConcentrationGain());
	loss->SetRXGain(rx->GetRXGain());

}

void UOC_channel::SetWavelength (int lower, int upper){	// sets upper and lower bound wavelength [nm]
	//NS_LOG_FUNCTION(this);
	this->m_SNR->SetWavelength(lower,upper);
}
void UOC_channel::SetTemperature (double t){		// sets the blackbody temperature of LED
	//NS_LOG_FUNCTION(this<<t);
	this->m_SNR->SetTemperature(t);
}

double UOC_channel::GetTemperature(){
	return this->m_SNR->GetTemperature();
}
void UOC_channel::SetReceivedPower (double p){	// sets the average received optical signal power
	//NS_LOG_FUNCTION(this<<p);
	this->m_SNR->SetReceivedPower(p);
}
void UOC_channel::CalculateNoiseVar (){	//calculates the noise variance
	//NS_LOG_FUNCTION(this<<A<<B<<Tk );
	ns3::Ptr<UOC_NetDeviceRX> rx = DynamicCast<UOC_NetDeviceRX>(this->GetDevice(1));
	this->m_SNR->CalculateNoiseVar(rx->GetPhotoDetectorArea() );

}
void UOC_channel::CalculateSNR (){		// caluclates the SNR value
	//NS_LOG_FUNCTION(this);
	this->m_SNR->CalculateSNR();
}

double UOC_channel::GetSNR () const{		// returns the signal-to-noise ratio (SNR)
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<UOC_NetDeviceRX> rx = DynamicCast<UOC_NetDeviceRX>(this->GetDevice(1));
	this->m_SNR->CalculateNoiseVar(rx->GetPhotoDetectorArea());
	m_SNR->CalculateSNR();
	return this->m_SNR->GetSNR();
}


void UOC_channel::SetAveragePower(double power){
	//NS_LOG_FUNCTION(this<<power);
	m_AvgPower = power;
}

double UOC_channel::GetAveragePower(){
	//NS_LOG_FUNCTION(this);
	return m_AvgPower;
}

void UOC_channel::SetElectricNoiseBandWidth (double b){	// sets the noise bandwidth
	this->m_SNR->SetElectricNoiseBandWidth(b);
}

double UOC_channel::GetNoiseBandwidth(){			//return the noise bandwidth
	return m_SNR->GetNoiseBandwidth();
}

UOC_channel::~UOC_channel() {

}


} /* namespace UOC */
