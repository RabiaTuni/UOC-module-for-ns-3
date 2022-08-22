/*
 * UOCNetDeviceTX.cc
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "ns3/UOCNetDeviceTX.h"

namespace UOC {

UOC_NetDeviceTX::UOC_NetDeviceTX(): m_TMAX(60){
//UOC_NetDeviceTX::UOC_NetDeviceTX(): m_TMAX(100){
	m_semiangle = 70;
	m_angleOfRadiance = 0;
	m_lOrder = 1;
	m_TXGain = 0;
	m_bias = 0;
}

double UOC_NetDeviceTX::GetLambertianOrder(){
	return this->m_lOrder;
}

//before setting Lambertian Order make sure the semiangle value is set
//Need to setup error handling when semiangle is not set
void UOC_NetDeviceTX::SetLambertainOrder(){
	this->m_lOrder = (-1*log(2))/(log(cos(this->m_semiangle)));
}

void UOC_NetDeviceTX::AddTXOpticalPowerSignal(double power){
	this->m_TXOpticalPower.push_back(power);
}
std::vector<double>& UOC_NetDeviceTX::GetTXOpticalPowerSignal(){
	return this->m_TXOpticalPower;
}
double UOC_NetDeviceTX::GetOpticalPowerSignalAtInstant(int time){
	return this->m_TXOpticalPower.at(time);
}
void UOC_NetDeviceTX::SetTXOpticalPowerSignal(std::vector<double> &powerSignal){
	this->m_TXOpticalPower = powerSignal;
}


double UOC_NetDeviceTX::GetTXPowerMax(){
	return this->m_TMAX;
}

void UOC_NetDeviceTX::SetCapacity(int size){

	m_TXOpticalPower.reserve(size);
	m_signal.reserve(size);
}

double UOC_NetDeviceTX::GetSemiangle(){
	return this->m_semiangle;
}

void UOC_NetDeviceTX::SetSemiangle(double angle){
	this->m_semiangle = angle*M_PI/180;
	this->SetLambertainOrder();
}

void UOC_NetDeviceTX::SetAngleOfRadiance(double angle){
	this->m_angleOfRadiance = angle*M_PI/180;
}

double UOC_NetDeviceTX::GetAngleOfRadiance(){
	return this->m_angleOfRadiance;
}

double UOC_NetDeviceTX::GetTXGain(){
	return this->m_TXGain;
}
void UOC_NetDeviceTX::SetTXGain(){
	this->m_TXGain = ((this->m_lOrder + 1)/(2*M_PI))*std::pow(std::cos((long double)this->m_angleOfRadiance),2);
}


void UOC_NetDeviceTX::AddSignal(double signal){
	this->m_signal.push_back(signal);
}

std::vector<double>& UOC_NetDeviceTX::GetSignal(){
	return this->m_signal;
}

double UOC_NetDeviceTX::GetSignalAtInstant(int time){
	return this->m_signal.at(time);
}

void UOC_NetDeviceTX::SetSignal(std::vector<double> &signal){
	this->m_signal = signal;
}

void UOC_NetDeviceTX::SetBias(double bias){
	this->m_bias = bias;
}

double UOC_NetDeviceTX::GetBias(){
	return m_bias;
}


void UOC_NetDeviceTX::BoostSignal(){
//std::cout<<"hi"<<std::endl;
	m_TXOpticalPower.clear();

	for(unsigned int i=0;i< m_signal.size();i++){
		m_TXOpticalPower.push_back( (double)(m_signal.at(i) + m_bias) );
		if(m_TXOpticalPower.at(i) > m_TMAX){
			m_TXOpticalPower.at(i) = m_TMAX;

		}
//std::cout<<"m_TXOpticalPower(from boostsignal function) = "<<m_TXOpticalPower.at(0)<<std::endl;

	}
}

double UOC_NetDeviceTX::GetAveragePowerSignalPower(){
	double pMax = this->m_TXOpticalPower.at(0);
	double pMin = this->m_TXOpticalPower.at(m_TXOpticalPower.size()-1);
	return (pMax+pMin)/2;
}

double UOC_NetDeviceTX::GetAverageSignal(){
	double pMax = m_signal.at(0);
	double pMin = m_signal.at(m_signal.size()-1);
	return (pMax+pMin)/2;
}


UOC_NetDeviceTX::~UOC_NetDeviceTX() {

}

} /* namespace UOC */
