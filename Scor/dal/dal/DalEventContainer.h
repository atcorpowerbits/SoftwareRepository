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
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		
		namespace DataAccess{

				//obslolete; this event passes tonometer data NOT STATUS
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

				//obslolete; this event passes tonometer data NOT STATUS
				/**
				* Delegate for tonometer event
				*/
				public delegate void DalTonoMeterDataEventHandler(Object^ sender, DalTonometerDataEventArgs ^ args); //TODO:STUB


				//obsolete: cuff pulse data is now put into the buffer. It wont be sent through events
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
				
				//obsolete: cuff pulse data is now put into the buffer. It wont be sent through events
				
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
						* The alarm status.
						*/
						property DalErrorAlarmStatusFlag ErrorAlarmStatus;

						/**
						* Name of the source
						*/
						property String^ AlarmSourceName;

						/**
						* The source of the alarm as an enum
						*/
						property DalAlarmSource SpecificAlarmSource;

						property ScorException^ ScorExceptionObject; 

						/**
						* Constructor for the class.
						*
						* @param[in]	alarmStatus	The type of alarm raised.
						* @param[in]	alarmSourceName	The name of the alarm source from the Alarm Flags.	
						* @param[in]	alarmSourceEnum	The alarm source as a DalAlarmSource enum
						*/
						DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag alarmStatus, String^ alarmSourceName, DalAlarmSource alarmSourceEnum);

						/**
						* Constructor for the class.
						*
						* @param[in]	alarmStatus	The type of alarm raised.
						* @param[in]	alarmSourceName	The name of the alarm source from the Alarm Flags.	
						* @param[in]	alarmSourceEnum	The alarm source as a DalAlarmSource enum
						* @param[in]	scorExcptionObject	The exception object, if this event is being raised in liue of an exception throw.
						*/
						DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag alarmStatus, String^ alarmSourceName, DalAlarmSource alarmSourceEnum, ScorException^ scorExcptionObject);

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
				* @class DalUnusedStatusFlagEventArgs
				* @brief Class to contain arguments for OnDalUnusedFlagChangeEvent.
				*/
				public ref class DalUnusedStatusFlagEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property DalUnusedStatusFlagBit UnusedStatusFlagChanged;

						/**
						* The value of the flag 1 set/ 0 = reset
						*/
						property bool ValueSetReset;
						
						/**
						* Constructor for the class.
						*
						* @param[in] changedStatusFlag	The flag that was changed
						* @param[in]	setResetValue	The value to be set.
						*/
						DalUnusedStatusFlagEventArgs(DalUnusedStatusFlagBit changedStatusFlag, bool setResetValue);
				};

				/**
				* Delegate for unused status flag changed event
				*/
				public delegate void DalUnusedStatusFlagChangedEventHandler(Object^ sender, DalUnusedStatusFlagEventArgs ^args);

				//TS STUB
				/**
				* @class DalNIBPDataEventArgs
				* @brief Class to contain arguments for OnDalNIBPDataEvent.
				*/
				public ref class DalNIBPDataEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event.
						*/
						property unsigned short nibpError;
						property unsigned short nibpSP;
						property unsigned short nibpDP;
						property unsigned short nibpMP;
						property unsigned short nibpHR;
						
						/**
						* Constructor for the class.
						*
						* @param[in] error  NIBP Error code
						* @param[in] sp     NIBP Systolic value in mmHg
						* @param[in] dp     NIBP Systolic value in mmHg
						* @param[in] mp     NIBP Mean arterial pressure value in mmHg
						* @param[in] hr     NIBP Heart rate in beats per min
						*/
						DalNIBPDataEventArgs(unsigned short error,
											 unsigned short sp,
											 unsigned short dp,
											 unsigned short mp, 
											 unsigned short hr);
				};

 				/**
				* Delegate for NIBP data event
				*/
				public delegate void DalNIBPDataEventHandler(Object^ sender, DalNIBPDataEventArgs ^args);


				/**
				* @class DalEventContainer
				* @brief A container to initialize events for the DAL.
				*/
				public ref class DalEventContainer
				{
					private:
						static DalEventContainer^ _instance = gcnew DalEventContainer(); //instance variable. Implements singleton
						DalEventContainer(); //Empty constructor to implement singleton
						DalEventContainer(DalEventContainer^); //Overloaded copy contructor. Made private to implement singleton
						DalEventContainer^ operator= (DalEventContainer); //overloaded assignment operator. Private to implement singleton.

						DalTonoMeterDataEventHandler^ _dalTonoMeterDataEventHandler; //Handler for tonometer events //TODO:STUB
						DalCuffPulseEventHandler^ _dalCuffPulseEventHandler; //Handler for cuff puse events //TODO:STUB

						DalCuffStatusEventHandler^ _DalCuffStatusEventHandler; //handler for cuff status change events
			 
						DalModuleErrorAlarmEventHandler^     _dalModuleErrorAlarmEventHandler;

						DalTonometerStatusEventHandler^ _dalTonometerStatusEventHandler; //handler for tonometer status change events

						DalUnusedStatusFlagChangedEventHandler^ _dalUnusedStatusFlagChangedEventHandler; //unused status flag changed event handler

						//TS STUB
						DalNIBPDataEventHandler^ _dalNIBPDataEventHandler; // NIBP data event handler
						
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
									//Moved log comment to the top and uncommented it as per TS stub
									AtCor::Scor::CrossCutting::Logging::CrxLogger::Instance->Write("Deepak>>>> CuffStatus event raised in DAL: "+ args->CuffStateFlag.ToString() );
									_DalCuffStatusEventHandler->Invoke(sender, args);
								}
							}
						}


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
								if (nullptr == args )
								{
									//validation of param based on FxCop
									//No need to validate the sender as it is unimportant.
									return;
								}
								//Raise the event.
								if(_dalModuleErrorAlarmEventHandler)
								{
									_dalModuleErrorAlarmEventHandler->Invoke(sender, args);
									//AtCor::Scor::CrossCutting::Logging::CrxLogger::Instance->Write("Deepak>>>> Error Alarm event raised in DAL: "+ args->ErrorAlarmStatus.ToString() + " : " + args->AlarmSourceName  );
								}
							
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
								if (nullptr == args )
								{
									//validation of param based on FxCop
									//No need to validate the sender as it is unimportant.
									return;
								}

								//Raise the event.
								if(_dalTonometerStatusEventHandler)
								{
									_dalTonometerStatusEventHandler->Invoke(sender, args);
									//AtCor::Scor::CrossCutting::Logging::CrxLogger::Instance->Write("Deepak>>>> Tonometer event raised in DAL: "+ args->TonometerStateFlag.ToString() );
								}
							}
						}




						/**
						* Unused status flag raised event.
						*/
						event DalUnusedStatusFlagChangedEventHandler^ OnDalUnusedStatusFlagChangedEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the cignature of DalUnusedStatusFlagChangedEventHandler
							*/
							void add(DalUnusedStatusFlagChangedEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalUnusedStatusFlagChangedEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalUnusedStatusFlagChangedEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalUnusedStatusFlagChangedEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalTonometerDataEventArgs.
							*/
							void raise(Object^ sender, DalUnusedStatusFlagEventArgs^ args)
							{
								if (nullptr == args )
								{
									//validation of param based on FxCop
									//No need to validate the sender as it is unimportant.
									return;
								}

								//Raise the event.
								if(_dalUnusedStatusFlagChangedEventHandler)
								{
									_dalUnusedStatusFlagChangedEventHandler->Invoke(sender, args);
									////AtCor::Scor::CrossCutting::Logging::CrxLogger::Instance->Write("Deepak>>>> UnusedStatusFlagChangedEvent raised in DAL: "+ args->UnusedStatusFlagChanged.ToString() + " : " + args->ValueSetReset.ToString()  );
								}
							}
						}
				

						/**
						* Unused status flag raised event.
						*/
						event DalNIBPDataEventHandler^ OnDalNIBPDataEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the signature of DalNIBPDataEventHandler
							*/
							void add(DalNIBPDataEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_dalNIBPDataEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(DalNIBPDataEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_dalNIBPDataEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type DalTonometerDataEventArgs.
							*/
							void raise(Object^ sender, DalNIBPDataEventArgs^ args)
							{
								if (nullptr == args )
								{
									//validation of param based on FxCop
									//No need to validate the sender as it is unimportant.
									return;
								}

								//Raise the event.
								if(_dalNIBPDataEventHandler)
								{
									_dalNIBPDataEventHandler->Invoke(sender, args);
								}
							}
						}
						
				}; // End class DalEventContainer
		}
	}
}