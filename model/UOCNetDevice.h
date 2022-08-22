/*
 * UOCNetDevice.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#ifndef UOCNETDEVICE_H_
#define UOCNETDEVICE_H_

#include "ns3/point-to-point-net-device.h"
#include "ns3/point-to-point-channel.h"
#include "ns3/UOCMobilityModel.h"
#include "ns3/mobility-model.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/core-module.h"
#include "ns3/object.h"

namespace UOC {

class UOC_NetDevice: public ns3::PointToPointNetDevice {

public:
	UOC_NetDevice();

	virtual ~UOC_NetDevice();

	//returns the azmuth, i.e. facing of the device
	double GetAzmuth();
	//sets the azmuth,i.e. facing of the device
	void SetAzmuth(double az);

	//returns the x,y,z co-ordinates of the device
	ns3::Vector GetPosition();

	//sets the position of the device to a particular x,y,z value
	void SetPosition(ns3::Vector position);

	//returns the elevation of the device
	double GetElevation();

	//sets the elevation of the device
	void SetElevation(double elevation);

	//returns a pointer to the mobility model of the device
	ns3::Ptr<UOCMobilityModel> GetMobilityModel();

	//sets the mobility model of the device
	void SetMobilityModel(ns3::Ptr<UOCMobilityModel> model);



private:
	ns3::Ptr<UOCMobilityModel> m_mobilityModel;

};

} /* namespace UOC */

#endif /* UOCNETDEVICE_H_ */
