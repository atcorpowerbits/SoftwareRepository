object Form1: TForm1
  Left = 706
  Top = 274
  Width = 460
  Height = 548
  Caption = 'NumLab Demo Program (C++ Version)'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Bevel1: TBevel
    Left = 16
    Top = 32
    Width = 281
    Height = 33
    Style = bsRaised
  end
  object NumLab1: TNumLab
    Left = 24
    Top = 37
    Width = 265
    Height = 22
    Alignment = taCenter
    ColorLabBakG = clSilver
    ColorLabText = clBlue
    ColorOutBakG = clBlack
    ColorOutText = clYellow
    ColorScheme = csBWG
    Comma = False
    DisplayType = dtFixP
    DTFormat = 'mmm-dd, yyyy'
    Empty = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ForcePlusSign = False
    FrameStyle = fsEmbossed
    LabelWidth = 120
    LeftSpace = 100
    LeftText = 'Voltage'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    ParentFont = False
    Precision = 4
    RightText = 'mV'
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 1555.25
  end
  object Bevel2: TBevel
    Left = 312
    Top = 8
    Width = 121
    Height = 65
    Style = bsRaised
  end
  object NLabPreci: TNumLab
    Left = 320
    Top = 16
    Width = 105
    Height = 22
    Alignment = taCenter
    ColorLabBakG = clGray
    ColorLabText = clWhite
    ColorOutBakG = clBtnFace
    ColorOutText = clBlack
    ColorScheme = csBWG
    Comma = False
    DisplayType = dtFixP
    DTFormat = 'mmm-dd, yyyy'
    Empty = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ForcePlusSign = False
    FrameStyle = fsLowered
    LabelWidth = 30
    LeftSpace = 70
    LeftText = 'Precision'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    ParentFont = False
    Precision = 0
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 4
  end
  object Bevel6: TBevel
    Left = 16
    Top = 440
    Width = 281
    Height = 73
    Shape = bsFrame
  end
  object Bevel3: TBevel
    Left = 312
    Top = 88
    Width = 121
    Height = 65
    Style = bsRaised
  end
  object NLabWidth: TNumLab
    Left = 320
    Top = 96
    Width = 105
    Height = 22
    Alignment = taCenter
    ColorLabBakG = clGray
    ColorLabText = clWhite
    ColorOutBakG = clBtnFace
    ColorOutText = clBlack
    ColorScheme = csBWG
    Comma = False
    DisplayType = dtInt
    DTFormat = 'mmm-dd, yyyy'
    Empty = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ForcePlusSign = False
    FrameStyle = fsRaised
    LabelWidth = 30
    LeftSpace = 70
    LeftText = 'Width'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    ParentFont = False
    Precision = 0
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 265
  end
  object Bevel4: TBevel
    Left = 312
    Top = 168
    Width = 121
    Height = 65
    Style = bsRaised
  end
  object NLabLeftSpace: TNumLab
    Left = 320
    Top = 176
    Width = 105
    Height = 22
    Alignment = taCenter
    ColorLabBakG = clGray
    ColorLabText = clWhite
    ColorOutBakG = clBtnFace
    ColorOutText = clBlack
    ColorScheme = csBWG
    Comma = False
    DisplayType = dtInt
    DTFormat = 'mmm-dd, yyyy'
    Empty = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ForcePlusSign = False
    FrameStyle = fsLowered
    LabelWidth = 30
    LeftSpace = 70
    LeftText = 'Left Space'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    ParentFont = False
    Precision = 0
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 100
  end
  object NLabLabelWidth: TNumLab
    Left = 319
    Top = 256
    Width = 105
    Height = 22
    Alignment = taCenter
    ColorLabBakG = clGray
    ColorLabText = clWhite
    ColorOutBakG = clBtnFace
    ColorOutText = clBlack
    ColorScheme = csBWG
    Comma = False
    DisplayType = dtInt
    DTFormat = 'mmm-dd, yyyy'
    Empty = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ForcePlusSign = False
    FrameStyle = fsLowered
    LabelWidth = 30
    LeftSpace = 75
    LeftText = 'Label Width'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    ParentFont = False
    Precision = 0
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 100
  end
  object Bevel5: TBevel
    Left = 312
    Top = 248
    Width = 121
    Height = 65
    Style = bsRaised
  end
  object SBPrecis: TScrollBar
    Left = 320
    Top = 48
    Width = 105
    Height = 14
    Max = 10
    PageSize = 0
    Position = 4
    TabOrder = 0
    OnChange = SBPrecisChange
  end
  object ScrollBar1: TScrollBar
    Left = 16
    Top = 8
    Width = 281
    Height = 14
    Max = 1000
    PageSize = 0
    Position = 750
    TabOrder = 1
    OnChange = ScrollBar1Change
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 328
    Width = 281
    Height = 81
    Caption = 'Frame Style'
    TabOrder = 2
    object RBRaised: TRadioButton
      Left = 8
      Top = 24
      Width = 105
      Height = 17
      Caption = 'Raised'
      TabOrder = 0
      OnClick = RBRaisedClick
    end
    object RBLowered: TRadioButton
      Left = 8
      Top = 40
      Width = 105
      Height = 17
      Caption = 'Lowered'
      TabOrder = 1
      OnClick = RBLoweredClick
    end
    object RbEmbossed: TRadioButton
      Left = 8
      Top = 56
      Width = 105
      Height = 17
      Caption = 'Embossed'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RbEmbossedClick
    end
    object RBEngraved: TRadioButton
      Left = 128
      Top = 24
      Width = 105
      Height = 17
      Caption = 'Engraved'
      TabOrder = 3
      OnClick = RBEngravedClick
    end
    object RBSimple: TRadioButton
      Left = 128
      Top = 40
      Width = 89
      Height = 17
      Caption = 'Simple'
      TabOrder = 4
      OnClick = RBSimpleClick
    end
    object RBNone: TRadioButton
      Left = 128
      Top = 56
      Width = 81
      Height = 17
      Caption = 'None'
      TabOrder = 5
      OnClick = RBNoneClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 160
    Width = 281
    Height = 161
    Caption = 'Display Type'
    TabOrder = 3
    object RBFixP: TRadioButton
      Left = 8
      Top = 24
      Width = 120
      Height = 17
      Caption = 'Fixed point'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RBFixPClick
    end
    object RBFloat: TRadioButton
      Left = 8
      Top = 40
      Width = 120
      Height = 17
      Caption = 'Float'
      TabOrder = 1
      OnClick = RBFloatClick
    end
    object RBInt: TRadioButton
      Left = 8
      Top = 56
      Width = 120
      Height = 17
      Caption = 'Integer'
      TabOrder = 2
      OnClick = RBIntClick
    end
    object RBZeroInt: TRadioButton
      Left = 8
      Top = 72
      Width = 120
      Height = 17
      Caption = 'Integer/zeroes'
      TabOrder = 3
      OnClick = RBZeroIntClick
    end
    object RBExp: TRadioButton
      Left = 8
      Top = 88
      Width = 120
      Height = 17
      Caption = 'Exponential'
      TabOrder = 4
      OnClick = RBExpClick
    end
    object RBHex: TRadioButton
      Left = 8
      Top = 136
      Width = 120
      Height = 17
      Caption = 'Hex'
      TabOrder = 5
      OnClick = RBHexClick
    end
    object RBDateTime: TRadioButton
      Left = 136
      Top = 40
      Width = 113
      Height = 17
      Caption = 'Date/Time'
      TabOrder = 6
      OnClick = RBDateTimeClick
    end
    object EdDateTime: TEdit
      Left = 136
      Top = 56
      Width = 121
      Height = 24
      Enabled = False
      TabOrder = 7
      Text = 'mmm-dd, yyyy'
      OnChange = EdDateTimeChange
    end
    object RBBin: TRadioButton
      Left = 8
      Top = 104
      Width = 120
      Height = 17
      Caption = 'Binary'
      TabOrder = 8
      OnClick = RBBinClick
    end
    object RBOct: TRadioButton
      Left = 8
      Top = 120
      Width = 120
      Height = 17
      Caption = 'Octal'
      TabOrder = 9
      OnClick = RBOctClick
    end
    object RBState: TRadioButton
      Left = 136
      Top = 24
      Width = 113
      Height = 17
      Caption = 'State'
      TabOrder = 10
      OnClick = RBStateClick
    end
    object RBLatDeg: TRadioButton
      Left = 136
      Top = 104
      Width = 138
      Height = 17
      Caption = 'Degrees'
      TabOrder = 11
      OnClick = RBLatDegClick
    end
    object RBLatDegMin: TRadioButton
      Left = 136
      Top = 120
      Width = 138
      Height = 17
      Caption = 'Deg. Minutes'
      TabOrder = 12
      OnClick = RBLatDegMinClick
    end
    object RBLatDegMinSec: TRadioButton
      Left = 136
      Top = 136
      Width = 138
      Height = 17
      Caption = 'Deg. Min. Seconds'
      TabOrder = 13
      OnClick = RBLatDegMinSecClick
    end
  end
  object ColSel3: TColSel
    Left = 168
    Top = 448
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clYellow
    ShowHint = True
    TabOrder = 4
    OnChange = ColSel3Change
  end
  object ColSel1: TColSel
    Left = 32
    Top = 448
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clBlue
    ShowHint = True
    TabOrder = 5
    OnChange = ColSel1Change
  end
  object ColSel2: TColSel
    Left = 32
    Top = 480
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clSilver
    ShowHint = True
    TabOrder = 6
    OnChange = ColSel2Change
  end
  object ColSel4: TColSel
    Left = 168
    Top = 480
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    ParentShowHint = False
    SelColor = clBlack
    ShowHint = True
    TabOrder = 7
    OnChange = ColSel4Change
  end
  object GroupBox3: TGroupBox
    Left = 112
    Top = 72
    Width = 89
    Height = 81
    Caption = 'Alignment'
    TabOrder = 8
    object RBCenter: TRadioButton
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'Center'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RBCenterClick
    end
    object RBLeft: TRadioButton
      Left = 8
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Left'
      TabOrder = 1
      OnClick = RBLeftClick
    end
    object RBRight: TRadioButton
      Left = 8
      Top = 56
      Width = 65
      Height = 17
      Caption = 'Right'
      TabOrder = 2
      OnClick = RBRightClick
    end
  end
  object BButExit: TBitBtn
    Left = 352
    Top = 480
    Width = 89
    Height = 33
    Caption = 'Exit'
    TabOrder = 9
    OnClick = BButExitClick
    Glyph.Data = {
      72010000424D7201000000000000760000002800000015000000150000000100
      040000000000FC00000000000000000000001000000010000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
      888888888880880000000000000008888880880EEEEEEEEEEE00088888808806
      66666666E0008888888088066666666E000888888880880666666666E0888888
      88808806666666666E088888888088066666666666E088888880880666666666
      666E088880008806666666666666E088800088066446666666666E0882018806
      40446666666666E0888088040004466666666600030988000080446666666000
      8888880008880446666600088988880088888044666000888910888888888804
      4600088885F08888888888804000888885F08888888888880008888885F08888
      888888888088888885F08888888888888888888885F0}
  end
  object SBWidth: TScrollBar
    Left = 320
    Top = 128
    Width = 105
    Height = 14
    Max = 265
    PageSize = 0
    Position = 265
    TabOrder = 10
    OnChange = SBWidthChange
  end
  object SBLeftSpace: TScrollBar
    Left = 320
    Top = 208
    Width = 105
    Height = 14
    PageSize = 0
    Position = 100
    TabOrder = 11
    OnChange = SBLeftSpaceChange
  end
  object ScrollBar2: TScrollBar
    Left = 320
    Top = 288
    Width = 105
    Height = 14
    Max = 130
    PageSize = 0
    Position = 100
    TabOrder = 12
    OnChange = ScrollBar2Change
  end
  object GroupBox4: TGroupBox
    Left = 16
    Top = 72
    Width = 89
    Height = 81
    Caption = 'Alignment'
    TabOrder = 13
    object RadioButton1: TRadioButton
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'Center'
      TabOrder = 0
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Left'
      TabOrder = 1
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 56
      Width = 65
      Height = 17
      Caption = 'Right'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RadioButton3Click
    end
  end
  object GroupBox5: TGroupBox
    Left = 208
    Top = 72
    Width = 89
    Height = 81
    Caption = 'Alignment'
    TabOrder = 14
    object RadioButton4: TRadioButton
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'Center'
      TabOrder = 0
      OnClick = RadioButton4Click
    end
    object RadioButton5: TRadioButton
      Left = 8
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Left'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = RadioButton5Click
    end
    object RadioButton6: TRadioButton
      Left = 8
      Top = 56
      Width = 65
      Height = 17
      Caption = 'Right'
      TabOrder = 2
      OnClick = RadioButton6Click
    end
  end
  object CBForcePlusSign: TCheckBox
    Left = 16
    Top = 416
    Width = 129
    Height = 17
    Caption = 'Force Plus Sign'
    TabOrder = 15
    OnClick = CBForcePlusSignClick
  end
end
