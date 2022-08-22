/*
 * UOCNetDevice.cc
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "ns3/UOCNetDevice.h"

namespace UOC {

UOC_NetDevice::UOC_NetDevice() {
	m_mobilityModel = ns3::CreateObject<UOCMobilityModel>();
	m_mobilityModel->SetAzimuth(0);
	m_mobilityModel->SetElevation(0);
	m_mobilityModel->SetPosition(ns3::Vector(0.0,0.0,0.0));
}


double UOC_NetDevice::GetAzmuth(){
	return this->m_mobilityModel->GetAzimuth();
}

void UOC_NetDevice::SetAzmuth(double az){
	this->m_mobilityModel->SetAzimuth(az);
}

ns3::Vector UOC_NetDevice::GetPosition(){
	return this->m_mobilityModel->GetPosition();
}

void UOC_NetDevice::SetPosition(ns3::Vector position){
	m_mobilityModel->SetPosition(position);
}

double UOC_NetDevice::GetElevation(){
	return m_mobilityModel->GetElevation();
}

void UOC_NetDevice::SetElevation(double elevation){

	m_mobilityModel->SetElevation(elevation);
}

ns3::Ptr<UOCMobilityModel> UOC_NetDevice::GetMobilityModel(){
	return m_mobilityModel;
}
void UOC_NetDevice::SetMobilityModel(ns3::Ptr<UOCMobilityModel> model){
	m_mobilityModel = model;
}


UOC_NetDevice::~UOC_NetDevice() {

}

} /* namespace UOC */

