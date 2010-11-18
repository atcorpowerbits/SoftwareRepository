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
				public ref class DalTonometerDataEventArgs: public EventArgs
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
				* @class DalCuffPulseEventArgs
				* @brief Class to contain arguments for OnDalCuffPulseEvent.
				*/
				public ref class DalCuffPulseEventArgs: public EventArgs
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
				* Delegate for tonometer event
				*/
				public delegate void DalTonoMeterDataEventHandler(Object^ sender, DalTonometerDataEventArgs ^ args);

				/**
				* Delegate for cuff pulse event
				*/
				public delegate void DalCuffPulseEventHandler(Object^ sender, DalCuffPulseEventArgs ^ args);


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

						DalTonoMeterDataEventHandler^ _dalTonoMeterDataEventHandler; //Handler for tonometer events
						DalCuffPulseEventHandler^ _dalCuffPulseEventHandler; //Handler for cuff puse events

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
						event DalTonoMeterDataEventHandler^ OnDalTonometerDataEvent
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
						event DalCuffPulseEventHandler^ OnDalCuffPulseEvent
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
				}; // End class DalEventContainer
		}
	}
}