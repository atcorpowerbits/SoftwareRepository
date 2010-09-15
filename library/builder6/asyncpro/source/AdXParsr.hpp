// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdXParsr.pas' rev: 6.00

#ifndef AdXParsrHPP
#define AdXParsrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdXChrFlt.hpp>	// Pascal unit
#include <AdXBase.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adxparsr
{
//-- type declarations -------------------------------------------------------
typedef WideString StringIds[2];

typedef void __fastcall (__closure *TApdDocTypeDeclEvent)(System::TObject* oOwner, WideString sDecl, WideString sId0, WideString sId1);

typedef void __fastcall (__closure *TApdValueEvent)(System::TObject* oOwner, WideString sValue);

typedef void __fastcall (__closure *TApdAttributeEvent)(System::TObject* oOwner, WideString sName, WideString sValue, bool bSpecified);

typedef void __fastcall (__closure *TApdProcessInstrEvent)(System::TObject* oOwner, WideString sName, WideString sValue);

typedef void __fastcall (__closure *TApdResolveEvent)(System::TObject* oOwner, const WideString sName, const WideString sPublicId, const WideString sSystemId, WideString &sValue);

typedef void __fastcall (__closure *TApdNonXMLEntityEvent)(System::TObject* oOwner, WideString sEntityName, WideString sPublicId, WideString sSystemId, WideString sNotationName);

typedef void __fastcall (__closure *TApdPreserveSpaceEvent)(System::TObject* oOwner, WideString sElementName, bool &bPreserve);

class DELPHICLASS TApdParser;
class PASCALIMPLEMENTATION TApdParser : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	Classes::TStringList* FAttrEnum;
	Classes::TStringList* FAttributeType;
	int FBufferSize;
	bool FCDATA;
	int FContext;
	WideString FCurrentElement;
	int FCurrentElementContent;
	AnsiString FCurrentPath;
	WideString FDataBuffer;
	Classes::TList* FDocStack;
	Classes::TStringList* FElementInfo;
	Classes::TStringList* FEntityInfo;
	Classes::TStringList* FErrors;
	Adxchrflt::TApdInCharFilter* FFilter;
	Adxbase::TApdCharEncoding FInCharSet;
	bool FNormalizeData;
	Classes::TStringList* FNotationInfo;
	TApdAttributeEvent FOnAttribute;
	TApdValueEvent FOnCDATASection;
	TApdValueEvent FOnCharData;
	TApdValueEvent FOnComment;
	TApdDocTypeDeclEvent FOnDocTypeDecl;
	Classes::TNotifyEvent FOnEndDocument;
	TApdValueEvent FOnEndElement;
	TApdValueEvent FOnIgnorableWhitespace;
	TApdNonXMLEntityEvent FOnNonXMLEntity;
	TApdPreserveSpaceEvent FOnPreserveSpace;
	TApdProcessInstrEvent FOnProcessingInstruction;
	TApdResolveEvent FOnResolveEntity;
	Classes::TNotifyEvent FOnStartDocument;
	TApdValueEvent FOnStartElement;
	TApdValueEvent FOnBeginElement;
	bool FPreserve;
	bool FRaiseErrors;
	Classes::TStringList* FTagAttributes;
	Classes::TStringList* FTempFiles;
	WideString FUrl;
	bool FIsStandAlone;
	bool FHasExternals;
	bool FXMLDecParsed;
	void __fastcall Cleanup(void);
	void __fastcall CheckParamEntityNesting(const WideString aString);
	void __fastcall DataBufferAppend(const WideString sVal);
	void __fastcall DataBufferFlush(void);
	void __fastcall DataBufferNormalize(void);
	WideString __fastcall DataBufferToString();
	Classes::TStringList* __fastcall DeclaredAttributes(const WideString sName, int aIdx);
	int __fastcall GetAttributeDefaultValueType(const WideString sElemName, const WideString sAttrName);
	WideString __fastcall GetAttributeExpandedValue(const WideString sElemName, const WideString sAttrName, int aIdx);
	int __fastcall GetElementContentType(const WideString sName, int aIdx);
	int __fastcall GetElementIndexOf(const WideString sElemName);
	int __fastcall GetEntityIndexOf(const WideString sEntityName, bool aPEAllowed);
	WideString __fastcall GetEntityNotationName(const WideString sEntityName);
	WideString __fastcall GetEntityPublicId(const WideString sEntityName);
	WideString __fastcall GetEntitySystemId(const WideString sEntityName);
	int __fastcall GetEntityType(const WideString sEntityName, bool aPEAllowed);
	WideString __fastcall GetEntityValue(const WideString sEntityName, bool aPEAllowed);
	int __fastcall GetErrorCount(void);
	WideString __fastcall GetExternalTextEntityValue(const WideString sName, const WideString sPublicId, WideString sSystemId);
	Adxbase::TApdCharEncoding __fastcall GetInCharSet(void);
	void __fastcall Initialize(void);
	bool __fastcall IsEndDocument(void);
	bool __fastcall IsWhitespace(const wchar_t cVal);
	bool __fastcall LoadDataSource(AnsiString sSrcName, Classes::TStringList* oErrors);
	WideString __fastcall ParseAttribute(const WideString sName);
	WideString __fastcall ParseEntityRef(bool bPEAllowed);
	void __fastcall ParseCDSect(void);
	wchar_t __fastcall ParseCharRef(void);
	void __fastcall ParseComment(void);
	void __fastcall ParseContent(void);
	void __fastcall ParseDocTypeDecl(void);
	void __fastcall ParseDocument(void);
	void __fastcall ParseEndTag(void);
	void __fastcall ParseEq(void);
	void __fastcall ParseElement(void);
	void __fastcall ParseMisc(void);
	WideString __fastcall ParseParameterEntityRef(bool aPEAllowed, bool bSkip);
	void __fastcall ParsePCData(bool aInEntityRef);
	void __fastcall ParsePI(void);
	bool __fastcall ParsePIEx(void);
	void __fastcall ParsePrim(void);
	void __fastcall ParseProlog(void);
	void __fastcall ParseUntil(const int * S, const int S_Size);
	void __fastcall ParseWhitespace(void);
	void __fastcall ParseXMLDeclaration(void);
	void __fastcall PopDocument(void);
	void __fastcall PushDocument(void);
	void __fastcall PushString(const WideString sVal);
	wchar_t __fastcall ReadChar(const bool UpdatePos);
	void __fastcall ReadExternalIds(bool bInNotation, WideString * sIds);
	WideString __fastcall ReadLiteral(int wFlags, bool &HasEntRef);
	WideString __fastcall ReadNameToken(bool aValFirst);
	void __fastcall Require(const int * S, const int S_Size);
	void __fastcall RequireWhitespace(void);
	void __fastcall SetAttribute(const WideString sElemName, const WideString sName, int wType, const WideString sEnum, const WideString sValue, int wValueType);
	void __fastcall SetElement(const WideString sName, int wType, const WideString sContentModel);
	void __fastcall SetEntity(const WideString sEntityName, int wClass, const WideString sPublicId, const WideString sSystemId, const WideString sValue, const WideString sNotationName, bool aIsPE);
	void __fastcall SetInternalEntity(const WideString sName, const WideString sValue, bool aIsPE);
	void __fastcall SetNotation(const WideString sNotationName, const WideString sPublicId, const WideString sSystemId);
	void __fastcall SkipChar(void);
	void __fastcall SkipWhitespace(bool aNextDoc);
	bool __fastcall TryRead(const int * S, const int S_Size);
	void __fastcall ValidateAttribute(const WideString aValue, bool HasEntRef);
	void __fastcall ValidateCData(const WideString CDATA);
	void __fastcall ValidateElementName(const WideString aName);
	void __fastcall ValidateEncName(const AnsiString aValue);
	void __fastcall ValidateEntityValue(const WideString aValue, wchar_t aQuoteCh);
	bool __fastcall ValidateNameChar(const bool First, const wchar_t Char);
	void __fastcall ValidatePCData(const WideString aString, bool aInEntityRef);
	void __fastcall ValidatePublicID(const WideString aString);
	void __fastcall ValidateVersNum(const AnsiString aString);
	__property TApdValueEvent OnIgnorableWhitespace = {read=FOnIgnorableWhitespace, write=FOnIgnorableWhitespace};
	
public:
	__fastcall virtual TApdParser(Classes::TComponent* oOwner);
	__fastcall virtual ~TApdParser(void);
	WideString __fastcall GetErrorMsg(int wIdx);
	bool __fastcall ParseDataSource(const AnsiString sSource);
	bool __fastcall ParseMemory(void *aBuffer, int aSize);
	bool __fastcall ParseStream(Classes::TStream* oStream);
	__property int ErrorCount = {read=GetErrorCount, nodefault};
	__property Classes::TStringList* Errors = {read=FErrors};
	__property Adxbase::TApdCharEncoding InCharSet = {read=GetInCharSet, nodefault};
	__property bool IsStandAlone = {read=FIsStandAlone, nodefault};
	__property bool HasExternals = {read=FHasExternals, nodefault};
	__property int BufferSize = {read=FBufferSize, write=FBufferSize, default=8192};
	__property bool NormalizeData = {read=FNormalizeData, write=FNormalizeData, default=1};
	__property bool RaiseErrors = {read=FRaiseErrors, write=FRaiseErrors, default=0};
	__property TApdAttributeEvent OnAttribute = {read=FOnAttribute, write=FOnAttribute};
	__property TApdValueEvent OnCDATASection = {read=FOnCDATASection, write=FOnCDATASection};
	__property TApdValueEvent OnCharData = {read=FOnCharData, write=FOnCharData};
	__property TApdValueEvent OnComment = {read=FOnComment, write=FOnComment};
	__property TApdDocTypeDeclEvent OnDocTypeDecl = {read=FOnDocTypeDecl, write=FOnDocTypeDecl};
	__property Classes::TNotifyEvent OnEndDocument = {read=FOnEndDocument, write=FOnEndDocument};
	__property TApdValueEvent OnEndElement = {read=FOnEndElement, write=FOnEndElement};
	__property TApdNonXMLEntityEvent OnNonXMLEntity = {read=FOnNonXMLEntity, write=FOnNonXMLEntity};
	__property TApdPreserveSpaceEvent OnPreserveSpace = {read=FOnPreserveSpace, write=FOnPreserveSpace};
	__property TApdProcessInstrEvent OnProcessingInstruction = {read=FOnProcessingInstruction, write=FOnProcessingInstruction};
	__property TApdResolveEvent OnResolveEntity = {read=FOnResolveEntity, write=FOnResolveEntity};
	__property Classes::TNotifyEvent OnStartDocument = {read=FOnStartDocument, write=FOnStartDocument};
	__property TApdValueEvent OnStartElement = {read=FOnStartElement, write=FOnStartElement};
	__property TApdValueEvent OnBeginElement = {read=FOnBeginElement, write=FOnBeginElement};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adxparsr */
using namespace Adxparsr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdXParsr
