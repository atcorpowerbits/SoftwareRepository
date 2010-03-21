# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = scor.exe
OBJFILES = scor.obj form_splash.obj form_main.obj ..\dbmgr\source\Dbmgr.obj \
    ..\patient\source\form_patient.obj Child.obj \
    ..\report\source\form_report_pwv.obj ..\meas\source\PWA.obj \
    ..\meas\source\Mathem.obj ..\meas\source\Measure.obj \
    ..\meas\source\Pressure.obj ..\meas\source\Pulse.obj \
    ..\meas\source\GetSeries.obj ..\capture\source\form_cappwa.obj \
    ..\capture\source\capture.obj ..\comms\source\Event.obj \
    ..\comms\source\Comms.obj ..\analysis\source\form_analysis_pwv.obj \
    ..\analysis\source\form_trend_pwv.obj ..\analysis\source\analysis.obj \
    ..\meas\source\form_pwa.obj ..\config\source\form_config.obj \
    ..\print\source\Print.obj ..\log\source\log.obj ..\meas\source\Common.obj \
    ..\meas\source\form_recalculate_pwa.obj ..\msg\source\MsgBox.obj \
    form_about.obj ..\capture\source\form_cappwv.obj \
    ..\meas\source\form_pwv.obj ..\meas\source\TSignal.obj \
    ..\meas\source\PWASignals.obj ..\export\source\form_export.obj \
    ..\meas\source\PWAPulse.obj form_selectdir.obj utils.obj \
    ..\analysis\source\form_select.obj ..\meas\source\PWV.obj \
    ..\meas\source\PWVSignals.obj ..\meas\source\PWVSite.obj \
    ..\report\source\form_report_pwa.obj \
    ..\meas\source\form_recalculate_pwv.obj \
    ..\analysis\source\form_trend_pwa.obj \
    ..\analysis\source\form_analysis_pwa.obj ..\meas\source\TBuffer.obj \
    ..\patient\source\form_patlist.obj ..\capture\source\form_cappwm.obj \
    ..\report\source\form_report_pwm.obj ..\meas\source\form_pwm.obj \
    ..\meas\source\PWM.obj ..\meas\source\TStack.obj \
    ..\multdb\source\form_merge.obj ..\comms\source\usbDriver.obj \
    ..\comms\source\usbComms.obj ..\print\source\form_batchprint.obj \
    ..\report\source\report.obj ..\export\source\form_export_database.obj \
    ..\multdb\source\form_multdb.obj ..\capture\source\form_caphrv.obj \
    ..\meas\source\hrvclass.obj ..\meas\source\form_hrv.obj \
    ..\meas\source\hrvtime.obj ..\report\source\form_report_hrv.obj \
    ..\meas\source\HRVfrequency.obj ..\meas\source\form_recalculate_hrv.obj
RESFILES = scor.res ..\msg\source\MsgDef.res
MAINSOURCE = scor.cpp
RESDEPEN = $(RESFILES) form_splash.dfm form_main.dfm ..\dbmgr\source\Dbmgr.dfm \
    ..\patient\source\form_patient.dfm ..\report\source\form_report_pwv.dfm \
    ..\capture\source\form_cappwa.dfm ..\analysis\source\form_analysis_pwv.dfm \
    ..\analysis\source\form_trend_pwv.dfm ..\meas\source\form_pwa.dfm \
    ..\config\source\form_config.dfm ..\meas\source\form_recalculate_pwa.dfm \
    form_about.dfm ..\capture\source\form_cappwv.dfm \
    ..\meas\source\form_pwv.dfm ..\export\source\form_export.dfm \
    form_selectdir.dfm ..\analysis\source\form_select.dfm \
    ..\report\source\form_report_pwa.dfm \
    ..\meas\source\form_recalculate_pwv.dfm \
    ..\analysis\source\form_trend_pwa.dfm \
    ..\analysis\source\form_analysis_pwa.dfm \
    ..\patient\source\form_patlist.dfm ..\capture\source\form_cappwm.dfm \
    ..\report\source\form_report_pwm.dfm ..\meas\source\form_pwm.dfm \
    ..\multdb\source\form_merge.dfm ..\print\source\form_batchprint.dfm \
    ..\export\source\form_export_database.dfm ..\multdb\source\form_multdb.dfm \
    ..\capture\source\form_caphrv.dfm ..\meas\source\form_hrv.dfm \
    ..\report\source\form_report_hrv.dfm ..\meas\source\form_recalculate_hrv.dfm
LIBFILES = "C:\Program Files\Borland\CBuilder6\Lib\Release\adortl.lib" \
    "C:\Program Files\Borland\CBuilder6\Lib\qrpt.lib" \
    ..\..\..\LIBRARY\Builder6\asyncpro\source\A406_R61.lib \
    ..\..\..\LIBRARY\Builder6\fftw\fftw3.lib
IDLFILES = 
IDLGENFILES = 
LIBRARIES = sdlbasepack_82C6.lib sdlmathpack_82C6.lib TeeImage.lib qrpt.lib \
    visualclx.lib adortl.lib TeeUI.lib TeePro.lib Tee.lib bdertl.lib vclx.lib \
    vcldbx.lib vcldb.lib dbrtl.lib vcl.lib rtl.lib
PACKAGES = vclx.bpi rtl.bpi vcl.bpi dbrtl.bpi vcldb.bpi bdertl.bpi vcldbx.bpi \
    bcbsmp.bpi dclocx.bpi A406_R61.bpi dclado6.bpi DCLTeP.bpi
SPARELIBS = rtl.lib vcl.lib dbrtl.lib vcldb.lib vcldbx.lib vclx.lib bdertl.lib Tee.lib \
    TeePro.lib TeeUI.lib adortl.lib visualclx.lib qrpt.lib TeeImage.lib \
    sdlmathpack_82C6.lib sdlbasepack_82C6.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = __cplusplus;_DEBUG
SYSDEFINES = NO_STRICT
INCLUDEPATH = K:\projects\016-S2000\source;..\report;..\multdb\source;..\export\source;..\import\source;..\msg\source;..\log\source;..\print\source;..\config\source;..\analysis\source;..\comms\source;..\capture\source;..\meas\source;..\report\source;..\patient\source;..\dbmgr\source;$(BCB)\include;$(BCB)\include\vcl;K:\projects\LIBRARY\BUILDER\ezusb;K:\projects\LIBRARY\Builder6\asyncpro\source;K:\projects\LIBRARY\Builder6\SDLSuite82\basepack\C6;K:\projects\LIBRARY\Builder6\SDLSuite82\mathpack\C6;K:\projects\LIBRARY\Builder6\fftw
LIBPATH = "K:\projects\016-S2000\source";..\report;..\multdb\source;..\export\source;..\import\source;..\msg\source;..\log\source;..\print\source;..\config\source;..\analysis\source;..\comms\source;..\capture\source;..\meas\source;..\report\source;..\patient\source;..\dbmgr\source;$(BCB)\lib;$(BCB)\lib\obj;K:\projects\LIBRARY\Builder6\asyncpro\source;K:\projects\LIBRARY\Builder6\SDLSuite82\basepack\C6;K:\projects\LIBRARY\Builder6\SDLSuite82\mathpack\C6;K:\projects\LIBRARY\Builder6\fftw
WARNINGS= -w-par -w-8027 -w-8026
PATHCPP = .;..\dbmgr\source;..\patient\source;..\report\source;..\meas\source;..\capture\source;..\comms\source;..\analysis\source;..\config\source;..\print\source;..\log\source;..\msg\source;..\export\source;..\multdb\source
PATHASM = .;
PATHPAS = .;
PATHRC = .;..\msg\source
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -Od -H=$(BCB)\lib\vcl60.csm -Hc -Vx -Ve -Tkh30000 -fp -X- -r- -a8 -6 -b- \
    -k -y -v -vi- -c -tW -tWM
IDLCFLAGS = -IK:\projects\016-S2000\source -I..\report -I..\multdb\source \
    -I..\export\source -I..\import\source -I..\msg\source -I..\log\source \
    -I..\print\source -I..\config\source -I..\analysis\source \
    -I..\comms\source -I..\capture\source -I..\meas\source -I..\report\source \
    -I..\patient\source -I..\dbmgr\source -I$(BCB)\include \
    -I$(BCB)\include\vcl -IK:\projects\LIBRARY\BUILDER\ezusb \
    -IK:\projects\LIBRARY\Builder6\asyncpro\source \
    -IK:\projects\LIBRARY\Builder6\SDLSuite82\basepack\C6 \
    -IK:\projects\LIBRARY\Builder6\SDLSuite82\mathpack\C6 \
    -IK:\projects\LIBRARY\Builder6\fftw -src_suffix cpp -D__cplusplus -D_DEBUG \
    -boa
PFLAGS = -$Y+ -$W -$O- -$A8 -v -M -JPHNE
RFLAGS = 
AFLAGS = /mx /w2 /zi
LFLAGS = -D"" -H:0x400000 -Hc:0x6000 -S:0x500000 -Sc:0xD0000 -aa -Tpe -GD -s -Gn -w \
    -v
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------




