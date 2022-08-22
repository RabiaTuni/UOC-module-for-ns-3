/*
 * UOCDeviceHelper.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#include "UOCDeviceHelper.h"



namespace UOC {

UOC_DeviceHelper::UOC_DeviceHelper() {


}

void UOC_DeviceHelper::CreateTransmitter(std::string TXName){
	m_TXDevices[TXName] = CreateObject<UOC::UOC_NetDeviceTX>();
}

void UOC_DeviceHelper::CreateReceiver(std::string RXName){
	m_RXDevices[RXName] = CreateObject<UOC::UOC_NetDeviceRX>();
}

void UOC_DeviceHelper::SetTrasmitterParameter(std::string devName, std::string paramName, double value ){

	if(paramName=="SemiAngle"){
		m_TXDevices[devName]->SetSemiangle(value);
	}
	else if(paramName=="AngleOfRadiance"){
		m_TXDevices[devName]->SetAngleOfRadiance(value);
	}
	else if(paramName=="LambertianOrder"){
		m_TXDevices[devName]->SetLambertainOrder();
	}
	else if(paramName=="Gain"){
		m_TXDevices[devName]->SetTXGain();
	}
	else if(paramName=="Bias"){
		m_TXDevices[devName]->SetBias(value);
	}
	else if(paramName=="Azimuth"){
		m_TXDevices[devName]->SetAzmuth(value);
	}
	else if(paramName=="Elevation"){
		m_TXDevices[devName]->SetElevation(value);
	}
	else if(paramName=="DataRateInMBPS"){
		std::ostringstream strs;
		strs << value;
		std::string str = strs.str();
		str = str + "Mbps";
		DataRate drate(str);
		m_TXDevices[devName]->SetDataRate(drate);
	}


}

void UOC_DeviceHelper::SetTrasmitterPosition(std::string devName, double x, double y, double z){
	m_TXDevices[devName]->SetPosition(Vector(x,y,z));
}

void UOC_DeviceHelper::SetReceiverPosition(std::string devName, double x, double y, double z){
	m_RXDevices[devName]->SetPosition(Vector(x,y,z));
}

void UOC_DeviceHelper::SetTrasmitterBoost(std::string devName){
	m_TXDevices[devName]->BoostSignal();
}

void UOC_DeviceHelper::SetReceiverParameter(std::string devName, std::string paramName, double value ){
	if(paramName=="FilterGain"){
		m_RXDevices[devName]->SetFilterGain(value);
	}
	else if(paramName=="PhotoDetectorArea"){
		m_RXDevices[devName]->SetPhotoDectectorArea(value);
	}
	else if(paramName=="FOVAngle"){
		m_RXDevices[devName]->SetFOVAngle(value);
	}
	else if(paramName=="RefractiveIndex"){
		m_RXDevices[devName]->SetRefractiveIndex(value);
	}
	else if(paramName=="IncidenceAngle"){
		m_RXDevices[devName]->SetIncidenceAngle(value);
	}
	else if(paramName=="ConcentrationGain"){
		m_RXDevices[devName]->SetConcentrationGain();
	}
	else if(paramName=="RXGain"){
		m_RXDevices[devName]->SetRXGain();
	}
	else if(paramName=="SetModulationScheme"){
		if(value==0){
			m_RXDevices[devName]->SetScheme( "OOK" );
		}
		else if(value==1){
			m_RXDevices[devName]->SetScheme("PAM");
		}
		else if(value==2){
			m_RXDevices[devName]->SetScheme("VPPM");
		}
	}
	else if(paramName=="DutyCycle"){
		m_RXDevices[devName]->SetAlpha(value);
	}
	else if(paramName=="Beta"){
		m_RXDevices[devName]->SetBeta(value);
	}


}

double UOC_DeviceHelper::GetReceiverParameter(std::string devName,std::string paramName){
	if(paramName=="BER")
	{
		return this->m_RXDevices[devName]->CalculateErrorRateForErrorModel();
	}
	if(paramName=="SER")
	{
	return this->m_RXDevices[devName]->CalculateErrorRateForErrorModel();
	}
	if(paramName=="PER"){

	return this->m_RXDevices[devName]->CalculatePacketErrorRate();
	}

	return 0;
}

std::vector<double> UOC_DeviceHelper::GenerateSignal(int size,double dutyRatio,double bias, double VMax,double VMin){

	std::vector<double> result;
	result.reserve(size);

	for(int i=0;i<size;i++){

		if(i<size*dutyRatio){
			result.push_back(VMax+bias);
		}
		else{
			result.push_back(VMin+bias);
		}
	}
//std::cout<<"generate signal from UOCdevicehelper"<<std::endl;
	return result;

}

void UOC_DeviceHelper::SetTXSignal(std::string devName,int size,double dutyRatio,double bias, double VMax,double VMin){

	std::vector<double> r =  GenerateSignal(size, dutyRatio, bias, VMax, VMin) ;
	m_TXDevices[devName]->SetSignal(r);

}

ns3::Ptr<UOC_NetDeviceTX> UOC_DeviceHelper::GetTransmitter(std::string devName){

	return this->m_TXDevices[devName];

}
ns3::Ptr<UOC_NetDeviceRX> UOC_DeviceHelper::GetReceiver(std::string devName){

	return this->m_RXDevices[devName];
}



UOC_DeviceHelper::~UOC_DeviceHelper() {
	this->m_RXDevices.clear();
	this->m_TXDevices.clear();
}

} /* namespace UOC */
