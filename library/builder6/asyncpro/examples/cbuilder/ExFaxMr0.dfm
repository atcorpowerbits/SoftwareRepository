�
 TFORM1 02  TPF0TForm1Form1Left� TopmWidth+HeightfCaption$ExFaxMR (Manual Receive Fax Example)
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style PositionpoScreenCenterPixelsPerInch`
TextHeight TLabelLabel1Left`Top.Width�HeightCaption\This example shows how to start an immediate fax receive by clicking a button..  This method  TLabelLabel2Left`Top:Width�HeightCaptionXwould be useful for instances where the modem should not automatically answer the phone.  TAdTerminalAdTerminal1LeftTop WidthHeight)CaptureFileAPROTERM.CAPComPortApdComPort1
ScrollbackColorclBlack
Font.ColorclSilverFont.Height�	Font.NameTerminal
Font.Style ParentColor
ParentFontTabOrder  TButtonButton1Left Top0WidthYHeightCaptionStart ReceiveTabOrder OnClickButton1Click  TApdReceiveFaxApdReceiveFax1ComPortApdComPort1StatusDisplayApdFaxStatus1
FaxFileExtAPFOnFaxFinishApdReceiveFax1FaxFinishOneFax	Left TopFakeProperty  TApdComPortApdComPort1InSize  OutSize  HWFlowOptions	hwfUseRTShwfRequireCTS TracingtlOn	TraceNameAPRO.TRCLoggingtlOnLogNameAPRO.LOGLeft�Top  TApdFaxStatusApdFaxStatus1PositionpoScreenCenterCtl3D	VisibleFaxApdReceiveFax1Caption
Fax StatusLeft�Top   