// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdSapiGr.pas' rev: 6.00

#ifndef AdSapiGrHPP
#define AdSapiGrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adsapigr
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdSapiPhraseType { ptConvert, ptDrop, ptConvertJoin };
#pragma option pop

#pragma pack(push, 4)
struct TApdSapiParseTable
{
	TApdSapiPhraseType PhraseType;
	AnsiString InputPhrase;
	AnsiString OutputPhrase;
} ;
#pragma pack(pop)

typedef TApdSapiParseTable AdSapiGr__1[12];

typedef TApdSapiParseTable AdSapiGr__2[29];

#pragma option push -b-
enum TApdTimeWordType { twtQuarter, twtHalf, twtMidnight, twtNoon, twtAfter, twtBefore, twtPM, twtAM, twtUnknown };
#pragma option pop

#pragma pack(push, 4)
struct TApdTimeWord
{
	TApdTimeWordType WordType;
	AnsiString TimeWord;
} ;
#pragma pack(pop)

typedef TApdTimeWord AdSapiGr__3[19];

#pragma option push -b-
enum TApdDateWordType { dwtMonth, dwtDay, dwtNext, dwtLast, dwtToday, dwtTomorrow, dwtYesterday, dwtWeekOff, dwtMonthOff, dwtYearOff, dwtUnknown };
#pragma option pop

#pragma pack(push, 4)
struct TApdDateWord
{
	TApdDateWordType WordType;
	AnsiString DateWord;
	int Number;
} ;
#pragma pack(pop)

typedef TApdDateWord AdSapiGr__4[27];

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ResourceString _ApdAskAreaCode;
#define Adsapigr_ApdAskAreaCode System::LoadResourceString(&Adsapigr::_ApdAskAreaCode)
extern PACKAGE System::ResourceString _ApdAskLastFour;
#define Adsapigr_ApdAskLastFour System::LoadResourceString(&Adsapigr::_ApdAskLastFour)
extern PACKAGE System::ResourceString _ApdAskNextThree;
#define Adsapigr_ApdAskNextThree System::LoadResourceString(&Adsapigr::_ApdAskNextThree)
extern PACKAGE System::ResourceString _ApdCannotGoBack;
#define Adsapigr_ApdCannotGoBack System::LoadResourceString(&Adsapigr::_ApdCannotGoBack)
extern PACKAGE System::ResourceString _ApdCannotHangUp;
#define Adsapigr_ApdCannotHangUp System::LoadResourceString(&Adsapigr::_ApdCannotHangUp)
extern PACKAGE System::ResourceString _ApdHangingUp;
#define Adsapigr_ApdHangingUp System::LoadResourceString(&Adsapigr::_ApdHangingUp)
extern PACKAGE System::ResourceString _ApdHelp;
#define Adsapigr_ApdHelp System::LoadResourceString(&Adsapigr::_ApdHelp)
extern PACKAGE System::ResourceString _ApdHelp2;
#define Adsapigr_ApdHelp2 System::LoadResourceString(&Adsapigr::_ApdHelp2)
extern PACKAGE System::ResourceString _ApdHelpVerify;
#define Adsapigr_ApdHelpVerify System::LoadResourceString(&Adsapigr::_ApdHelpVerify)
extern PACKAGE System::ResourceString _ApdGoingBack;
#define Adsapigr_ApdGoingBack System::LoadResourceString(&Adsapigr::_ApdGoingBack)
extern PACKAGE System::ResourceString _ApdMain;
#define Adsapigr_ApdMain System::LoadResourceString(&Adsapigr::_ApdMain)
extern PACKAGE System::ResourceString _ApdMain2;
#define Adsapigr_ApdMain2 System::LoadResourceString(&Adsapigr::_ApdMain2)
extern PACKAGE System::ResourceString _ApdMaxSpeed;
#define Adsapigr_ApdMaxSpeed System::LoadResourceString(&Adsapigr::_ApdMaxSpeed)
extern PACKAGE System::ResourceString _ApdMinSpeed;
#define Adsapigr_ApdMinSpeed System::LoadResourceString(&Adsapigr::_ApdMinSpeed)
extern PACKAGE System::ResourceString _ApdOperator;
#define Adsapigr_ApdOperator System::LoadResourceString(&Adsapigr::_ApdOperator)
extern PACKAGE System::ResourceString _ApdNoOperator;
#define Adsapigr_ApdNoOperator System::LoadResourceString(&Adsapigr::_ApdNoOperator)
extern PACKAGE System::ResourceString _ApdNoSpeedChange;
#define Adsapigr_ApdNoSpeedChange System::LoadResourceString(&Adsapigr::_ApdNoSpeedChange)
extern PACKAGE System::ResourceString _ApdSpeakingFaster;
#define Adsapigr_ApdSpeakingFaster System::LoadResourceString(&Adsapigr::_ApdSpeakingFaster)
extern PACKAGE System::ResourceString _ApdSpeakingSlower;
#define Adsapigr_ApdSpeakingSlower System::LoadResourceString(&Adsapigr::_ApdSpeakingSlower)
extern PACKAGE System::ResourceString _ApdTooFewDigits;
#define Adsapigr_ApdTooFewDigits System::LoadResourceString(&Adsapigr::_ApdTooFewDigits)
extern PACKAGE System::ResourceString _ApdTooManyDigits;
#define Adsapigr_ApdTooManyDigits System::LoadResourceString(&Adsapigr::_ApdTooManyDigits)
extern PACKAGE System::ResourceString _ApdUnrecognized;
#define Adsapigr_ApdUnrecognized System::LoadResourceString(&Adsapigr::_ApdUnrecognized)
extern PACKAGE System::ResourceString _ApdVerifyPost;
#define Adsapigr_ApdVerifyPost System::LoadResourceString(&Adsapigr::_ApdVerifyPost)
extern PACKAGE System::ResourceString _ApdVerifyPre;
#define Adsapigr_ApdVerifyPre System::LoadResourceString(&Adsapigr::_ApdVerifyPre)
extern PACKAGE System::ResourceString _ApdWhere;
#define Adsapigr_ApdWhere System::LoadResourceString(&Adsapigr::_ApdWhere)
extern PACKAGE System::ResourceString _ApdWhere2;
#define Adsapigr_ApdWhere2 System::LoadResourceString(&Adsapigr::_ApdWhere2)
extern PACKAGE System::ResourceString _ApdYouHaveSpelled;
#define Adsapigr_ApdYouHaveSpelled System::LoadResourceString(&Adsapigr::_ApdYouHaveSpelled)
extern PACKAGE System::ResourceString _ecApdNoSS;
#define Adsapigr_ecApdNoSS System::LoadResourceString(&Adsapigr::_ecApdNoSS)
extern PACKAGE System::ResourceString _ecApdNoSR;
#define Adsapigr_ecApdNoSR System::LoadResourceString(&Adsapigr::_ecApdNoSR)
extern PACKAGE System::ResourceString _ecApdBadIndex;
#define Adsapigr_ecApdBadIndex System::LoadResourceString(&Adsapigr::_ecApdBadIndex)
extern PACKAGE System::ResourceString _ecNoSREngines;
#define Adsapigr_ecNoSREngines System::LoadResourceString(&Adsapigr::_ecNoSREngines)
extern PACKAGE System::ResourceString _ecNoSSEngines;
#define Adsapigr_ecNoSSEngines System::LoadResourceString(&Adsapigr::_ecNoSSEngines)
extern PACKAGE System::ResourceString _ecApdNoSapiEngine;
#define Adsapigr_ecApdNoSapiEngine System::LoadResourceString(&Adsapigr::_ecApdNoSapiEngine)
extern PACKAGE System::ResourceString _ecApdNoPrompts;
#define Adsapigr_ecApdNoPrompts System::LoadResourceString(&Adsapigr::_ecApdNoPrompts)
extern PACKAGE System::ResourceString _ecApdBadDeviceNum;
#define Adsapigr_ecApdBadDeviceNum System::LoadResourceString(&Adsapigr::_ecApdBadDeviceNum)
extern PACKAGE System::ResourceString _ecApdCannotCreateCOM;
#define Adsapigr_ecApdCannotCreateCOM System::LoadResourceString(&Adsapigr::_ecApdCannotCreateCOM)
extern PACKAGE System::ResourceString _ecApdNotPhone;
#define Adsapigr_ecApdNotPhone System::LoadResourceString(&Adsapigr::_ecApdNotPhone)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDINTERFACE;
#define Adsapigr_ApdStrTTSERR_INVALIDINTERFACE System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDINTERFACE)
extern PACKAGE System::ResourceString _ApdStrTTSERR_OUTOFDISK;
#define Adsapigr_ApdStrTTSERR_OUTOFDISK System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_OUTOFDISK)
extern PACKAGE System::ResourceString _ApdStrTTSERR_NOTSUPPORTED;
#define Adsapigr_ApdStrTTSERR_NOTSUPPORTED System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_NOTSUPPORTED)
extern PACKAGE System::ResourceString _ApdStrTTSERR_VALUEOUTOFRANGE;
#define Adsapigr_ApdStrTTSERR_VALUEOUTOFRANGE System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_VALUEOUTOFRANGE)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDWINDOW;
#define Adsapigr_ApdStrTTSERR_INVALIDWINDOW System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDWINDOW)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDPARAM;
#define Adsapigr_ApdStrTTSERR_INVALIDPARAM System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDPARAM)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDMODE;
#define Adsapigr_ApdStrTTSERR_INVALIDMODE System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDMODE)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDKEY;
#define Adsapigr_ApdStrTTSERR_INVALIDKEY System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDKEY)
extern PACKAGE System::ResourceString _ApdStrTTSERR_WAVEFORMATNOTSUPPORTED;
#define Adsapigr_ApdStrTTSERR_WAVEFORMATNOTSUPPORTED System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_WAVEFORMATNOTSUPPORTED)
extern PACKAGE System::ResourceString _ApdStrTTSERR_INVALIDCHAR;
#define Adsapigr_ApdStrTTSERR_INVALIDCHAR System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_INVALIDCHAR)
extern PACKAGE System::ResourceString _ApdStrTTSERR_QUEUEFULL;
#define Adsapigr_ApdStrTTSERR_QUEUEFULL System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_QUEUEFULL)
extern PACKAGE System::ResourceString _ApdStrTTSERR_WAVEDEVICEBUSY;
#define Adsapigr_ApdStrTTSERR_WAVEDEVICEBUSY System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_WAVEDEVICEBUSY)
extern PACKAGE System::ResourceString _ApdStrTTSERR_NOTPAUSED;
#define Adsapigr_ApdStrTTSERR_NOTPAUSED System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_NOTPAUSED)
extern PACKAGE System::ResourceString _ApdStrTTSERR_ALREADYPAUSED;
#define Adsapigr_ApdStrTTSERR_ALREADYPAUSED System::LoadResourceString(&Adsapigr::_ApdStrTTSERR_ALREADYPAUSED)
extern PACKAGE System::ResourceString _ApdStrSRERR_OUTOFDISK;
#define Adsapigr_ApdStrSRERR_OUTOFDISK System::LoadResourceString(&Adsapigr::_ApdStrSRERR_OUTOFDISK)
extern PACKAGE System::ResourceString _ApdStrSRERR_NOTSUPPORTED;
#define Adsapigr_ApdStrSRERR_NOTSUPPORTED System::LoadResourceString(&Adsapigr::_ApdStrSRERR_NOTSUPPORTED)
extern PACKAGE System::ResourceString _ApdStrSRERR_NOTENOUGHDATA;
#define Adsapigr_ApdStrSRERR_NOTENOUGHDATA System::LoadResourceString(&Adsapigr::_ApdStrSRERR_NOTENOUGHDATA)
extern PACKAGE System::ResourceString _ApdStrSRERR_VALUEOUTOFRANGE;
#define Adsapigr_ApdStrSRERR_VALUEOUTOFRANGE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_VALUEOUTOFRANGE)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARTOOCOMPLEX;
#define Adsapigr_ApdStrSRERR_GRAMMARTOOCOMPLEX System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARTOOCOMPLEX)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARWRONGTYPE;
#define Adsapigr_ApdStrSRERR_GRAMMARWRONGTYPE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARWRONGTYPE)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDWINDOW;
#define Adsapigr_ApdStrSRERR_INVALIDWINDOW System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDWINDOW)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDPARAM;
#define Adsapigr_ApdStrSRERR_INVALIDPARAM System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDPARAM)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDMODE;
#define Adsapigr_ApdStrSRERR_INVALIDMODE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDMODE)
extern PACKAGE System::ResourceString _ApdStrSRERR_TOOMANYGRAMMARS;
#define Adsapigr_ApdStrSRERR_TOOMANYGRAMMARS System::LoadResourceString(&Adsapigr::_ApdStrSRERR_TOOMANYGRAMMARS)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDLIST;
#define Adsapigr_ApdStrSRERR_INVALIDLIST System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDLIST)
extern PACKAGE System::ResourceString _ApdStrSRERR_WAVEDEVICEBUSY;
#define Adsapigr_ApdStrSRERR_WAVEDEVICEBUSY System::LoadResourceString(&Adsapigr::_ApdStrSRERR_WAVEDEVICEBUSY)
extern PACKAGE System::ResourceString _ApdStrSRERR_WAVEFORMATNOTSUPPORTED;
#define Adsapigr_ApdStrSRERR_WAVEFORMATNOTSUPPORTED System::LoadResourceString(&Adsapigr::_ApdStrSRERR_WAVEFORMATNOTSUPPORTED)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDCHAR;
#define Adsapigr_ApdStrSRERR_INVALIDCHAR System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDCHAR)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMTOOCOMPLEX;
#define Adsapigr_ApdStrSRERR_GRAMTOOCOMPLEX System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMTOOCOMPLEX)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMTOOLARGE;
#define Adsapigr_ApdStrSRERR_GRAMTOOLARGE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMTOOLARGE)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDINTERFACE;
#define Adsapigr_ApdStrSRERR_INVALIDINTERFACE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDINTERFACE)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDKEY;
#define Adsapigr_ApdStrSRERR_INVALIDKEY System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDKEY)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDFLAG;
#define Adsapigr_ApdStrSRERR_INVALIDFLAG System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDFLAG)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARERROR;
#define Adsapigr_ApdStrSRERR_GRAMMARERROR System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARERROR)
extern PACKAGE System::ResourceString _ApdStrSRERR_INVALIDRULE;
#define Adsapigr_ApdStrSRERR_INVALIDRULE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_INVALIDRULE)
extern PACKAGE System::ResourceString _ApdStrSRERR_RULEALREADYACTIVE;
#define Adsapigr_ApdStrSRERR_RULEALREADYACTIVE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_RULEALREADYACTIVE)
extern PACKAGE System::ResourceString _ApdStrSRERR_RULENOTACTIVE;
#define Adsapigr_ApdStrSRERR_RULENOTACTIVE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_RULENOTACTIVE)
extern PACKAGE System::ResourceString _ApdStrSRERR_NOUSERSELECTED;
#define Adsapigr_ApdStrSRERR_NOUSERSELECTED System::LoadResourceString(&Adsapigr::_ApdStrSRERR_NOUSERSELECTED)
extern PACKAGE System::ResourceString _ApdStrSRERR_BAD_PRONUNCIATION;
#define Adsapigr_ApdStrSRERR_BAD_PRONUNCIATION System::LoadResourceString(&Adsapigr::_ApdStrSRERR_BAD_PRONUNCIATION)
extern PACKAGE System::ResourceString _ApdStrSRERR_DATAFILEERROR;
#define Adsapigr_ApdStrSRERR_DATAFILEERROR System::LoadResourceString(&Adsapigr::_ApdStrSRERR_DATAFILEERROR)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARALREADYACTIVE;
#define Adsapigr_ApdStrSRERR_GRAMMARALREADYACTIVE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARALREADYACTIVE)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARNOTACTIVE;
#define Adsapigr_ApdStrSRERR_GRAMMARNOTACTIVE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARNOTACTIVE)
extern PACKAGE System::ResourceString _ApdStrSRERR_GLOBALGRAMMARALREADYACTIVE;
#define Adsapigr_ApdStrSRERR_GLOBALGRAMMARALREADYACTIVE System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GLOBALGRAMMARALREADYACTIVE)
extern PACKAGE System::ResourceString _ApdStrSRERR_LANGUAGEMISMATCH;
#define Adsapigr_ApdStrSRERR_LANGUAGEMISMATCH System::LoadResourceString(&Adsapigr::_ApdStrSRERR_LANGUAGEMISMATCH)
extern PACKAGE System::ResourceString _ApdStrSRERR_MULTIPLELANG;
#define Adsapigr_ApdStrSRERR_MULTIPLELANG System::LoadResourceString(&Adsapigr::_ApdStrSRERR_MULTIPLELANG)
extern PACKAGE System::ResourceString _ApdStrSRERR_LDGRAMMARNOWORDS;
#define Adsapigr_ApdStrSRERR_LDGRAMMARNOWORDS System::LoadResourceString(&Adsapigr::_ApdStrSRERR_LDGRAMMARNOWORDS)
extern PACKAGE System::ResourceString _ApdStrSRERR_NOLEXICON;
#define Adsapigr_ApdStrSRERR_NOLEXICON System::LoadResourceString(&Adsapigr::_ApdStrSRERR_NOLEXICON)
extern PACKAGE System::ResourceString _ApdStrSRERR_SPEAKEREXISTS;
#define Adsapigr_ApdStrSRERR_SPEAKEREXISTS System::LoadResourceString(&Adsapigr::_ApdStrSRERR_SPEAKEREXISTS)
extern PACKAGE System::ResourceString _ApdStrSRERR_GRAMMARENGINEMISMATCH;
#define Adsapigr_ApdStrSRERR_GRAMMARENGINEMISMATCH System::LoadResourceString(&Adsapigr::_ApdStrSRERR_GRAMMARENGINEMISMATCH)
extern PACKAGE System::ResourceString _ApdStrSRERR_BOOKMARKEXISTS;
#define Adsapigr_ApdStrSRERR_BOOKMARKEXISTS System::LoadResourceString(&Adsapigr::_ApdStrSRERR_BOOKMARKEXISTS)
extern PACKAGE System::ResourceString _ApdStrSRERR_BOOKMARKDOESNOTEXIST;
#define Adsapigr_ApdStrSRERR_BOOKMARKDOESNOTEXIST System::LoadResourceString(&Adsapigr::_ApdStrSRERR_BOOKMARKDOESNOTEXIST)
extern PACKAGE System::ResourceString _ApdStrSRERR_MICWIZARDCANCELED;
#define Adsapigr_ApdStrSRERR_MICWIZARDCANCELED System::LoadResourceString(&Adsapigr::_ApdStrSRERR_MICWIZARDCANCELED)
extern PACKAGE System::ResourceString _ApdStrSRERR_WORDTOOLONG;
#define Adsapigr_ApdStrSRERR_WORDTOOLONG System::LoadResourceString(&Adsapigr::_ApdStrSRERR_WORDTOOLONG)
extern PACKAGE System::ResourceString _ApdStrSRERR_BAD_WORD;
#define Adsapigr_ApdStrSRERR_BAD_WORD System::LoadResourceString(&Adsapigr::_ApdStrSRERR_BAD_WORD)
extern PACKAGE System::ResourceString _ApdStrE_WRONGTYPE;
#define Adsapigr_ApdStrE_WRONGTYPE System::LoadResourceString(&Adsapigr::_ApdStrE_WRONGTYPE)
extern PACKAGE System::ResourceString _ApdStrE_BUFFERTOOSMALL;
#define Adsapigr_ApdStrE_BUFFERTOOSMALL System::LoadResourceString(&Adsapigr::_ApdStrE_BUFFERTOOSMALL)
extern PACKAGE System::ResourceString _ApdStrE_UNKNOWN;
#define Adsapigr_ApdStrE_UNKNOWN System::LoadResourceString(&Adsapigr::_ApdStrE_UNKNOWN)
extern PACKAGE System::ResourceString _ApdStrE_CANNOTCREATESS;
#define Adsapigr_ApdStrE_CANNOTCREATESS System::LoadResourceString(&Adsapigr::_ApdStrE_CANNOTCREATESS)
extern PACKAGE System::ResourceString _ApdStrE_CANNOTCREATESR;
#define Adsapigr_ApdStrE_CANNOTCREATESR System::LoadResourceString(&Adsapigr::_ApdStrE_CANNOTCREATESR)
extern PACKAGE System::ResourceString _ApdStrE_CANNOTSETSPEAKER;
#define Adsapigr_ApdStrE_CANNOTSETSPEAKER System::LoadResourceString(&Adsapigr::_ApdStrE_CANNOTSETSPEAKER)
extern PACKAGE System::ResourceString _ApdStrE_CANNOTSETMIC;
#define Adsapigr_ApdStrE_CANNOTSETMIC System::LoadResourceString(&Adsapigr::_ApdStrE_CANNOTSETMIC)
extern PACKAGE System::ResourceString _ApdStrE_NOSAPI4;
#define Adsapigr_ApdStrE_NOSAPI4 System::LoadResourceString(&Adsapigr::_ApdStrE_NOSAPI4)
extern PACKAGE System::ResourceString _scApdTrainGeneral;
#define Adsapigr_scApdTrainGeneral System::LoadResourceString(&Adsapigr::_scApdTrainGeneral)
extern PACKAGE System::ResourceString _scApdTrainMic;
#define Adsapigr_scApdTrainMic System::LoadResourceString(&Adsapigr::_scApdTrainMic)
extern PACKAGE System::ResourceString _scApdTrainGrammar;
#define Adsapigr_scApdTrainGrammar System::LoadResourceString(&Adsapigr::_scApdTrainGrammar)
extern PACKAGE AnsiString scApdDefaultUser;
extern PACKAGE AnsiString scApdDefaultMic;
extern PACKAGE AnsiString scApdTelMic;
extern PACKAGE AnsiString ApdDefaultPhoneGrammar;
extern PACKAGE AnsiString ApdAskForDateGrammar;
extern PACKAGE AnsiString ApdAskForExtensionGrammar;
extern PACKAGE AnsiString ApdAskForPhoneNumberGrammar;
extern PACKAGE AnsiString ApdAskForSpellingGrammar;
extern PACKAGE AnsiString ApdAskForTimeGrammar;
extern PACKAGE AnsiString ApdAskForYesNoGrammar;
static const Shortint ApdPhoneNumberEntries = 0xc;
extern PACKAGE TApdSapiParseTable ApdPhoneNumberConvert[12];
static const Shortint ApdNumericCvtEntries = 0x1d;
extern PACKAGE TApdSapiParseTable ApdNumericCvt[29];
static const Shortint ApdTimeWordCount = 0x13;
extern PACKAGE TApdTimeWord ApdTimeWordList[19];
static const Shortint ApdDateWordCount = 0x1b;
extern PACKAGE TApdDateWord ApdDateWordList[27];

}	/* namespace Adsapigr */
using namespace Adsapigr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdSapiGr
