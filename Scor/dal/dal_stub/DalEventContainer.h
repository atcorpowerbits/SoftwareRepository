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
				public delegate void DalTonometerDataEventHandler(Object^ sender, DalTonometerDataEventArgs ^ args);

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
						static DalEventContainer^ _instance = gcnew DalEventContainer();
						DalEventContainer();
						DalEventContainer(const DalEventContainer^);
						DalEventContainer^ operator= (const DalEventContainer);

						DalTonometerDataEventHandler^ _dalTonometerDataEventHandler;
						DalCuffPulseEventHandler^ _dalCuffPulseEventHandler;

					public:
						/**
						* The current instance. Implemented as a singleton.
						*/
						static property DalEventContainer^ Instance
						{
							DalEventContainer^ get()
							{
								return DalEventContainer::_instance;
							};
						};

						/**
						* Tonometer event.
						*/
						event DalTonometerDataEventHandler^ OnDalTonometerDataEvent
						{
							void add(DalTonometerDataEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalTonometerDataEventHandler += handler;
							}

							void remove(DalTonometerDataEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalTonometerDataEventHandler -= handler;
							}

							void raise(Object^ sender, DalTonometerDataEventArgs ^ args)
							{
								if(_dalTonometerDataEventHandler)
									_dalTonometerDataEventHandler->Invoke(sender, args);
							}
						}

						/**
						* Cuff pulse event.
						*/
						event DalCuffPulseEventHandler^ OnDalCuffPulseEvent
						{
							void add(DalCuffPulseEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCuffPulseEventHandler += handler;
							}

							void remove(DalCuffPulseEventHandler^ handler)
							{
								lock lockEvents(this);
								_dalCuffPulseEventHandler -= handler;
							}

							void raise(Object^ sender, DalCuffPulseEventArgs ^ args)
							{
								if(_dalCuffPulseEventHandler)
									_dalCuffPulseEventHandler->Invoke(sender, args);
							}
						}
				}; // End class DalEventContainer
		}
	}
}