/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalConfigurationAndUsage.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalConfigurationAndUsage class
*/

#pragma once

#include "stdafx.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			public ref class DalConfigurationAndUsage
			{
				public:

					//0x0
					property String^ SerialNumberMainProcessorBoardPCB
					{

						String^ get();

						void set(String^ value);
					};

					//0x1
					property String^ ProcessorFirmwareVersionMainProcessorBoard
					{
						String^ get();

						void set(String^ value);
					};

					//0x2
					property String^ PLDSafetyFirmwareVersionMainProcessorBoard
					{
						String^ get();

						void set(String^ value);
					};

					//0x3
					property unsigned short HWConfigurationMainProcessorBoard
					{
						unsigned short get();

						void set(unsigned short value);
					};

					//0x4
					property String^ SerialNumberSuntechPCB
					{
						String^ get();

						void set(String^ value);
					};

					//0x5
					property String^ BPFirmwareVersionSuntech
					{
						String^ get();

						void set(String^ value);
					};

					//0x6
					property String^ SafetyFirmwareVersionSuntech
					{
						String^ get();

						void set(String^ value);
					};

					//0x7
					property unsigned short SystemConfigurationID
					{
						unsigned short get();

						void set(unsigned short value);
					};

					//0x8
					property String^ SerialNumberEM4
					{
						String^ get();

						void set(String^ value);
					};

					//0x9
					property unsigned int NumberOfPwvMeasurements
					{
						unsigned int get();

						void set(unsigned int value);
					};

					//0xA
					property unsigned int NumberOfPwaTonometerMeasurements
					{
						unsigned int get();

						void set(unsigned int value);
					};

					//0xB
					property unsigned int NumberOfPwaCuffMeasurements
					{
						unsigned int get();

						void set(unsigned int value);
					};

					//0xC
					property unsigned int NumberOfNibpMeasurements
					{
						unsigned int get();

						void set(unsigned int value);
					};

					//0xD
					property DateTime CalibrationDateMainProcessorBoard
					{
						DateTime get();

						void set(DateTime value);
					};

					//0xE
					property DateTime CalibrationDateSuntech
					{
						DateTime get();

						void set(DateTime value);
					};

					//0xF
					property DateTime TestDate
					{
						DateTime get();

						void set(DateTime value);
					};

					//0x10
					property DateTime SystemConfigurationChangeDate
					{
						DateTime get();

						void set(DateTime value);
					};




			}; //End class DalConfigurationAndUsage

					} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor


