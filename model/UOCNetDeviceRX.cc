/*
 * UOCNetDeviceRX.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "ns3/UOCNetDeviceRX.h"

namespace UOC {

UOC_NetDeviceRX::UOC_NetDeviceRX() {

	//NS_LOG_FUNCTION(this);

	m_filterGain = 0;
	m_photodetectorArea = 0;
	m_FOVangle = 0;
	m_refIndex = 0;
	m_angleOfIncidence = 0;
	m_concentrationGain = 0;
	m_RXGain = 0;
	m_bias = 0;
	this->m_error = ns3::CreateObject<ns3::UOC_ErrorModel>();


}


//use this function after setting up FOV and refractive index
void UOC_NetDeviceRX::SetConcentrationGain(){
	//NS_LOG_FUNCTION(this);
	this->m_concentrationGain = std::pow(this->m_refIndex,2)/std::pow((float)std::sin((float)m_FOVangle),2);
}

void UOC_NetDeviceRX::AddRXOpticalPowerSignal(double power){
	//NS_LOG_FUNCTION(this<<power);
	this->m_RXOpticalPower.push_back(power);
}
std::vector<double>& UOC_NetDeviceRX::GetRXOpticalPowerSignal(){
	//NS_LOG_FUNCTION(this);
	return this->m_RXOpticalPower;
}
double UOC_NetDeviceRX::GetOpticalPowerSignalAtInstant(int time){
	//NS_LOG_FUNCTION(this<<time);
	return this->m_RXOpticalPower.at(time);
}
void UOC_NetDeviceRX::SetRXOpticalPowerSignal(std::vector<double> &powerSignal){
	//NS_LOG_FUNCTION(this<<powerSignal);
	this->m_RXOpticalPower = powerSignal;
}



void UOC_NetDeviceRX::SetCapacity(int size){
	//NS_LOG_FUNCTION(this<<size);
	this->m_signal.reserve(size);
	this->m_RXOpticalPower.reserve(size);
}

double UOC_NetDeviceRX::GetFilterGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_filterGain;
}
void UOC_NetDeviceRX::SetFilterGain(double fgain){
	//NS_LOG_FUNCTION(this<<fgain);
	this->m_filterGain = fgain;
}

double UOC_NetDeviceRX::GetPhotoDetectorArea(){
	//NS_LOG_FUNCTION(this);
	return this->m_photodetectorArea;
}

void UOC_NetDeviceRX::SetPhotoDectectorArea(double pArea){
	//NS_LOG_FUNCTION(this<<pArea);
	this->m_photodetectorArea = pArea;
}

double UOC_NetDeviceRX::GetFOVAngle(){
	//NS_LOG_FUNCTION(this);
	return this->m_FOVangle;
}

void UOC_NetDeviceRX::SetFOVAngle(double angle){
	//NS_LOG_FUNCTION(this<<angle);
	this->m_FOVangle = angle*M_PI/180;
}

double UOC_NetDeviceRX::GetRefractiveIndex(){
	//NS_LOG_FUNCTION(this);
	return this->m_refIndex;
}
void UOC_NetDeviceRX::SetRefractiveIndex(double angle){
	//NS_LOG_FUNCTION(this << angle);
	this->m_refIndex = angle;
}


double UOC_NetDeviceRX::GetConcentrationGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_concentrationGain;
}


double UOC_NetDeviceRX::GetRXGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_RXGain;
}
void UOC_NetDeviceRX::SetRXGain(){
	//NS_LOG_FUNCTION(this);
	this->m_RXGain = std::cos(this->m_angleOfIncidence);
}


void UOC_NetDeviceRX::SetIncidenceAngle(double angle){
	//NS_LOG_FUNCTION(this << angle);
	this->m_angleOfIncidence = angle*M_PI/180;
}

ns3::UOC_ErrorModel::ModScheme UOC_NetDeviceRX::GeModulationtScheme (void) const{	 // returns the modulation scheme used
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetScheme();
}

void UOC_NetDeviceRX::SetScheme (std::string scheme){ // sets the value of the modulation scheme used
	//NS_LOG_FUNCTION(this<<scheme);
	this->m_error->SetScheme(scheme);

}

void UOC_NetDeviceRX::SetRandomVariableForErrorModel(ns3::Ptr<ns3::RandomVariableStream> ranVar){	// assigns a random variable stream to be used by this model
	//NS_LOG_FUNCTION(this<<ranVar);
	this->m_error->SetRandomVariable(ranVar);
}

int64_t UOC_NetDeviceRX::AssignStreamsForErrorModel (int64_t stream){	// assigns a fixed stream number to the random variables used by this model
	//NS_LOG_FUNCTION(this);
	return this->m_error->AssignStreams(stream);
}

double UOC_NetDeviceRX::GetSNRFromErrorModel (void) const{		// returns the signal-to-noise ratio (SNR)
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetSNR();
}

void UOC_NetDeviceRX::SetSNRForErrorModel (double snr){		// sets the SNR value
	//NS_LOG_FUNCTION(this<<snr);
	this->m_error->SetSNR(snr);
}

double UOC_NetDeviceRX::CalculateErrorRateForErrorModel (void){		// calculates the error rate value according to modulation scheme
	//NS_LOG_FUNCTION(this);
	return this->m_error->CalculateErrorRate();
}
double UOC_NetDeviceRX::CalculatePacketErrorRate(){		// calculates the error rate value according to modulation scheme
	//NS_LOG_FUNCTION(this);
	return this->m_error->CalculatePacketErrorRate();
}

bool UOC_NetDeviceRX::IsCorrupt (ns3::Ptr<ns3::Packet> pkt){	// determines if the packet is corrupted according to the error model
	//NS_LOG_FUNCTION(this<<pkt);
	return this->m_error->IsCorrupt(pkt);
}

// methods for PAM
int UOC_NetDeviceRX::GetModulationOrder (void) const{	// returns the modulation order (M)
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetModulationOrder();
}

void UOC_NetDeviceRX::SetModulationOrder (int m_order){	// sets the modulation order value
	//NS_LOG_FUNCTION(this<<m_order);
	return this->m_error->SetModulationOrder(m_order);
}

// methods for VPPM
double UOC_NetDeviceRX::GetAlpha(void) const{	// returns alpha value
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetAlpha();
}
void UOC_NetDeviceRX::SetAlpha (double a){		// sets alpha value
	//NS_LOG_FUNCTION(this);
	this->m_error->SetAlpha(a);
}

double UOC_NetDeviceRX::GetBeta(void) const{		// returns beta value
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetBeta();
}
void UOC_NetDeviceRX::SetBeta (double b){		// sets beta value
	//NS_LOG_FUNCTION(this<<b);
	return this->m_error->SetBeta(b);
}


double UOC_NetDeviceRX::GetIncidenceAngle(){
	return this->m_angleOfIncidence;
}


UOC_NetDeviceRX::~UOC_NetDeviceRX() {
	// TODO Auto-generated destructor stub
}

} /* namespace UOC */
