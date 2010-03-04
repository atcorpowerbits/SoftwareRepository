object FrmControl: TFrmControl
  Left = 492
  Top = 586
  Width = 693
  Height = 367
  Caption = 'Control Panel for Dot Matrix Display'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 8
    Top = 160
    Width = 87
    Height = 16
    Caption = 'Light Dot Color'
  end
  object Label2: TLabel
    Left = 8
    Top = 208
    Width = 88
    Height = 16
    Caption = 'Dark Dot Color'
  end
  object Label3: TLabel
    Left = 8
    Top = 257
    Width = 108
    Height = 16
    Caption = 'Background Color'
  end
  object Label4: TLabel
    Left = 8
    Top = 8
    Width = 124
    Height = 16
    Caption = 'Text to be Displayed'
  end
  object RGDotSize: TRadioGroup
    Left = 8
    Top = 56
    Width = 73
    Height = 89
    Caption = ' Dot Size '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8')
    TabOrder = 0
    OnClick = RGDotSizeClick
  end
  object RGDotSpacing: TRadioGroup
    Left = 96
    Top = 56
    Width = 97
    Height = 57
    Caption = ' Dot Spacing '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      '0'
      '1'
      '2'
      '3')
    TabOrder = 1
    OnClick = RGDotSpacingClick
  end
  object RGScroll: TRadioGroup
    Left = 208
    Top = 56
    Width = 97
    Height = 121
    Caption = ' Scroll Mode '
    ItemIndex = 2
    Items.Strings = (
      'Off'
      'Left'
      'Right'
      'Down'
      'Up'
      'By Mouse')
    TabOrder = 2
    OnClick = RGScrollClick
  end
  object RGScrollSpeed: TRadioGroup
    Left = 320
    Top = 56
    Width = 105
    Height = 73
    Caption = ' Scroll Speed '
    Columns = 2
    ItemIndex = 2
    Items.Strings = (
      '100'
      '50'
      '20'
      '10'
      '5'
      '2')
    TabOrder = 3
    OnClick = RGScrollSpeedClick
  end
  object RGScrollStep: TRadioGroup
    Left = 440
    Top = 56
    Width = 105
    Height = 73
    Caption = ' Scroll Step '
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      '1'
      '2'
      '3'
      '5'
      '7'
      '24')
    TabOrder = 4
    OnClick = RGScrollStepClick
  end
  object CSelDotFg: TColSel
    Left = 8
    Top = 176
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clLime
    ShowHint = True
    TabOrder = 5
    OnChange = CSelDotFgChange
  end
  object CSelDotBg: TColSel
    Left = 8
    Top = 224
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = 4210752
    ShowHint = True
    TabOrder = 6
    OnChange = CSelDotBgChange
  end
  object CSelBg: TColSel
    Left = 8
    Top = 275
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clBlack
    ShowHint = True
    TabOrder = 7
    OnChange = CSelBgChange
  end
  object CBoxProportional: TCheckBox
    Left = 192
    Top = 192
    Width = 153
    Height = 17
    Caption = 'Proportional Font'
    TabOrder = 8
    OnClick = CBoxProportionalClick
  end
  object RGFrameStyle: TRadioGroup
    Left = 560
    Top = 152
    Width = 105
    Height = 113
    Caption = ' FrameStyle '
    ItemIndex = 1
    Items.Strings = (
      'None'
      'Simple'
      'Lowered'
      'Raised'
      'Embossed'
      'Engraved')
    TabOrder = 9
    OnClick = RGFrameStyleClick
  end
  object BButFont: TBitBtn
    Left = 184
    Top = 272
    Width = 153
    Height = 25
    Caption = 'Change Font'
    TabOrder = 10
    OnClick = BButFontClick
  end
  object ComboBlockMode: TComboBox
    Left = 184
    Top = 216
    Width = 145
    Height = 24
    Style = csDropDownList
    ItemHeight = 16
    TabOrder = 11
    OnChange = ComboBlockModeChange
    Items.Strings = (
      'No Blocks'
      'Blocks'
      'Raster')
  end
  object EdText: TEdit
    Left = 8
    Top = 24
    Width = 665
    Height = 24
    TabOrder = 12
    Text = '<dat>% of the day is gone'
    OnChange = EdTextChange
  end
  object RGPlaceHolder: TRadioGroup
    Left = 416
    Top = 152
    Width = 129
    Height = 89
    Caption = ' Place Holder '
    ItemIndex = 1
    Items.Strings = (
      'Literal'
      'Percent of Day'
      'Time'
      'Date/Time')
    TabOrder = 13
  end
  object BButCloseUI: TBitBtn
    Left = 472
    Top = 272
    Width = 201
    Height = 57
    Caption = 'Close Control Panel'
    TabOrder = 14
    OnClick = BButCloseUIClick
  end
  object BButDefaultFont: TBitBtn
    Left = 184
    Top = 304
    Width = 153
    Height = 25
    Caption = 'Load Default Font'
    TabOrder = 15
    OnClick = BButDefaultFontClick
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 624
    Top = 88
  end
end
