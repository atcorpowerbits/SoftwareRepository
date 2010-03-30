object Form1: TForm1
  Left = 498
  Top = 282
  Width = 705
  Height = 533
  Caption = 'Sample Application for TMeter Component'
  Color = clSilver
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
  object Meter1: TMeter
    Left = 8
    Top = 48
    Width = 321
    Height = 249
    AnchorSize = 24
    AnchorCovered = True
    BkgndFillMode = bfSimple
    Caption = 'Left'
    ColorBakG = clNavy
    ColorCover = clSilver
    ColorScale = clSilver
    ColorScheme = csBWG
    ColorSclBkLow = clWhite
    ColorSclBkNorm = 33023
    ColorSclBkHigh = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -13
    Font.Name = 'BankGothic Md BT'
    Font.Style = [fsBold]
    FontCaption.Charset = ANSI_CHARSET
    FontCaption.Color = clYellow
    FontCaption.Height = -25
    FontCaption.Name = 'Courier'
    FontCaption.Style = [fsBold]
    FrameStyle = fsEmbossed
    LimWatchHighOn = True
    LimWatchLowOn = False
    LimWatchActColor = clRed
    LimWatchPsvColor = clSilver
    ThresholdLow = 10
    ThresholdHigh = 13
    MeterMaxValue = 15
    MeterDecPlaces = 0
    MeterNrTicks = 5
    MeterLayout = mlCirc90
    MeterShortTicks = False
    MeterScaleLine = False
    NeedleLayout.HeadSize = 20
    NeedleLayout.HeadAngle = 20
    NeedleLayout.HeadMidLeng = 20
    NeedleLayout.Thickness = 0
    NeedleLayout.ColorBody = clWhite
    NeedleLayout.ColorOutline = clSilver
    NeedleLayout.PercentNeedleLength = 100
    NeedleLayout.ShadowDx = 0
    NeedleLayout.ShadowDy = 0
    NeedleLayout.ShadowColor = clGray
    NeedleLayout.Visible = True
    NeedleLayoutSec.HeadSize = 20
    NeedleLayoutSec.HeadAngle = 30
    NeedleLayoutSec.HeadMidLeng = 20
    NeedleLayoutSec.Thickness = 0
    NeedleLayoutSec.ColorBody = clNavy
    NeedleLayoutSec.ColorOutline = clGray
    NeedleLayoutSec.PercentNeedleLength = 100
    NeedleLayoutSec.ShadowDx = 0
    NeedleLayoutSec.ShadowDy = 0
    NeedleLayoutSec.ShadowColor = clGray
    NeedleLayoutSec.Visible = False
    ParentFont = False
    RimBottom = 16
    RimTop = 8
    RimSide = 8
    ScaleBkVisible = True
    ScaleVisible = True
    ValueSec = 4
  end
  object Meter3: TMeter
    Left = 8
    Top = 416
    Width = 161
    Height = 89
    AnchorSize = 24
    AnchorCovered = False
    BkgndFillMode = bfSimple
    Caption = 'V'
    ColorBakG = clSilver
    ColorCover = clBtnFace
    ColorScale = clNavy
    ColorScheme = csBWG
    ColorSclBkLow = clSilver
    ColorSclBkNorm = clSilver
    ColorSclBkHigh = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    FontCaption.Charset = DEFAULT_CHARSET
    FontCaption.Color = clWindowText
    FontCaption.Height = -13
    FontCaption.Name = 'MS Sans Serif'
    FontCaption.Style = [fsBold]
    FrameStyle = fsSimple
    LimWatchHighOn = True
    LimWatchLowOn = True
    LimWatchActColor = clRed
    LimWatchPsvColor = clLime
    ThresholdHigh = 8
    MeterMaxValue = 8
    MeterDecPlaces = 0
    MeterNrTicks = 4
    MeterLayout = mlCirc90
    MeterShortTicks = True
    MeterScaleLine = False
    NeedleLayout.HeadSize = 0
    NeedleLayout.HeadAngle = 45
    NeedleLayout.HeadMidLeng = 0
    NeedleLayout.Thickness = 0
    NeedleLayout.ColorBody = clSilver
    NeedleLayout.ColorOutline = clRed
    NeedleLayout.PercentNeedleLength = 100
    NeedleLayout.ShadowDx = 0
    NeedleLayout.ShadowDy = 0
    NeedleLayout.ShadowColor = clGray
    NeedleLayout.Visible = True
    NeedleLayoutSec.HeadSize = 20
    NeedleLayoutSec.HeadAngle = 30
    NeedleLayoutSec.HeadMidLeng = 20
    NeedleLayoutSec.Thickness = 0
    NeedleLayoutSec.ColorBody = clSilver
    NeedleLayoutSec.ColorOutline = clBlack
    NeedleLayoutSec.PercentNeedleLength = 100
    NeedleLayoutSec.ShadowDx = 0
    NeedleLayoutSec.ShadowDy = 0
    NeedleLayoutSec.ShadowColor = clGray
    NeedleLayoutSec.Visible = False
    ParentFont = False
    ParentShowHint = False
    RimBottom = 0
    RimTop = 0
    RimSide = 0
    ScaleBkWidth = 10
    ScaleBkVisible = False
    ScaleVisible = True
    ShowHint = True
  end
  object Meter2: TMeter
    Left = 176
    Top = 344
    Width = 161
    Height = 153
    AnchorSize = 12
    AnchorCovered = True
    BkgndFillMode = bfSimple
    ColorBakG = 13289655
    ColorCover = clSilver
    ColorScale = clNavy
    ColorScheme = csBWG
    ColorSclBkLow = clLime
    ColorSclBkNorm = 33023
    ColorSclBkHigh = clRed
    FontCaption.Charset = DEFAULT_CHARSET
    FontCaption.Color = clWindowText
    FontCaption.Height = -13
    FontCaption.Name = 'MS Sans Serif'
    FontCaption.Style = []
    FrameStyle = fsRaised
    LimWatchHighOn = True
    LimWatchLowOn = True
    LimWatchActColor = clRed
    LimWatchPsvColor = clOlive
    ThresholdHigh = 1
    MeterMinValue = -2
    MeterMaxValue = 10
    MeterDecPlaces = 0
    MeterNrTicks = 3
    MeterLayout = mlCirc300
    MeterShortTicks = True
    MeterScaleLine = False
    NeedleLayout.HeadSize = 0
    NeedleLayout.HeadAngle = 45
    NeedleLayout.HeadMidLeng = 0
    NeedleLayout.Thickness = 0
    NeedleLayout.ColorBody = clSilver
    NeedleLayout.ColorOutline = clRed
    NeedleLayout.PercentNeedleLength = 100
    NeedleLayout.ShadowDx = 0
    NeedleLayout.ShadowDy = 0
    NeedleLayout.ShadowColor = clGray
    NeedleLayout.Visible = True
    NeedleLayoutSec.HeadSize = 20
    NeedleLayoutSec.HeadAngle = 30
    NeedleLayoutSec.HeadMidLeng = 20
    NeedleLayoutSec.Thickness = 0
    NeedleLayoutSec.ColorBody = clSilver
    NeedleLayoutSec.ColorOutline = clBlack
    NeedleLayoutSec.PercentNeedleLength = 100
    NeedleLayoutSec.ShadowDx = 0
    NeedleLayoutSec.ShadowDy = 0
    NeedleLayoutSec.ShadowColor = clGray
    NeedleLayoutSec.Visible = False
    RimBottom = 5
    RimTop = 5
    RimSide = 5
    ScaleBkVisible = False
    ScaleVisible = True
    Value = 0.8
  end
  object Label3: TLabel
    Left = 344
    Top = 68
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Color of meter background'
  end
  object Label4: TLabel
    Left = 344
    Top = 116
    Width = 145
    Height = 16
    AutoSize = False
    Caption = 'Color of meter cover'
  end
  object Label1: TLabel
    Left = 344
    Top = 164
    Width = 153
    Height = 15
    AutoSize = False
    Caption = 'Color of meter scale'
  end
  object Label2: TLabel
    Left = 344
    Top = 212
    Width = 161
    Height = 16
    AutoSize = False
    Caption = 'Color of meter inscription'
  end
  object SBColBak: TSpeedButton
    Left = 480
    Top = 88
    Width = 25
    Height = 22
    Caption = '...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    Layout = blGlyphBottom
    Margin = 4
    ParentFont = False
    OnClick = SBColBakClick
  end
  object Label5: TLabel
    Left = 488
    Top = 268
    Width = 105
    Height = 16
    AutoSize = False
    Caption = 'Meter Units ID'
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 697
    Height = 49
    Align = alTop
    TabOrder = 0
    object SBExit: TSpeedButton
      Left = 8
      Top = 6
      Width = 81
      Height = 35
      Caption = 'Exit'
      Glyph.Data = {
        72010000424D7201000000000000760000002800000015000000150000000100
        040000000000FC00000000000000000000001000000000000000000000000000
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
      OnClick = SBExitClick
    end
    object NumLab1: TNumLab
      Left = 604
      Top = 5
      Width = 89
      Height = 36
      Alignment = taCenter
      ColorLabBakG = clBtnFace
      ColorLabText = clBlack
      ColorOutBakG = clBtnFace
      ColorOutText = clBlack
      ColorScheme = csBWG
      Comma = False
      DisplayType = dtFixP
      DTFormat = 'mmm-dd, yyyy'
      Empty = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -20
      Font.Name = 'Arial'
      Font.Style = []
      ForcePlusSign = False
      FrameStyle = fsRaised
      LabelWidth = 80
      LeftSpace = 2
      LeftText = 'X:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentFont = False
      Precision = 2
      RightTextAlignment = taLeftJustify
      StateText = 'undefined'
    end
    object Label8: TLabel
      Left = 520
      Top = 17
      Width = 81
      Height = 16
      Alignment = taCenter
      AutoSize = False
      Caption = 'Meter Value'
    end
    object Label11: TLabel
      Left = 304
      Top = 5
      Width = 77
      Height = 16
      Caption = 'Main Needle'
    end
    object LblSecNeedle: TLabel
      Left = 304
      Top = 25
      Width = 114
      Height = 16
      Caption = 'Secondary Needle'
    end
    object SBValue: TScrollBar
      Left = 96
      Top = 5
      Width = 201
      Height = 17
      Max = 150
      Min = -20
      PageSize = 0
      TabOrder = 0
      OnChange = SBValueChange
    end
    object SBarValue2: TScrollBar
      Left = 96
      Top = 25
      Width = 201
      Height = 17
      Max = 150
      Min = -20
      PageSize = 0
      Position = 40
      TabOrder = 1
      OnChange = SBarValue2Change
    end
  end
  object CSMeterBkgnd: TColSel
    Left = 344
    Top = 88
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clNavy
    TabOrder = 1
    OnChange = CSMeterBkgndChange
  end
  object CSColorCover: TColSel
    Left = 344
    Top = 136
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clSilver
    TabOrder = 2
    OnChange = CSColorCoverChange
  end
  object CSColorScale: TColSel
    Left = 344
    Top = 184
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clSilver
    TabOrder = 3
    OnChange = CSColorScaleChange
  end
  object CSColorText: TColSel
    Left = 344
    Top = 232
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clSilver
    TabOrder = 4
    OnChange = CSColorTextChange
  end
  object GroupBox2: TGroupBox
    Left = 512
    Top = 80
    Width = 73
    Height = 177
    Caption = ' Range '
    TabOrder = 5
    object Label6: TLabel
      Left = 8
      Top = 20
      Width = 24
      Height = 16
      Caption = 'Low'
    end
    object Label7: TLabel
      Left = 40
      Top = 20
      Width = 28
      Height = 16
      Caption = 'High'
    end
    object SBMaxVal: TScrollBar
      Left = 47
      Top = 40
      Width = 14
      Height = 129
      Kind = sbVertical
      Min = 10
      PageSize = 0
      Position = 90
      TabOrder = 0
      OnChange = SBMaxValChange
    end
    object SBMinVal: TScrollBar
      Left = 11
      Top = 40
      Width = 14
      Height = 129
      Kind = sbVertical
      PageSize = 0
      TabOrder = 1
      OnChange = SBMinValChange
    end
  end
  object GroupBox1: TGroupBox
    Left = 344
    Top = 264
    Width = 129
    Height = 129
    Caption = 'Frame Style'
    TabOrder = 6
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
      Left = 8
      Top = 72
      Width = 105
      Height = 17
      Caption = 'Engraved'
      TabOrder = 3
      OnClick = RBEngravedClick
    end
    object RBSimple: TRadioButton
      Left = 8
      Top = 88
      Width = 89
      Height = 17
      Caption = 'Simple'
      TabOrder = 4
      OnClick = RBSimpleClick
    end
    object RBNone: TRadioButton
      Left = 8
      Top = 104
      Width = 81
      Height = 17
      Caption = 'None'
      TabOrder = 5
      OnClick = RBNoneClick
    end
  end
  object EdCaption: TEdit
    Left = 488
    Top = 284
    Width = 97
    Height = 24
    MaxLength = 10
    TabOrder = 7
    Text = 'Left'
    OnChange = EdCaptionChange
  end
  object CBShortTicks: TCheckBox
    Left = 488
    Top = 312
    Width = 97
    Height = 17
    Caption = 'ShortTicks'
    TabOrder = 8
    OnClick = CBShortTicksClick
  end
  object CBScaleLine: TCheckBox
    Left = 488
    Top = 328
    Width = 97
    Height = 17
    Caption = 'ScaleLine'
    TabOrder = 9
    OnClick = CBScaleLineClick
  end
  object CBLimHigh: TCheckBox
    Left = 488
    Top = 360
    Width = 97
    Height = 17
    Caption = 'LimHigh'
    Checked = True
    State = cbChecked
    TabOrder = 10
    OnClick = CBLimHighClick
  end
  object CBLimLow: TCheckBox
    Left = 488
    Top = 376
    Width = 97
    Height = 17
    Caption = 'LimLow'
    TabOrder = 11
    OnClick = CBLimLowClick
  end
  object BButNeedleLayout: TBitBtn
    Left = 8
    Top = 336
    Width = 161
    Height = 33
    Caption = 'Needle Layout'
    TabOrder = 12
    OnClick = BButNeedleLayoutClick
  end
  object GroupBox3: TGroupBox
    Left = 600
    Top = 80
    Width = 89
    Height = 177
    Caption = ' Thresholds '
    TabOrder = 13
    object Label9: TLabel
      Left = 16
      Top = 20
      Width = 24
      Height = 16
      Caption = 'Low'
    end
    object Label10: TLabel
      Left = 48
      Top = 20
      Width = 28
      Height = 16
      Caption = 'High'
    end
    object SBThreshHigh: TScrollBar
      Left = 56
      Top = 40
      Width = 13
      Height = 129
      Kind = sbVertical
      PageSize = 0
      Position = 13
      TabOrder = 0
      OnChange = SBThreshHighChange
    end
    object SBThreshLow: TScrollBar
      Left = 20
      Top = 40
      Width = 13
      Height = 129
      Kind = sbVertical
      PageSize = 0
      Position = 33
      TabOrder = 1
      OnChange = SBThreshLowChange
    end
  end
  object CBVisThresh: TCheckBox
    Left = 488
    Top = 344
    Width = 97
    Height = 17
    Caption = 'Thresholds'
    Checked = True
    State = cbChecked
    TabOrder = 14
    OnClick = CBVisThreshClick
  end
  object RGLayout: TRadioGroup
    Left = 600
    Top = 264
    Width = 89
    Height = 129
    Caption = ' Layout '
    ItemIndex = 0
    Items.Strings = (
      '90'#176
      '120'#176
      '180'#176
      '270'#176
      '300'#176
      '360'#176)
    TabOrder = 15
    OnClick = RGLayoutClick
  end
  object BButNeedle2Layout: TBitBtn
    Left = 8
    Top = 376
    Width = 161
    Height = 33
    Caption = 'Secondary Needle Layout'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 16
    OnClick = BButNeedle2LayoutClick
  end
  object SBAnchorSize: TScrollBar
    Left = 8
    Top = 312
    Width = 185
    Height = 17
    Max = 40
    PageSize = 0
    Position = 24
    TabOrder = 17
    OnChange = SBAnchorSizeChange
  end
  object CBAnchorOn: TCheckBox
    Left = 200
    Top = 312
    Width = 137
    Height = 17
    Caption = 'Anchor covered'
    Checked = True
    State = cbChecked
    TabOrder = 18
    OnClick = CBAnchorOnClick
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 552
    Top = 8
  end
end
