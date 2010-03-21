object Form1: TForm1
  Left = 19
  Top = 88
  Width = 628
  Height = 375
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 504
    Top = 144
    Width = 23
    Height = 22
    OnClick = SpeedButton1Click
  end
  object Label2: TLabel
    Left = 8
    Top = 16
    Width = 38
    Height = 15
    Caption = 'Label2'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object RadioGroup1: TRadioGroup
    Left = 392
    Top = 40
    Width = 137
    Height = 97
    Caption = 'Response'
    Items.Strings = (
      'Yes'
      'No')
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 8
    Top = 160
    Width = 225
    Height = 21
    TabOrder = 0
    Text = '??????????'
  end
  object ListBox1: TListBox
    Left = 8
    Top = 40
    Width = 377
    Height = 113
    ItemHeight = 13
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object Button1: TButton
    Left = 224
    Top = 320
    Width = 75
    Height = 25
    Caption = 'Done'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 184
    Width = 337
    Height = 105
    TabOrder = 4
  end
end
