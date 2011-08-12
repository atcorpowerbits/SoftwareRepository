#include "stdafx.h"
#include "dal_stub.h"
#include "dal_stub_constants.h"
#include "DalCommon.h"
#include <msclr\lock.h>

using namespace System;
using namespace msclr;

namespace AtCor{ 
	namespace Scor { 
		
		namespace DataAccess{

				/**
				* @class DalCountdownTimerEventArgs
				* @brief Class to contain arguments for OnDalCountdownTimerEvent.
				*/
				public ref class DalCountdownTimerEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short data;

						/**
						* Constructor for the class.
						*
						* @param[in] data	The data for the event (countdown timer).						
						*/
						DalCountdownTimerEventArgs(unsigned short data);
				};

				/**
				* @class DalCuffStatusEventArgs
				* @brief Class to contain arguments for OnDalCuffStatusEvent.
				*/
				public ref class DalCuffStatusEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short data;

						/**
						* Constructor for the class.
						*
						* @param[in] data	The data for the event (countdown timer).						
						*/
						DalCuffStatusEventArgs(unsigned short data);
				};

				/**
				* @class DalModuleErrorAlarmEventArgs
				* @brief Class to contain arguments for OnDalModuleErrorAlarmEvent.
				*/
				public ref class DalModuleErrorAlarmEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short errorAlarmStatus;
//						property String^ source;

						/**
						* Constructor for the class.
						*
						* @param[in] state	The state of the last event (error/alarm/none).						
						* @param[in] source	The source of the last event (source id).						
						*/
//						DalModuleErrorAlarmEventArgs(unsigned short state, unsigned int source);
						DalModuleErrorAlarmEventArgs(unsigned short state);
					private:
//						String^ MapErrorSourceToString(unsigned short source);
//						String^ MapAlarmSourceToString(unsigned short source);
				};

				/**
				* Delegate for countdown timer event
				*/
				public delegate void DalCountdownTimerEventHandler(Object^ sender, DalCountdownTimerEventArgs ^ args);

				/**
				* Delegate for cuff status event
				*/
				public delegate void DalCuffStatusEventHandler(Object^ sender, DalCuffStatusEventArgs ^ args);

				/**
				* Delegate for cuff status event
				*/
				public delegate void DalModuleErrorAlarmEventHandler(Object^ sender, DalModuleErrorAlarmEventArgs ^ args);

				/**
				* @class DalEventContainerStub
				* @brief A container stub to initialize missing events for the DAL.
				*/
				public ref class DalEventContainerStub
				{
					private:
						static DalEventContainerStub^ _instance = gcnew DalEventContainerStub();
						DalEventContainerStub();
						DalEventContainerStub(const DalEventContainerStub^);
						DalEventContainerStub^ operator= (const DalEventContainerStub);

						DalCountdownTimerEventHandler^ _dalCountdownTimerEventHandler;
						DalCuffStatusEventHandler^ _dalCuffStatusEventHandler;
						DalModuleErrorAlarmEventHandler^ _dalModuleErrorAlarmEventHandler;

					public:
						/**
						* The current instance. Implemented as a singleton.
						*/
						static property DalEventContainerStub^ Instance
						{
							DalEventContainerStub^ get()
							{
								return DalEventContainerStub::_instance;
							};
						};

						/**
						* Countdown Timer event.
						*/
						event DalCountdownTimerEventHandler^ OnDalCountdownTimerEvent
						{
							void add(DalCountdownTimerEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCountdownTimerEventHandler += handler;
							}

							void remove(DalCountdownTimerEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCountdownTimerEventHandler -= handler;
							}

							void raise(Object^ sender, DalCountdownTimerEventArgs ^ args)
							{
								if(_dalCountdownTimerEventHandler)
									_dalCountdownTimerEventHandler->Invoke(sender, args);
							}
						}

						/**
						* Cuff Status event.
						*/
						event DalCuffStatusEventHandler^ OnDalCuffStatusEvent
						{
							void add(DalCuffStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCuffStatusEventHandler += handler;
							}

							void remove(DalCuffStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCuffStatusEventHandler -= handler;
							}

							void raise(Object^ sender, DalCuffStatusEventArgs ^ args)
							{
								if(_dalCuffStatusEventHandler)
									_dalCuffStatusEventHandler->Invoke(sender, args);
							}
						}

						/**
						* Module Status event.
						*/
						event DalModuleErrorAlarmEventHandler^ OnDalModuleErrorAlarmEvent
						{
							void add(DalModuleErrorAlarmEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalModuleErrorAlarmEventHandler += handler;
							}

							void remove(DalModuleErrorAlarmEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalModuleErrorAlarmEventHandler -= handler;
							}

							void raise(Object^ sender, DalModuleErrorAlarmEventArgs ^ args)
							{
								if(_dalModuleErrorAlarmEventHandler)
									_dalModuleErrorAlarmEventHandler->Invoke(sender, args);
							}
						}

				}; // End class DalEventContainerStub
		}
	}
}