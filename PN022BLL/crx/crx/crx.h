// crx.h

#pragma once

using namespace System;

namespace AtCor {
namespace Scor {
namespace CrossCutting {

	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	};
}}}

namespace AtCor {
namespace Scor {
namespace CrossCutting {
namespace Configuration {

	public ref class CrxConfigConstants
	{
	public:
		static const bool GENERAL_PATIENT_PRIVACY = true;
		static const unsigned short GENERAL_UNIT_METRIC = 0;
		static const unsigned short GENERAL_UNIT_IMPERIAL = 1;
		static const unsigned short GENERAL_BP_ENTRY_SPDP = 0;
		static const unsigned short GENERAL_BP_ENTRY_SPMP = 1;
		static const unsigned short GENERAL_BP_ENTRY_MPDP = 2;
	};
}}}}
