�
 TFORM1 0�  TPF0TForm1Form1Left� TopmWidth�HeightaCaptionForm1
Font.ColorclWindowTextFont.Height�	Font.NameSystem
Font.Style OnCreate
FormCreate	OnDestroyFormDestroyPixelsPerInch`
TextHeight TButtonButton1Left� Top!WidthKHeightCaption&Test
Font.ColorclBlackFont.Height�	Font.NameMS Sans Serif
Font.Style 
ParentFontTabOrder OnClickButton1Click  TMemoMemo1LeftTop Width�HeightLines.Strings;This example shows how to dynamically create a TApdComPort A(without dropping it on the form). The TApdComPort is created in ?the main form's OnCreate event. After the com port is created, Bthe com port's properties are set. Finally, a TriggerData handler is attached to the com port. =When the TEST button is pressed, an "ATZ" command is sent to Athe port. This will cause a modem attached to the port to return ="OK". When the TriggerData handler is called, we simply show -a message to indicate that it did get called. ;The key point of this example is to show how to attach the <trigger event when the com port is created dynamically. The ;trigger procedure must be a method of the form or a syntax /error will occur when trying to set the event.  TabOrder   