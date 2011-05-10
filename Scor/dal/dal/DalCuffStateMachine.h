/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCuffStateMachine.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for CuffStateMachine
*/
//************************************************
//This class is not a part of the deliverable for sprint 8. 
//It was done as a POC. It hasnt been integrated into the code but we have not removed the file
//Since we will be implementing it in sprint 9 anyway.
//**************************************************
#pragma once

#include "stdafx.h"
#include "DalEventContainer.h"
#include "IDalHandler.h"

using namespace System;
using namespace System::IO;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			public ref class DalCuffState 
			{
				public:
					DalCuffState();
					virtual void StartCapture(); //Start the simulation capture //TODO:STUB
					virtual void StartCapture(int captureTime, int samplingRate); //new parametrized method
					virtual void StopCapture(); //Stop the simulation capture
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					virtual String^ GetErrorAlarmSource(); 

				protected:
					virtual void ChangeState(DalCuffState^); //TODO: need to passa handle to the friend class
				internal:
					//IDalHandler^ _currentDevice; //TODO: do something about the warning
			};

			public ref class CuffDeflated: public DalCuffState
			{
			private:
				static CuffDeflated^ _instance = gcnew CuffDeflated();
			public:
				
				virtual void StartCapture() override;
				virtual void StartCapture(int captureTime, int samplingRate) override; //new parametrized method

				static property DalCuffState^ Instance
					{
						DalCuffState^ get()
						{
							return CuffDeflated::_instance;
						};
					};
			};

			public ref class CuffInflating: public DalCuffState
			{
				private:
				static CuffInflating^ _instance = gcnew CuffInflating();
			public:
				virtual void StopCapture() override;

				static property DalCuffState^ Instance
					{
						DalCuffState^ get()
						{
							return CuffInflating::_instance;
						};
					};
			};

			public ref class CuffInflated: public DalCuffState 
			{
				private:
				static CuffInflated^ _instance = gcnew CuffInflated();
			public:
				virtual void StopCapture() override;

				static property DalCuffState^ Instance
					{
						DalCuffState^ get()
						{
							return CuffInflated::_instance;
						};
					};
			};

			public ref class CuffDeflating: public DalCuffState
			{
				private:
					static CuffDeflating^ _instance = gcnew CuffDeflating();
				public:
					virtual void StartCapture() override;
					virtual void StartCapture(int captureTime, int samplingRate) override;

				static property DalCuffState^ Instance
					{
						DalCuffState^ get()
						{
							return CuffDeflating::_instance;
						};
					};
			};

			public ref class CuffDisconnected: public DalCuffState 
			{
				private:
					static CuffDisconnected^ _instance = gcnew CuffDisconnected();

			public:
//			virtual void GetConnectionStatus() override;

				static property DalCuffState^ Instance
					{
						DalCuffState^ get()
						{
							return CuffDisconnected::_instance;
						};
					};

			};

			public ref class CuffStateMachine
			{
				private:
					static CuffStateMachine^ _instance = gcnew CuffStateMachine();
					CuffStateMachine();
					CuffStateMachine(const CuffStateMachine^);
					CuffStateMachine^ operator= (const CuffStateMachine);

					static void ChangeState(DalCuffState^); //made static to call with CuffStateChangeListener. TODO, revert back if necessary.
					//static DalCuffState^ _currentCuffState;
					static void CuffStateChangeListener(Object^ sender, DalCuffStatusEventArgs ^ args);

				public:

					/**
					* Returns the current singleton instance.
					*/
					static property CuffStateMachine^ Instance
					{
						CuffStateMachine^ get()
						{
							return CuffStateMachine::_instance;
						};
					};

			};
		}
	}
}