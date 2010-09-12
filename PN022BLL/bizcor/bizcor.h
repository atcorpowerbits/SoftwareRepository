// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BIZCORNATIVEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BIZCORNATIVEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BIZCORNATIVEDLL_EXPORTS
   #define BIZCORNATIVEDLL_API __declspec(dllexport)
#else
   #define BIZCORNATIVEDLL_API __declspec(dllimport)
#endif

// This class is exported from the bizcor.dll
class BIZCORNATIVEDLL_API CPerson {
public:
   // Initialization
   CPerson(LPCTSTR pszName, SYSTEMTIME birthDate);
   // Accessors
   unsigned int get_Age();

private:
   TCHAR m_sName[64];
   SYSTEMTIME m_birthDate;

   CPerson();
};


#ifdef __cplusplus
extern "C" {
#endif

extern BIZCORNATIVEDLL_API int nBizCorNativeDLL;

BIZCORNATIVEDLL_API int fnBizCorNativeDLL(void);

#ifdef __cplusplus
}
#endif
