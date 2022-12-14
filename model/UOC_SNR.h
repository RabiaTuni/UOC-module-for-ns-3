#ifndef UOC_SNR_H
#define UOC_SNR_H
 

#include "ns3/object.h"
  
namespace ns3 {

class UOC_SNR : public Object	// This class is a subclass of Object class
{
	public:
		// Public methods
		static TypeId GetTypeId (void); // returns meta-information about PAMErrorModel class 

		UOC_SNR ();	// constructor
		virtual ~UOC_SNR ();	//destructor
		
		void SetWavelength (int lower, int upper);	// sets upper and lower bound wavelength [nm]
		void SetTemperature (double t);		// sets the blackbody temperature of LED
		double GetTemperature();
		void SetReceivedPower (double p);	// sets the average received optical signal power
		void SetElectricNoiseBandWidth (double b);	// sets the noise bandwidth
		double GetNoiseBandwidth();			//return the noise bandwidth

		void CalculateNoiseVar (double A);	//calculates the noise variance
		void CalculateSNR ();		// caluclates the SNR value
		double GetSNR () ;		// returns the signal-to-noise ratio (SNR)
		
	private:
		// Private methods called by other methods inside the class
		double IntegralPlanck();
		double IntegralRes();
		double SpectralRadiance(int wavelength, double temperature);
	
		// Private class members
		double noise_var;   // total noise variance
		double Pr;			// average received optical signal power
		double res;  		// responsitivity of receiver
		double SNR;  		// signal-to-noise ratio
		double SNR_dB;		// signal-to-noise ratio in dB
		double B;			// B: electric noise bandwidth
		
		int wavelength_lower;	// lower bound WaveLength [nm]
		int wavelength_upper;	// upper bound Wavelength [nm]
		double temp;  			// Blackbody temp of LED
		
		static double V_lambda[];
		static double Response[];
};

} // namespace ns3
#endif
