/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxEventContainer.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for Cross-cutting events.
*/

#pragma once

#include "stdafx.h"
#include "CrxCrossCutting.h"
#include <msclr\lock.h>
#include "ScorException.h"

using namespace System;
using namespace msclr;


namespace AtCor {
	namespace Scor { 
		namespace CrossCutting
		{
				/**
				* @class CommsPortEventArgs
				* @brief Class to contain arguments for comms port settings change events.
				*/
				public ref class CommsPortEventArgs: public EventArgs
				{
					public:
						/**
						* Data for the event: The current setting selected in the GUI.
						*/
						property String^ commsPortSetting; 

						/**
						* Constructor for the class.
						*
						* @param[in] commsPortSetting	The string to intitialize this instance.						
						*/
						CommsPortEventArgs(String^ commsPortSetting); 
				};

				/**
				* @class CrxShowStatusEventArgs, 
				* @brief Class to contains arguments to status information or warning events.
				*/
				public ref class CrxShowStatusEventArgs : public EventArgs
				{
					public:
						/**
						* Data for the event: The message to be displayed in the GUI.
						*/						
						property ScorException^ ObjScorException;

						/**
						* Constructor for the class.
						*
						* @param[in] objScorException	The scorException object to ne manipulated.						
						*/
						CrxShowStatusEventArgs(ScorException^ objScorException); 
				};


				/**
				* Delegate for Comms port setting changed event.
				*/
				public delegate void CommsPortEventHandler(Object^ sender, CommsPortEventArgs ^ args);

				/**
				* Delegate for Show Status changed event.
				*/
				public delegate void CrxShowStatusEventHandler(Object^ sender, CrxShowStatusEventArgs ^ args);



				/**
				* @class CrxEventContainer
				* @brief A container to initialize events for the Cross cutting layer.
				*/
				public ref class CrxEventContainer
				{
					private:
						static CrxEventContainer^ _instance = gcnew CrxEventContainer(); //instance variable. Implements singleton
						CrxEventContainer(); //Empty constructor to implement singleton
						CrxEventContainer(CrxEventContainer^); //Overloaded copy contructor. Made private to implement singleton
						CrxEventContainer^ operator= (CrxEventContainer); //overloaded assignment operator. Private to implement singleton.

						CommsPortEventHandler^ _commsPortEventHandler; //Handler for Comms Port settings events

						CrxShowStatusEventHandler^ _showStatusEventHandler; //Handler for Show Status events

					public:
						/**
						* Pointer to the current instance as a property. 
						* Implements as a singleton.
						*/
						static property CrxEventContainer^ Instance
						{
							//overloaded get() operator to return singleton instance
							CrxEventContainer^ get()
							{
								return CrxEventContainer::_instance;
							};
						};

						/**
						* Comms port setting event.
						*/
						event CommsPortEventHandler^ OnCommsPortEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the cignature of CommsPortEventHandler
							*/
							void add(CommsPortEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_commsPortEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(CommsPortEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_commsPortEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type CommsPortEventArgs.
							*/
							void raise(Object^ sender, CommsPortEventArgs ^ args)
							{
								//Raise the event.
								if(_commsPortEventHandler)
									_commsPortEventHandler->Invoke(sender, args);
							}
						}

						/**
						* Show Status event.
						*/
						event CrxShowStatusEventHandler^ OnShowStatusEvent
						{
							/**
							* Registers specifed handler method as a listener to this event.
							*
							* @param[in] handler	The handler method to be registered as a listener. @n
							*						Should match the Signature of CrxShowStatusEventHandler
							*/
							void add(CrxShowStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//add the specified handler as listener.
								_showStatusEventHandler += handler;
							}
							
							/**
							* Removes specifed handler method from the list of listners. @n
							* The handler can no  longer listen to this event.
							*
							* @param[in] handler	The handler method to be de-registered as a listener. @n
							*						Should be already added as a listener.
							*/
							void remove(CrxShowStatusEventHandler^ handler)
							{
								lock lockEvents(this);
								//Remove the specified handler from the list of listeners
								_showStatusEventHandler -= handler;
							}

							/**
							* Overloaded raise method.
							* Needed to raise an event.
							*
							* @param[in]	sender	Reference to object that raised the event.
							* @param[in[	args	The arguments for this event. Should be of the type CrxShowStatusEventArgs.
							*/
							void raise(Object^ sender, CrxShowStatusEventArgs ^ args)
							{
								//Raise the event.
								if(_showStatusEventHandler)
									_showStatusEventHandler->Invoke(sender, args);
							}
						}

				}; // End class CrxEventContainer				

		}
	}
}