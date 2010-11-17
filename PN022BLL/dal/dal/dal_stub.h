// dal_stub.h

#pragma once

using namespace System;

namespace AtCor{ 
namespace Scor { 
namespace DataAccess{

#if 1
	public enum ModuleErrorAlarmStatus
	{
		NoErrorAlarm = 0x0000, //0
		ErrorStatus = 0x0020,   //32
		AlarmStatus = 0x0008,   //8
		ErrorAndAlarmStatus = 0x0028 // 40
	};
#endif

	// Byte  3  2 | 1  0
	//      Alarm | Error
	// 0x00000001 Power up
	// 0x00000002 High inflation rate
	// 0x00000004 Cuff motor power
	// 0x00000008 Cuff leak
	// 0x00000010 High deflation rate 
	// 0x00000020 Dual sensor
	// 0x00000040 Temperature
	// 0x00000080 Low pump speed
	// 0x00000100 Power rail
	// 0x00000200 (Power rail source xxx1)
	// 0x00000400 ditto
	// 0x00000800 ditto
	// 0x00001000 Spare
	// 0x00002000 Low deflation rate
	// 0x00004000 r2
	// 0x00008000 r3
	//
	// 0x00010000 TA Over pressure
	// 0x00020000 TA Over time over pressure
	// 0x00040000 TA Overtime
	// 0x00080000 Short wait
	// 0x00100000 r
	// 0x00200000 r
	// 0x00400000 r
	// 0x00800000 r 

	public enum ModuleErrorSource
	{
		CuffLeak   = 0x0008,
		DualSensor = 0x0020
	};

	public enum ModuleAlarmSource
	{
		OverPressure     = 0x0001,
		InflatedOverTime = 0x0004
	};

}}}
