/*
 * UOCPropagationLoss.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Rabia Qadar
 */

#ifndef UOCPROPAGATIONLOSS_H_
#define UOCPROPAGATIONLOSS_H_

#include "ns3/point-to-point-channel.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/ptr.h"
#include "ns3/pointer.h"
#include "ns3/mobility-model.h"
#include "ns3/point-to-point-net-device.h"
#include <math.h>


using namespace ns3;

namespace UOC {

class UOCPropagationLossModel: public ns3::PropagationLossModel {

public:
	/**
	 * \breif Get the type ID.
	 * \return the object TypeId
	 */
	//static ns3::TypeId GetTypeId(void);
	//Constructor
	UOCPropagationLossModel();
	void SetTxPower(double watt);
	void SetTxPowerMAX(double MAX);

	double GetTxPower();
	double GetTxPowerMAX();


	void SetFilterGain(double gain);
	double GetFilterGain();

	void SetConcentratorGain(double cGain); //set concentration gain calculated in RX
	double GetConcentratorGain();

	void SetTXGain(double txgain);
	double GetTXGain();

	void SetRXGain(double rxgain);
	double GetRXGain();

	double GetDistance(ns3::Ptr<ns3::MobilityModel> aTX, ns3::Ptr<ns3::MobilityModel> bRX) const;

	double GetRxPower();

	void SetRXPower(double wattTX, ns3::Ptr<ns3::MobilityModel> aTX,
			ns3::Ptr<ns3::MobilityModel> bRX);



	double dotProduct(std::vector<double> v1, std::vector<double> v2) const;
	double magnitude(std::vector<double> v) const;

	~UOCPropagationLossModel();
private:
	/**
	 * \brief Copy constructor
	 *
	 * Defined and unimplemented to avoid misuse
	 */
	UOCPropagationLossModel(const UOCPropagationLossModel &);
	/**
	 * \brief Copy constructor
	 *
	 * Defined and unimplemented to avoid misuse
	 * \returns
	 */
	UOCPropagationLossModel & operator =(const UOCPropagationLossModel &);

	virtual double DoCalcRxPower(double txPowerDbm, ns3::Ptr<ns3::MobilityModel> aTX,ns3::Ptr<ns3::MobilityModel> bRX) const;

	virtual int64_t DoAssignStreams(int64_t stream);

	double m_TxPower;
	double m_TxPowerMAX;

	double m_FilterGain;
	double m_ConcentratorGain;
	double m_RxPower;

	double m_TXGain;
	double m_RXGain;

};

} /* namespace UOC */

#endif /* UOCPROPAGATIONLOSS_H_ */
