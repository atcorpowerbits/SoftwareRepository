�
 TAPXLINEDLG 0�  TPF0TApxLineDlg
ApxLineDlgLeft�Top�ActiveControlcbxBaudRateBorderIconsbiSystemMenu BorderStylebsDialogCaptionDirect to Com PortClientHeightClientWidth5Color	clBtnFaceFont.CharsetDEFAULT_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style OldCreateOrderPositionpoScreenCenter
OnActivateFormActivatePixelsPerInch`
TextHeight TBevelBevel1LeftTopWidthHeightShape	bsTopLine  TLabelLabel3LeftTopWidthYHeightCaptionPort configuration    TLabelLabel4LeftTopWidth1HeightCaption&Baud rate:FocusControlcbxBaudRate  TLabelLabel5LeftTop7WidthHeightCaption&Parity:FocusControl	cbxParity  TLabelLabel6Left� TopWidth-HeightCaption&Data bits:FocusControlcbxDataBits  TLabelLabel7Left� Top7Width,HeightCaption&Stop bits:FocusControlcbxStopBits  TBevelBevel2LeftTop[WidthHeightShape	bsTopLine  TLabelLabel8LeftTopUWidth?HeightCaptionFlow control    TLabelLabel1LeftTop� Width.HeightCaption
&Xon char:FocusControl
edtXonChar  TLabelLabel2Left� Top� Width.HeightCaptionXo&ff char:FocusControledtXoffChar  TBevelBevel3LeftTopmWidthHeightShape	bsTopLine  TLabelLabel9LeftTopgWidth4HeightCaption
Hardware    TBevelBevel4LeftTop� WidthHeightShape	bsTopLine  TLabelLabel10LeftTop� Width0HeightCaption
Software    TButtonbtnOkLeft� Top� WidthKHeightCaptionOKDefault	ModalResultTabOrderOnClick
btnOkClick  TButton	btnCancelLeft� Top� WidthKHeightCancel	CaptionCancelModalResultTabOrderOnClickbtnCancelClick  	TComboBoxcbxBaudRateLeftETopWidthKHeight
ItemHeightTabOrder OnChangecbxBaudRateChangeItems.Strings3006001200240048009600192003840057600115200   	TComboBox	cbxParityLeftETop3WidthKHeightStylecsDropDownList
ItemHeightTabOrderItems.StringsNoneOddEvenMarkSpace   	TComboBoxcbxDataBitsLeft� TopWidthKHeightStylecsDropDownList
ItemHeightTabOrderItems.Strings8765   	TComboBoxcbxStopBitsLeft� Top3WidthKHeightStylecsDropDownList
ItemHeightTabOrderItems.Strings12   	TCheckBox	chkUseDTRLeftTopwWidthIHeightCaptionUse D&TRTabOrder  	TCheckBox	chkUseRTSLeft� TopwWidthIHeightCaptionUse &RTSTabOrder  	TCheckBoxchkSWTransmitLeftTop� WidthiHeightCaptionSoftware tr&ansmitTabOrder  	TCheckBoxchkSWReceiveLeft� Top� WidthiHeightCaptionSoft&ware receiveTabOrder	  	TCheckBoxchkRequireDSRLeftTop� WidthYHeightCaptionR&equire DSRTabOrder  	TCheckBoxchkRequireCTSLeft� Top� WidthYHeightCaptionRequire &CTSTabOrder  TEdit
edtXonCharLeftKTop� WidthHeightTabOrder
  TEditedtXoffCharLeft� Top� WidthHeightTabOrder   