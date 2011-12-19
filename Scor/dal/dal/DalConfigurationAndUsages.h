/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalConfigurationAndUsages.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalConfigurationAndUsages class.
*/

#pragma once

#include "stdafx.h"
#include "DalActiveDevice.h"

using namespace System;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalConfigurationAndUsages
			* @brief	Exposes main functionality for the DalConfigurationAndUsages module. Singleton class.
			*/
			public ref class DalConfigurationAndUsages
			{
			private:
				static DalConfigurationAndUsages^ _instance = gcnew DalConfigurationAndUsages();

				DalConfigurationAndUsages();
				DalConfigurationAndUsages(DalConfigurationAndUsages^){};
				DalConfigurationAndUsages^ operator= (DalConfigurationAndUsages){return this;};

			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalConfigurationAndUsages^ Instance
				{
					DalConfigurationAndUsages^ get()
					{
						return DalConfigurationAndUsages::_instance;
					};
				};

				/**
				* Returns the Serial Number main processor board PCB.
				*/
				property String^ SerialNumberMpb
				{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->SerialNumberMpb();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->SerialNumberMpb(data);
					}
				};
				
				/**
				* Returns the Processor Firmware Version main processor board PCB.
				*/
				property String^ ProcessorFirmwareVersionMpb
				{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->ProcessorFirmwareVersionMpb();	//Dummy
					};
					
					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->ProcessorFirmwareVersionMpb(data);
					}
				};

				/**
				* Returns the Pld Safety Firmware Version main processor board PCB.
				*/
				property String^ PldSafetyFirmwareVersionMpb
				{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->PldSafetyFirmwareVersionMpb();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->PldSafetyFirmwareVersionMpb(data);
					}
				};

				/**
				* Returns the Serial number Suntech PCB.
				*/
				property String^ SerialNumberSuntechPcb
					{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->SerialNumberSuntechPcb();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->SerialNumberSuntechPcb(data);
					}
				};

				/**
				* Returns the BP firmware version Suntech.
				*/
				property String^ BPFirmwareVersionSuntech
					{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->BPFirmwareVersionSuntech();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->BPFirmwareVersionSuntech(data);
					}
				};

				/**
				* Returns the Safety firmware Version Suntech.
				*/
				property String^ SafetyFirmwareVersionSuntech
					{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->SafetyFirmwareVersionSuntech();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->SafetyFirmwareVersionSuntech(data);
					}
				};

				/**
				* Returns the Serial number EM4.
				*/
				property String^ SerialNumberEm4
				{
					String^ get()
					{
						return DalActiveDevice::CurrentDevice->SerialNumberEm4();	//Dummy
					};

					void set(String^ data)
					{
						DalActiveDevice::CurrentDevice->SerialNumberEm4(data);
					}
				};


				/**
				* Returns the HW Configuration main processor board.
				*/
				property unsigned short HWConfigurationMpb
				{
					unsigned short  get()
					{
						return DalActiveDevice::CurrentDevice->HWConfigurationMpb();	//Dummy
					};

					void set(unsigned short data)
					{
						DalActiveDevice::CurrentDevice->HWConfigurationMpb(data);
					}
				};

				/**
				* Returns the System configuration ID.
				*/
				property unsigned short SystemConfigurationId
				{
					unsigned short  get()
					{
						return DalActiveDevice::CurrentDevice->SystemConfigurationId();	//Dummy
					};

					void set(unsigned short data)
					{
						DalActiveDevice::CurrentDevice->SystemConfigurationId(data);
					}
				};

				
				/**
				* Returns the Number of PWV measurements.
				*/
				property unsigned int NumberofPWVmeasurements
				{
					unsigned int get()
					{
						return DalActiveDevice::CurrentDevice->NumberofPWVmeasurements();	//Dummy
					};
					
					void set(unsigned int data)
					{
						DalActiveDevice::CurrentDevice->NumberofPWVmeasurements(data);
					}
				};

				/**
				* Returns the Number of PWA tonometer measurements.
				*/
				property unsigned int NumberofPWAtonometermeasurements
				{
					unsigned int get()
					{
						return DalActiveDevice::CurrentDevice->NumberofPWAtonometermeasurements();	//Dummy
					};

					void set(unsigned int data)
					{
						DalActiveDevice::CurrentDevice->NumberofPWAtonometermeasurements(data);
					}

				};

				/**
				* Returns the Number of PWA cuff measurements.
				*/
				property unsigned int NumberofPWAcuffmeasurements
				{
					unsigned int get()
					{
						return DalActiveDevice::CurrentDevice->NumberofPWAcuffmeasurements();	//Dummy
					};

					void set(unsigned int data)
					{
						DalActiveDevice::CurrentDevice->NumberofPWAcuffmeasurements(data);
					}
				};

				/**
				* Returns the Number of NIBP measurements.
				*/
				property unsigned int NumberOfNibpMeasurements
				{
					unsigned int get()
					{
						return DalActiveDevice::CurrentDevice->NumberOfNibpMeasurements();	//Dummy
					};

					void set(unsigned int data)
					{
						DalActiveDevice::CurrentDevice->NumberOfNibpMeasurements(data);
					}
				};

				
				/**
				* Returns the calibration date main processor board.
				*/
				property DateTime CalibrationDateMpb
				{
					DateTime get()
					{
						return DalActiveDevice::CurrentDevice->CalibrationDateMpb();	//Dummy
					};

					void set(DateTime data)
					{
						DalActiveDevice::CurrentDevice->CalibrationDateMpb(data);
					}
				};

				/**
				* Returns the calibration date Suntech.
				*/
				property DateTime CalibrationDateSuntech
				{
					DateTime get()
					{
						return DalActiveDevice::CurrentDevice->CalibrationDateSuntech();	//Dummy
					};

					void set(DateTime data)
					{
						DalActiveDevice::CurrentDevice->CalibrationDateSuntech(data);
					}
				};

				/**
				* Returns the test date.
				*/
				property DateTime TestDate
				{
					DateTime get()
					{
						return DalActiveDevice::CurrentDevice->TestDate();	//Dummy
					};

					void set(DateTime data)
					{
						DalActiveDevice::CurrentDevice->TestDate(data);
					}
				};

				/**
				* Returns the System configuration Change Date.
				*/
				property DateTime SystemConfigurationChangeDate
				{
					DateTime get()
					{
						return DalActiveDevice::CurrentDevice->SystemConfigurationChangeDate();	//Dummy
					};

					void set(DateTime data)
					{
						DalActiveDevice::CurrentDevice->SystemConfigurationChangeDate(data);
					}
				};

				/**
				* Returns the System configuration Change Date.
				*/
				property unsigned short NotchFilterEnable
				{
					unsigned short get()
					{
						return DalActiveDevice::CurrentDevice->NotchFilterEnable();	//Dummy
					};

					void set(unsigned short data)
					{
						DalActiveDevice::CurrentDevice->NotchFilterEnable(data);
					}
				};
			};
		}
	}
}