�
 TFORM1 0�  TPF0TForm1Form1Left� TopmBorderIconsbiSystemMenu
biMinimize BorderStylebsDialogCaptionSimple Fax on DemandClientHeight� ClientWidth	Color	clBtnFace
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style OnCreate
FormCreatePixelsPerInch`
TextHeight TButtonButton1LeftTop� Width|HeightCaptionSelect A TAPI DeviceTabOrder OnClickButton1Click  TButtonAnswerButtonLeft� Top� WidthLHeightCaptionAnswer CallsTabOrderOnClickAnswerButtonClick  	TGroupBox	GroupBox1LeftTopWidth� Height� CaptionStatusTabOrder TLabelLabel1LeftTopWidth� Height	AlignmenttaCenterAutoSizeCaptionFax on Demand Current State  TLabelLabel2LeftTopDWidth� Height	AlignmenttaCenterAutoSizeCaptionWave Device Status  TLabelLabel3LeftTopqWidth� Height	AlignmenttaCenterAutoSizeCaption
Fax Number  TEditEdit1LeftTop#Width� HeightColorclSilverReadOnly	TabOrder TextStateGreeting  TEditEdit2LeftTopRWidth� HeightColorclSilverReadOnly	TabOrderTextWave Device Idle...  TEditEdit3LeftTopWidth� HeightColorclSilverReadOnly	TabOrder   TApdTapiDeviceApdTapiDevice1ComPortApdComPort1ShowTapiDevices		ShowPorts	EnableVoiceOnTapiPortOpenApdTapiDevice1TapiPortOpenOnTapiConnectApdTapiDevice1TapiConnect
OnTapiDTMFApdTapiDevice1TapiDTMFOnTapiWaveNotifyApdTapiDevice1TapiWaveNotifyLeft  TApdSendFaxApdSendFax1FaxClassfcClass2	StationIDABCComPortApdComPort1StatusDisplayApdFaxStatus1AbortNoConnect	
FaxFileExtAPFOnFaxFinishApdSendFax1FaxFinishEnhTextEnabledEnhHeaderFont.ColorclWindowTextEnhHeaderFont.Height�EnhHeaderFont.NameMS Sans SerifEnhHeaderFont.Style EnhFont.ColorclWindowTextEnhFont.Height�EnhFont.NameMS Sans SerifEnhFont.Style 
HeaderLineHILeft8FakeProperty  TApdFaxStatusApdFaxStatus1PositionpoScreenCenterCtl3D	VisibleFaxApdSendFax1Caption
Fax StatusLeftT  TApdComPortApdComPort1InSize  OutSize  AutoOpenHWFlowOptions	hwfUseRTShwfRequireCTS 
BufferFull�BufferResume3TracingtlOn	TraceName	VOICE.TRCLoggingtlOnLogName	VOICE.LOG  TTimerTimer1EnabledInterval'OnTimerTimer1TimerLeftp   