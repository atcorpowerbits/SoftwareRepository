/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEventContainer.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for Dal events.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include <msclr\lock.h>

using namespace System;
using namespace msclr;

namespace AtCor{ 
	namespace Scor { 
		
		namespace DataAccess{

				/**
				* @class DalTonometerDataEventArgs
				* @brief Class to contain arguments for OnDalTonometerDataEvent.
				*/
				public ref class DalTonometerDataEventArgs: public EventArgs //TODO:STUB
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short data;

						/**
						* Constructor for the class.
						*
						* @param[in] data	The data for the event (tonometer measurement).						
						*/
						DalTonometerDataEventArgs(unsigned short data);
				};

				/**
				* Delegate for tonometer event
				*/
				public delegate void DalTonoMeterDataEventHandler(Object^ sender, DalTonometerDataEventArgs ^ args); //TODO:STUB


				/**
				* @class DalCuffPulseEventArgs
				* @brief Class to contain arguments for OnDalCuffPulseEvent.
				*/
				public ref class DalCuffPulseEventArgs: public EventArgs //TODO:STUB
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short data;

						/**
						* Constructor for the class.
						*
						* @param[in] data	The data for the event (Cuff Pulse reading).						
						*/
						DalCuffPulseEventArgs(unsigned short data);
				};
				
				
				/**
				* Delegate for cuff pulse event
				*/
				public delegate void DalCuffPulseEventHandler(Object^ sender, DalCuffPulseEventArgs ^ args); //TODO:STUB

				

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
						property DalCuffStateFlags CuffStateFlag;
						/*property long countDownTimerValue;
						property long cuffPressure;*/

						/**
						* Constructor for the class.
						*
						* @param[in] cuffStateFlag	The data for the event (The resolved status flag).						
						*/
						DalCuffStatusEventArgs(DalCuffStateFlags cuffStateFlag);
				};

				/**
				* Delegate for cuff status changed event
				*/
				public delegate void DalCuffStatusEventHandler(Object^ sender, DalCuffStatusEventArgs ^ args);


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
						property DalErrorAlarmStatusFlag ErrorAlarmStatus;

						/**
						* Constructor for the class.
						*
						* @param[in] data	The data for the event (error or alarm raised event).						
						*/
						DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag data);
				};

				/**
				* Delegate for cuff status changed event
				*/
				public delegate void DalModuleErrorAlarmEventHandler(Object^ sender, DalModuleErrorAlarmEventArgs ^ args);



				/**
				* @class DalTonometerStatusEventArgs
				* @brief Class to contain arguments for OnDalTonometerStatusEvent.
				*/
				public ref class DalTonometerStatusEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property DalTonometerState TonometerStateFlag;
						
						/**
						* Constructor for the class.
						*
						* @param[in] tonometerStateFlag	The data for the event (The resolved tonometer state flag).						
						*/
						DalTonometerStatusEventArgs(DalTonometerState tonometerStateFlag);
				};

				/**
				* Delegate for cuff status changed event
				*/
				public delegate void DalTonometerStatusEventHandler(Object^ sender, DalTonometerStatusEventArgs ^args);



				/**
				* @class DalEventContainer
				* @brief A container to initialize events for the DAL.
				*/
				public ref class DalEventContainer
				{
					private:
						static DalEventContainer^ _instance = gcnew DalEventContainer(); //instance variable. Implements singleton
						DalEventContainer(); //Empty constructor to implement singleton
						DalEventContainer(const DalEventContainer^); //Overloaded copy contructor. Made private to implement singleton
						DalEventContainer^ operator= (const DalEventContainer); //overloaded assignment operator. Private to implement singleton.

						DalTonoMeterDataEventHandler^ _dalTonoMeterDataEventHandler; //Handler for tonometer events //TODO:STUB
						DalCuffPulseEventHandler^ _dalCuffPulseEventHandler; //Handler for cuff puse events //TODO:STUB

						DalCuffStatusEventHandler^ _DalCuffStatusEventHandler; //handler for cuff status change events

					//	DalCuffStatusEventHandler^ _dalCuffStatusEventHandler; //handler for cuff status change events

					//	DalModuleErrorAlarmEventHandler^     _dalModuleErrorAlarmEventHandler;

						 
						DalModuleErrorAlarmEventHandler^     _dalModuleErrorAlarmEventHandler;

						DalTonometerStatusEventHandler^ _dalTonometerStatusEventHandler; //handler for tonometer status change events



						
					public:
						/**
						* Pointer to the current instance as a property. 
						* Implements as a singleton.
						*/
						static property DalEventContainer^ Instance
						{
							//overloaded get() operator to return singleton instance
							DalEventContainer^ get()
							{
								return DalEventContainer::_instance;
							};
						};

						/**
						* Tonometer event.
						*/
						event DalTonoMeterDataEventHandler^ OnDalTonometerDataEvent //TODO:STUB
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the cignature of DalTonoMeterDataEventHandler
							*/
							void add(DalTonoMeterDataEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalTonoMeterDataEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalTonoMeterDataEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalTonoMeterDataEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalTonometerDataEventArgs.
							*/
							void raise(Object^ sender, DalTonometerDataEventArgs ^ args)
							{
								//Raise the event.
								if(_dalTonoMeterDataEventHandler)
									_dalTonoMeterDataEventHandler->Invoke(sender, args);
							}
						}

						/**
						* Cuff pulse event.
						*/
						event DalCuffPulseEventHandler^ OnDalCuffPulseEvent //TODO:STUB
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the signature of DalCuffPulseEventHandler.
							*/
							void add(DalCuffPulseEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalCuffPulseEventHandler += handler;
							}

							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalCuffPulseEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalCuffPulseEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalCuffPulseEventArgs.
							*/
							void raise(Object^ sender, DalCuffPulseEventArgs ^ args)
							{
								//Raise the event.
								if(_dalCuffPulseEventHandler)
									_dalCuffPulseEventHandler->Invoke(sender, args);
							}
						}


						/**
						* Cuff status changed event.
						*/
						event DalCuffStatusEventHandler^ OnDalCuffStatusEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the signature of DalCuffStatusEventHandler
							*/
							void add(DalCuffStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_DalCuffStatusEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalCuffStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_DalCuffStatusEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalCuffStatusEventArgs.
							*/
							void raise(Object^ sender, DalCuffStatusEventArgs ^ args)
							{
								if (!args)
								{
									return;
								}
								//Raise the event.
								if(_DalCuffStatusEventHandler)
								{
									_DalCuffStatusEventHandler->Invoke(sender, args);
								}
							}
						}

						//Deepak: No event to get EA source. It will be called by method
						///**
						//* Error or alarm source event.
						//*/
						//event DalErrorAlarmSourceEventHandler^ OnDalErrorAlarmSourceEvent
						//{
						//	/**
						//	* Registers specifed handler method as a listener to this event.
						//	*
						//	* @param[in] handler	The handler method to be registered as a listener. @n
						//	*						Should match the signature of DalErrorAlarmSourceEventHandler
						//	*/
						//	void add(DalErrorAlarmSourceEventHandler^ handler)
						//	{
						//		lock lockEvents(this);
						//		//add the specified handler as listener.
						//		_dalErrorAlarmSourceEventHandler += handler;
						//	}
						//	
						//	/**
						//	* Removes specifed handler method from the list of listners. @n
						//	* The handler can no  longer listen to this event.
						//	*
						//	* @param[in] handler	The handler method to be de-registered as a listener. @n
						//	*						Should be already added as a listener.
						//	*/
						//	void remove(DalErrorAlarmSourceEventHandler^ handler)
						//	{
						//		lock lockEvents(this);
						//		//Remove the specified handler from the list of listeners
						//		_dalErrorAlarmSourceEventHandler -= handler;
						//	}

						//	/*
						//	* Overloaded raise method.
						//	* Needed to raise an event.
						//	*
						//	* @param[in]	sender	Reference to object that raised the event.
						//	* @param[in]	args	The arguments for this event. Should be of the type DalErrorAlarmSourceEventArgs.
						//	*/
						//	void raise(Object^ sender, DalErrorAlarmSourceEventArgs ^ args)
						//	{
						//		//Raise the event.
						//		if(_dalErrorAlarmSourceEventHandler)
						//			_dalErrorAlarmSourceEventHandler->Invoke(sender, args);
						//	}
						//}


						/**
						* Error or alarm raised event.
						*/
						event DalModuleErrorAlarmEventHandler^ OnDalModuleErrorAlarmEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the signature of DalModuleErrorAlarmEventHandler
							*/
							void add(DalModuleErrorAlarmEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalModuleErrorAlarmEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalModuleErrorAlarmEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalModuleErrorAlarmEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalModuleErrorAlarmEventArgs.
							*/
							void raise(Object^ sender, DalModuleErrorAlarmEventArgs ^ args)
							{
								//Raise the event.
								if(_dalModuleErrorAlarmEventHandler)
									_dalModuleErrorAlarmEventHandler->Invoke(sender, args);
							}
						}

						
						/**
						* Tonometer status changed event.
						*/
						event DalTonometerStatusEventHandler^ OnDalTonometerStatusEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the signature of DalTonometerStatusEventHandler
							*/
							void add(DalTonometerStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalTonometerStatusEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalTonometerStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalTonometerStatusEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalTonometerStatusEventArgs.
							*/
							void raise(Object^ sender, DalTonometerStatusEventArgs ^args)
							{
								//Raise the event.
								if(_dalTonometerStatusEventHandler)
								{
									_dalTonometerStatusEventHandler->Invoke(sender, args);
									//AtCor::Scor::CrossCutting::Logging::CrxLogger::Instance->Write("Deepak>>>> Tonometer event raised in DAL: "+ args->CuffStateFlag.ToString() );
								}
							}
						}



				}; // End class DalEventContainer
		}
	}
}