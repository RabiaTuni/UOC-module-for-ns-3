/*
 * UOCPropagationLoss.cc
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "ns3/UOCPropagationLoss.h"

namespace UOC {


UOCPropagationLossModel::UOCPropagationLossModel() {
	m_TxPowerMAX = 0;
	m_TxPower = 0;
	m_FilterGain = 0;
	m_ConcentratorGain = 0;
	m_RxPower = 0;

	m_RXGain = 0 ;
	m_TXGain = 0;
		

}

void UOCPropagationLossModel::SetTxPower(double watt){
	this->m_TxPower = watt;
}
void UOCPropagationLossModel::SetTxPowerMAX(double MAX){
	this->m_TxPowerMAX = MAX;
}

double UOCPropagationLossModel::GetTxPower(){
	return this->m_TxPower;
}

double UOCPropagationLossModel::GetTxPowerMAX(){
	return this->m_TxPowerMAX;
//std::cout<<"m_TxPowerMAX(1) = "<<m_TxPowerMAX<<std::endl;
}


void UOCPropagationLossModel::SetFilterGain(double gain){
	this->m_FilterGain = gain;
}

double UOCPropagationLossModel::GetFilterGain(){
	return this->m_FilterGain;
}

void UOCPropagationLossModel::SetConcentratorGain(double cGain){
	this->m_ConcentratorGain = cGain;
}

double UOCPropagationLossModel::GetConcentratorGain(){
	return this->m_ConcentratorGain;
}

double UOCPropagationLossModel::DoCalcRxPower(double txPowerDbm, ns3::Ptr<ns3::MobilityModel> aTX,ns3::Ptr<ns3::MobilityModel> bRX) const{
	double distance = this->GetDistance(aTX,bRX);
//	std::cout<< " Distance = " << distance << std::endl;
	double Ar = 1.1e-6;  //receiver/photodetector area(m^2)
	int Beta = 0; //inclination angle = receiver's normal w.r.t light beam(rad)
	double theta = 0.5; // transmitter beam divergence also called semiangle (rad)
	double At = 1e-5; // transmitter size (m^2)//(10mm^2)
	double pi = 3.14;
	double cd = 0.043 * distance; //attenuation coefficient of pure sea water (m^-1) * distance
//	double cd = 0.151 * distance; //attenuation coefficient of clean ocean water (m^-1) * distance
//	double cd = 0.298 * distance; //attenuation coefficient of coastal ocean water (m^-1) * distance
//	double cd = 2.190 * distance; //attenuation coefficient of turbid harbor water (m^-1) * distance
	double exponent_cd = exp(-cd); // e^-cd
	double cos_theta = 0.8775; 
	std::cout<<"txPowerDbm = "<<txPowerDbm<<std::endl;
	
	double pRX = ((2* txPowerDbm * Ar)/ (((pi * std::pow(distance,2) * (1-cos_theta)) + 2 * At))) * exponent_cd; // gives received power in dBm
	//double watts;
	//watts = pow (10, pRX/10)/ 1000;  // converts received power from dBm to watts for calculations of SNR
	std::cout<<" Received power = " << pRX <<" at distance = "<< distance <<std::endl;
	return pRX;
}

double UOCPropagationLossModel::GetRxPower(){
	return this->m_RxPower;
}

void UOCPropagationLossModel::SetRXPower(double wattTX, ns3::Ptr<ns3::MobilityModel> aTX,
			ns3::Ptr<ns3::MobilityModel> bRX){
	this->m_RxPower = this->DoCalcRxPower(wattTX,aTX,bRX);
}

int64_t UOCPropagationLossModel::DoAssignStreams(int64_t stream){
	return stream;
}

double UOCPropagationLossModel::GetDistance(ns3::Ptr<ns3::MobilityModel> aTX, ns3::Ptr<ns3::MobilityModel> bRX) const{
	double dist = 0;
	Vector tx = aTX->GetPosition();
	Vector rx = bRX->GetPosition();
	dist = std::pow((tx.x-rx.x),2) + std::pow((tx.y-rx.y),2) + std::pow((tx.z-rx.z),2) ;
	dist = std::sqrt(dist);
	return dist;
}

void UOCPropagationLossModel::SetTXGain(double txgain){
	this->m_TXGain = txgain;
}

double UOCPropagationLossModel::GetTXGain(){
	return this->m_TXGain;
}

void UOCPropagationLossModel::SetRXGain(double rxgain){
	this->m_RXGain = rxgain;
}

double UOCPropagationLossModel::GetRXGain(){
	return this->m_RXGain;
}

UOCPropagationLossModel::~UOCPropagationLossModel() {

}

} /* namespace UOC */

