object Form1: TForm1
  Left = 320
  Top = 239
  Width = 773
  Height = 730
  Caption = 'Dual RChart Layers'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object RC1: TRChart
    Left = 0
    Top = 121
    Width = 765
    Height = 581
    Align = alClient
    AllocSize = 1000
    AutoRedraw = True
    LRim = 100
    RRim = 20
    TRim = 24
    BRim = 70
    BackGroundImg.IncludePath = False
    BackGroundImg.FillMode = bfStretch
    ClassDefault = 0
    GridStyle = gsNone
    Isometric = False
    GridColor = clMoneyGreen
    JointLayers.L01xControlledBy = 1
    JointLayers.L01yControlledBy = 1
    JointLayers.L02xControlledBy = 2
    JointLayers.L02yControlledBy = 2
    CaptionPosX = 0
    CaptionPosY = -16
    CaptionAlignment = taRightJustify
    CaptionAnchorHoriz = cahChartRight
    CaptionAnchorVert = cavChartTop
    CrossHair1.Color = clBlack
    CrossHair1.Layer = 1
    CrossHair1.Mode = chOff
    CrossHair1.LineType = psSolid
    CrossHair1.LineWid = 1
    CrossHair2.Color = clBlack
    CrossHair2.Layer = 2
    CrossHair2.Mode = chOff
    CrossHair2.LineType = psSolid
    CrossHair2.LineWid = 1
    CrossHair3.Color = clBlack
    CrossHair3.Layer = 3
    CrossHair3.Mode = chOff
    CrossHair3.LineType = psSolid
    CrossHair3.LineWid = 1
    CrossHair4.Color = clBlack
    CrossHair4.Layer = 4
    CrossHair4.Mode = chOff
    CrossHair4.LineType = psSolid
    CrossHair4.LineWid = 1
    MouseAction = maPan
    MouseCursorFixed = True
    Scale1X.CaptionPosX = -20
    Scale1X.CaptionPosY = 7
    Scale1X.CaptionAlignment = taRightJustify
    Scale1X.CaptionAnchor = uaSclTopLft
    Scale1X.ColorScale = clNavy
    Scale1X.DateFormat.TimeFormat = tfHHMMSS
    Scale1X.DateFormat.DateSeparator = '-'
    Scale1X.DateFormat.TimeSeparator = ':'
    Scale1X.DateFormat.YearLength = ylYYYY
    Scale1X.DateFormat.MonthName = True
    Scale1X.DateFormat.DateOrder = doDDMMYY
    Scale1X.DateFormat.DateForTime = dtOnePerDay
    Scale1X.DecPlaces = -2
    Scale1X.Font.Charset = DEFAULT_CHARSET
    Scale1X.Font.Color = clWindowText
    Scale1X.Font.Height = -13
    Scale1X.Font.Name = 'MS Sans Serif'
    Scale1X.Font.Style = []
    Scale1X.Logarithmic = False
    Scale1X.LabelType = ftNum
    Scale1X.MinTicks = 3
    Scale1X.MinRange = 1E-10
    Scale1X.RangeHigh = 100
    Scale1X.ShortTicks = False
    Scale1X.ScalePos = 0
    Scale1X.Visible = True
    Scale1X.ScaleLocation = slBottom
    Scale1Y.CaptionPosX = 0
    Scale1Y.CaptionPosY = -23
    Scale1Y.CaptionAlignment = taRightJustify
    Scale1Y.CaptionAnchor = uaSclTopLft
    Scale1Y.ColorScale = clNavy
    Scale1Y.DateFormat.TimeFormat = tfHHMMSS
    Scale1Y.DateFormat.DateSeparator = '-'
    Scale1Y.DateFormat.TimeSeparator = ':'
    Scale1Y.DateFormat.YearLength = ylYYYY
    Scale1Y.DateFormat.MonthName = True
    Scale1Y.DateFormat.DateOrder = doDDMMYY
    Scale1Y.DateFormat.DateForTime = dtOnePerDay
    Scale1Y.DecPlaces = -2
    Scale1Y.Font.Charset = DEFAULT_CHARSET
    Scale1Y.Font.Color = clWindowText
    Scale1Y.Font.Height = -13
    Scale1Y.Font.Name = 'MS Sans Serif'
    Scale1Y.Font.Style = []
    Scale1Y.Logarithmic = False
    Scale1Y.LabelType = ftNum
    Scale1Y.MinTicks = 3
    Scale1Y.MinRange = 1E-10
    Scale1Y.RangeLow = -100
    Scale1Y.RangeHigh = 100
    Scale1Y.ShortTicks = False
    Scale1Y.ScalePos = 0
    Scale1Y.Visible = True
    Scale1Y.ScaleLocation = slLeft
    Scale2X.CaptionPosX = -20
    Scale2X.CaptionPosY = 7
    Scale2X.CaptionAlignment = taRightJustify
    Scale2X.CaptionAnchor = uaSclTopLft
    Scale2X.ColorScale = 225
    Scale2X.DateFormat.TimeFormat = tfHHMMSS
    Scale2X.DateFormat.DateSeparator = '-'
    Scale2X.DateFormat.TimeSeparator = ':'
    Scale2X.DateFormat.YearLength = ylYYYY
    Scale2X.DateFormat.MonthName = True
    Scale2X.DateFormat.DateOrder = doDDMMYY
    Scale2X.DateFormat.DateForTime = dtOnePerDay
    Scale2X.DecPlaces = -2
    Scale2X.Font.Charset = DEFAULT_CHARSET
    Scale2X.Font.Color = clWindowText
    Scale2X.Font.Height = -13
    Scale2X.Font.Name = 'MS Sans Serif'
    Scale2X.Font.Style = []
    Scale2X.Logarithmic = False
    Scale2X.LabelType = ftNum
    Scale2X.MinTicks = 3
    Scale2X.MinRange = 1E-10
    Scale2X.RangeLow = -1.5
    Scale2X.RangeHigh = 1.5
    Scale2X.ShortTicks = True
    Scale2X.ScalePos = 30
    Scale2X.Visible = True
    Scale2X.ScaleLocation = slBottom
    Scale2Y.CaptionPosX = 0
    Scale2Y.CaptionPosY = -23
    Scale2Y.CaptionAlignment = taRightJustify
    Scale2Y.CaptionAnchor = uaSclTopLft
    Scale2Y.ColorScale = 225
    Scale2Y.DateFormat.TimeFormat = tfHHMMSS
    Scale2Y.DateFormat.DateSeparator = '-'
    Scale2Y.DateFormat.TimeSeparator = ':'
    Scale2Y.DateFormat.YearLength = ylYYYY
    Scale2Y.DateFormat.MonthName = True
    Scale2Y.DateFormat.DateOrder = doDDMMYY
    Scale2Y.DateFormat.DateForTime = dtOnePerDay
    Scale2Y.DecPlaces = -2
    Scale2Y.Font.Charset = DEFAULT_CHARSET
    Scale2Y.Font.Color = clWindowText
    Scale2Y.Font.Height = -13
    Scale2Y.Font.Name = 'MS Sans Serif'
    Scale2Y.Font.Style = []
    Scale2Y.Logarithmic = False
    Scale2Y.LabelType = ftNum
    Scale2Y.MinTicks = 3
    Scale2Y.MinRange = 1E-10
    Scale2Y.RangeLow = -1.5
    Scale2Y.RangeHigh = 1.5
    Scale2Y.ShortTicks = True
    Scale2Y.ScalePos = 50
    Scale2Y.Visible = True
    Scale2Y.ScaleLocation = slLeft
    ShadowStyle = ssFlying
    ShadowColor = clGrayText
    ShadowBakColor = clBtnFace
    TextFontStyle = []
    TextBkStyle = tbClear
    TextBkColor = clWhite
    TextAlignment = taCenter
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 765
    Height = 121
    Align = alTop
    BevelOuter = bvLowered
    TabOrder = 0
    object BButExit: TBitBtn
      Left = 8
      Top = 8
      Width = 97
      Height = 33
      Caption = 'Exit'
      TabOrder = 0
      OnClick = BButExitClick
      Glyph.Data = {
        76050000424D7605000000000000360000002800000015000000150000000100
        1800000000004005000000000000000000000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        6331186331186331186331186331186331186331186331186331186331186331
        18633118000000000000000000C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDAD6331
        18000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDAD6331180000
        00000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDAD6331
        18000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        AD633118000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDAD633118000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDAD633118000000C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDAD633118000000C0C0C0C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADCEBDADF7E7D6CEBDADCEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDADCEBDAD633118000000C0C0C0C0C0C000C0C0C0000000
        CEBDADCEBDADF7E7D6F7E7D6F7E7D6CEBDADCEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDADCEBDADCEBDAD633118000000C0C0C000C0C0C0000000
        CEBDADF7E7D6000000000000F7E7D6F7E7D6CEBDADCEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDADCEBDADCEBDAD00000000000000000000C0C0C0000000
        F7E7D6000000000000000000000000F7E7D6F7E7D6CEBDADCEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDADCEBDAD000000000000000000C0C0C000C0C0C0000000
        000000000000000000C0C0C0C0C0C0000000F7E7D6F7E7D6CEBDADCEBDADCEBD
        ADCEBDADCEBDADCEBDAD000000000000000000C0C0C0C0C0C000C0C0C0000000
        000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000F7E7D6F7E7D6CEBDADCEBD
        ADCEBDADCEBDAD000000000000000000C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000F7E7D6F7E7D6CEBD
        ADCEBDAD000000000000000000C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000F7E7D6F7E7
        D6000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000F7E7
        D6000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
        00000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000}
    end
    object CBoxMouseAffectsLayer1: TCheckBox
      Left = 120
      Top = 16
      Width = 169
      Height = 17
      Caption = 'Mouse affects layer 1'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = CBoxMouseAffectsLayer1Click
    end
    object CBoxMouseAffectsLayer2: TCheckBox
      Left = 120
      Top = 40
      Width = 169
      Height = 17
      Caption = 'Mouse affects layer 2'
      TabOrder = 2
      OnClick = CBoxMouseAffectsLayer2Click
    end
    object RGLayout: TRadioGroup
      Left = 312
      Top = 32
      Width = 345
      Height = 81
      Caption = ' Layout of Axes '
      ItemIndex = 0
      Items.Strings = (
        'Both axes left and bottom'
        'Y axes left and right, X1 axis bottom, X2 axis invisible'
        'Y axes left and right, X axes top and bottom')
      TabOrder = 3
      OnClick = RGLayoutClick
    end
    object RGMouseAction: TRadioGroup
      Left = 120
      Top = 64
      Width = 177
      Height = 49
      Caption = ' Mouse Action '
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        'Pan'
        'Zoom')
      TabOrder = 4
      OnClick = RGMouseActionClick
    end
    object BButZoom11: TBitBtn
      Left = 8
      Top = 80
      Width = 97
      Height = 33
      Caption = 'Reset Zoom'
      TabOrder = 5
      OnClick = BButZoom11Click
    end
    object RGGrid: TRadioGroup
      Left = 664
      Top = 32
      Width = 89
      Height = 81
      Caption = ' Grid '
      ItemIndex = 0
      Items.Strings = (
        'None'
        'Layer 1'
        'Layer 2')
      TabOrder = 6
      OnClick = RGGridClick
    end
  end
end
