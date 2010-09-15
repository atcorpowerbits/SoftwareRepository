object Form1: TForm1
  Left = 559
  Top = 262
  Width = 316
  Height = 575
  Caption = 'Color Calculator'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 64
    Top = 16
    Width = 25
    Height = 16
    Alignment = taRightJustify
    Caption = 'Hue'
  end
  object Label2: TLabel
    Left = 29
    Top = 56
    Width = 60
    Height = 16
    Alignment = taRightJustify
    Caption = 'Saturation'
  end
  object Label3: TLabel
    Left = 41
    Top = 96
    Width = 48
    Height = 16
    Alignment = taRightJustify
    Caption = 'Intensity'
  end
  object LblHue: TLabel
    Left = 256
    Top = 16
    Width = 43
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblHue'
  end
  object LblSat: TLabel
    Left = 261
    Top = 56
    Width = 38
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblSat'
  end
  object LblIntens: TLabel
    Left = 246
    Top = 96
    Width = 53
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblIntens'
  end
  object LblRed: TLabel
    Left = 255
    Top = 411
    Width = 44
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblRed'
  end
  object LblGreen: TLabel
    Left = 244
    Top = 443
    Width = 55
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblGreen'
  end
  object LblBlue: TLabel
    Left = 254
    Top = 475
    Width = 45
    Height = 16
    Alignment = taRightJustify
    Caption = 'LblBlue'
  end
  object Label4: TLabel
    Left = 22
    Top = 411
    Width = 26
    Height = 16
    Alignment = taRightJustify
    Caption = 'Red'
  end
  object Label5: TLabel
    Left = 11
    Top = 443
    Width = 37
    Height = 16
    Alignment = taRightJustify
    Caption = 'Green'
  end
  object Label6: TLabel
    Left = 21
    Top = 475
    Width = 27
    Height = 16
    Alignment = taRightJustify
    Caption = 'Blue'
  end
  object Label7: TLabel
    Left = 8
    Top = 514
    Width = 74
    Height = 16
    Caption = 'HTML-Code'
  end
  object SBarHue: TScrollBar
    Left = 96
    Top = 16
    Width = 169
    Height = 20
    Max = 360
    PageSize = 0
    Position = 30
    TabOrder = 0
    OnChange = SBarIntensChange
  end
  object SBarSat: TScrollBar
    Left = 96
    Top = 56
    Width = 169
    Height = 20
    PageSize = 0
    Position = 50
    TabOrder = 1
    OnChange = SBarIntensChange
  end
  object SBarIntens: TScrollBar
    Left = 96
    Top = 96
    Width = 169
    Height = 20
    PageSize = 0
    Position = 80
    TabOrder = 2
    OnChange = SBarIntensChange
  end
  object PnlRed: TPanel
    Left = 56
    Top = 408
    Width = 209
    Height = 24
    TabOrder = 3
  end
  object PnlGreen: TPanel
    Left = 56
    Top = 440
    Width = 209
    Height = 24
    TabOrder = 4
  end
  object PnlBlue: TPanel
    Left = 56
    Top = 472
    Width = 209
    Height = 24
    TabOrder = 5
  end
  object PnlColor: TPanel
    Left = 8
    Top = 128
    Width = 289
    Height = 265
    TabOrder = 6
  end
  object EdHTML: TEdit
    Left = 88
    Top = 512
    Width = 81
    Height = 24
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 7
    Text = '#000000'
  end
  object ButInvert: TButton
    Left = 176
    Top = 512
    Width = 121
    Height = 25
    Caption = 'Invert Color'
    TabOrder = 8
    OnClick = ButInvertClick
  end
end
