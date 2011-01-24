/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business data event classes.
*/

#pragma once

#include <biz_namespace.h>
#include <msclr\lock.h>

using namespace System;
using namespace System::Drawing;
using namespace msclr;

START_BIZ_NAMESPACE

// BizTonometerDataEventArgs: a custom event inherited from EventArgs.
public ref class BizTonometerDataEventArgs: public EventArgs
{
public:
   BizTonometerDataEventArgs( unsigned short data )
   {
	  this->data = data;
   }
   property unsigned short data;
};

// BizCuffPulseEventArgs: a custom event inherited from EventArgs.
public ref class BizCuffPulseEventArgs: public EventArgs
{
public:
   BizCuffPulseEventArgs( unsigned short data )
   {
	  this->data = data;
   }
   property unsigned short data;
};

// BizCountdownTimerEventArgs: a custom event inherited from EventArgs.
public ref class BizCountdownTimerEventArgs: public EventArgs
{
public:
   BizCountdownTimerEventArgs( unsigned short data )
   {
	  this->data = data;
   }
   property unsigned short data;
};

// BizCuffStateEventArgs: a custom event inherited from EventArgs.
public ref class BizCuffStateEventArgs: public EventArgs
{
public:
   BizCuffStateEventArgs( String^ data,  unsigned short deflationTime)
   {
	  this->data = data;
	  this->deflationTime = deflationTime;
   }
   property String^ data;
   // When cuff is in inflated state, subtract deflationTime from the countdown timer
   // to adjust countdown timer so it would countdown to zero when cuff starts to deflate
   property unsigned short deflationTime;
};

// BizCarotidQualityEventArgs: a custom event inherited from EventArgs.
public ref class BizCarotidQualityEventArgs: public EventArgs
{
public:
	
   BizCarotidQualityEventArgs( unsigned short signalMinimum, unsigned short signalMaximum, 
								Color signalStrengthColor, bool enableOkayButton )
   {
	  this->signalMinimum = signalMinimum;
	  this->signalMaximum = signalMaximum;
	  this->signalStrengthColor = signalStrengthColor;
	  this->enableOkayButton = enableOkayButton;
   }
   property unsigned short signalMinimum;	// Signal maximum, used to calculate signal strength and scale the display
   property unsigned short signalMaximum;	// Signal minimum, used to calculate signal strength and scale the display
   property Color signalStrengthColor;		// Colour to be displayed on the quality indicator
   property bool enableOkayButton;			// Can the user calculate a report or not
};

// BizFemoralQualityEventArgs: a custom event inherited from EventArgs.
public ref class BizFemoralQualityEventArgs: public EventArgs
{
public:
	
   BizFemoralQualityEventArgs( unsigned short signalMinimum, unsigned short signalMaximum, 
								bool signalStrengthIsGood, bool enableOkayButton )
   {
	  this->signalMinimum = signalMinimum;
	  this->signalMaximum = signalMaximum;
	  this->signalStrengthIsGood = signalStrengthIsGood;
	  this->enableOkayButton = enableOkayButton;
   }
   property unsigned short signalMinimum;	// Signal maximum, used to calculate signal strength and scale the display
   property unsigned short signalMaximum;	// Signal minimum, used to calculate signal strength and scale the display
   property bool signalStrengthIsGood;		// Good (true) or Bad (false) quality to be displayed on the quality indicator
   property bool enableOkayButton;			// Can the user calculate a report or not
};

// BizInformationEventArgs: a custom event inherited from EventArgs.
public ref class BizInformationEventArgs: public EventArgs
{
public:
   BizInformationEventArgs( String^ data )
   {
	  this->data = data;
   }
   property String^ data;
};

// BizWarningEventArgs: a custom event inherited from EventArgs.
public ref class BizWarningEventArgs: public EventArgs
{
public:
   BizWarningEventArgs( String^ data )
   {
	  this->data = data;
   }
   property String^ data;
};

// BizErrorEventArgs: a custom event inherited from EventArgs.
public ref class BizErrorEventArgs: public EventArgs
{
public:
   BizErrorEventArgs( String^ data )
   {
	  this->data = data;
   }
   property String^ data;
};

// Delegate for tonometer data event
public delegate void BizTonometerDataEventHandler(Object^ sender, BizTonometerDataEventArgs ^ e);

// Delegate for cuff pulse event
public delegate void BizCuffPulseEventHandler(Object^ sender, BizCuffPulseEventArgs ^ e);

// Delegate for countdown timer event
public delegate void BizCountdownTimerEventHandler(Object^ sender, BizCountdownTimerEventArgs ^ e);

// Delegate for cuff state event
public delegate void BizCuffStateEventHandler(Object^ sender, BizCuffStateEventArgs ^ e);

// Delegate for carotid quality event
public delegate void BizCarotidQualityEventHandler(Object^ sender, BizCarotidQualityEventArgs ^ e);

// Delegate for femoral quality event
public delegate void BizFemoralQualityEventHandler(Object^ sender, BizFemoralQualityEventArgs ^ e);

// Delegate for information event
public delegate void BizInformationEventHandler(Object^ sender, BizInformationEventArgs ^ e);

// Delegate for warning event
public delegate void BizWarningEventHandler(Object^ sender, BizWarningEventArgs ^ e);

// Delegate for error event
public delegate void BizErrorEventHandler(Object^ sender, BizErrorEventArgs ^ e);

// Container for all BizXXXEvent handlers
public ref class BizEventContainer
{
	private:
		static BizEventContainer^ _instance = gcnew BizEventContainer();
		BizEventContainer() {};
		BizEventContainer(const BizEventContainer^) {};
		BizEventContainer^ operator= (const BizEventContainer) { return this; };

		BizTonometerDataEventHandler^ _bizTonometerDataEventHandler;
		BizCuffPulseEventHandler^ _bizCuffPulseEventHandler;
		BizCountdownTimerEventHandler^ _bizCountdownTimerEventHandler;
		BizCuffStateEventHandler^ _bizCuffStateEventHandler;
		BizCarotidQualityEventHandler^ _bizCarotidQualityEventHandler;
		BizFemoralQualityEventHandler^ _bizFemoralQualityEventHandler;
		BizInformationEventHandler^ _bizInformationEventHandler;
		BizWarningEventHandler^ _bizWarningEventHandler;
		BizErrorEventHandler^ _bizErrorEventHandler;

	public:
		static property BizEventContainer^ Instance
		{
			BizEventContainer^ get()
			{
				return BizEventContainer::_instance;
			};
		};

		event BizTonometerDataEventHandler^ OnBizTonometerDataEvent
		{
			void add(BizTonometerDataEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizTonometerDataEventHandler += handler;
			}

			void remove(BizTonometerDataEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizTonometerDataEventHandler -= handler;
			}

			void raise(Object^ sender, BizTonometerDataEventArgs ^ e)
			{
				if(_bizTonometerDataEventHandler)
					_bizTonometerDataEventHandler->Invoke(sender, e);
			}
		}

		event BizCuffPulseEventHandler^ OnBizCuffPulseEvent
		{
			void add(BizCuffPulseEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCuffPulseEventHandler += handler;
			}

			void remove(BizCuffPulseEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCuffPulseEventHandler -= handler;
			}

			void raise(Object^ sender, BizCuffPulseEventArgs ^ e)
			{
				if(_bizCuffPulseEventHandler)
					_bizCuffPulseEventHandler->Invoke(sender, e);
			}
		}

		event BizCountdownTimerEventHandler^ OnBizCountdownTimerEvent
		{
			void add(BizCountdownTimerEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCountdownTimerEventHandler += handler;
			}

			void remove(BizCountdownTimerEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCountdownTimerEventHandler -= handler;
			}

			void raise(Object^ sender, BizCountdownTimerEventArgs ^ e)
			{
				if(_bizCountdownTimerEventHandler)
					_bizCountdownTimerEventHandler->Invoke(sender, e);
			}
		}

		event BizCuffStateEventHandler^ OnBizCuffStateEvent
		{
			void add(BizCuffStateEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCuffStateEventHandler += handler;
			}

			void remove(BizCuffStateEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCuffStateEventHandler -= handler;
			}

			void raise(Object^ sender, BizCuffStateEventArgs ^ e)
			{
				if(_bizCuffStateEventHandler)
					_bizCuffStateEventHandler->Invoke(sender, e);
			}
		}

		event BizCarotidQualityEventHandler^ OnBizCarotidQualityEvent
		{
			void add(BizCarotidQualityEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCarotidQualityEventHandler += handler;
			}

			void remove(BizCarotidQualityEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizCarotidQualityEventHandler -= handler;
			}

			void raise(Object^ sender, BizCarotidQualityEventArgs ^ e)
			{
				if(_bizCarotidQualityEventHandler)
					_bizCarotidQualityEventHandler->Invoke(sender, e);
			}
		}

		event BizFemoralQualityEventHandler^ OnBizFemoralQualityEvent
		{
			void add(BizFemoralQualityEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizFemoralQualityEventHandler += handler;
			}

			void remove(BizFemoralQualityEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizFemoralQualityEventHandler -= handler;
			}

			void raise(Object^ sender, BizFemoralQualityEventArgs ^ e)
			{
				if(_bizFemoralQualityEventHandler)
					_bizFemoralQualityEventHandler->Invoke(sender, e);
			}
		}

		event BizInformationEventHandler^ OnBizInformationEvent
		{
			void add(BizInformationEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizInformationEventHandler += handler;
			}

			void remove(BizInformationEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizInformationEventHandler -= handler;
			}

			void raise(Object^ sender, BizInformationEventArgs ^ e)
			{
				if(_bizInformationEventHandler)
					_bizInformationEventHandler->Invoke(sender, e);
			}
		}

		event BizWarningEventHandler^ OnBizWarningEvent
		{
			void add(BizWarningEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizWarningEventHandler += handler;
			}

			void remove(BizWarningEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizWarningEventHandler -= handler;
			}

			void raise(Object^ sender, BizWarningEventArgs ^ e)
			{
				if(_bizWarningEventHandler)
					_bizWarningEventHandler->Invoke(sender, e);
			}
		}

		event BizErrorEventHandler^ OnBizErrorEvent
		{
			void add(BizErrorEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizErrorEventHandler += handler;
			}

			void remove(BizErrorEventHandler^ handler)
			{
				lock lockEvents(this);
				_bizErrorEventHandler -= handler;
			}

			void raise(Object^ sender, BizErrorEventArgs ^ e)
			{
				if(_bizErrorEventHandler)
					_bizErrorEventHandler->Invoke(sender, e);
			}
		}
};

END_BIZ_NAMESPACE
