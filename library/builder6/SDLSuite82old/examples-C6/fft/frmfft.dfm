object Form1: TForm1
  Left = 331
  Top = 220
  Width = 615
  Height = 526
  Caption = 'FFT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Scaled = False
  OnActivate = FormActivate
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 17
    Top = 8
    Width = 36
    Height = 16
    Caption = 'Noise'
  end
  object Label2: TLabel
    Left = 72
    Top = 8
    Width = 31
    Height = 16
    Caption = 'Freq.'
  end
  object Label3: TLabel
    Left = 8
    Top = 224
    Width = 111
    Height = 16
    Caption = 'Weighting Window'
  end
  object RChart2: TRChart
    Left = 152
    Top = 249
    Width = 441
    Height = 240
    AllocSize = 1000
    AutoRedraw = True
    LRim = 60
    RRim = 20
    TRim = 20
    BRim = 40
    BackGroundImg.IncludePath = False
    BackGroundImg.FillMode = bfStretch
    ClassDefault = 0
    GridStyle = gsDotLines
    Isometric = False
    GridColor = clSilver
    JointLayers.L01xControlledBy = 1
    JointLayers.L01yControlledBy = 1
    JointLayers.L02xControlledBy = 2
    JointLayers.L02yControlledBy = 2
    Caption = 'Magnitude spectrum of signal above'
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
    MouseAction = maNone
    MouseCursorFixed = True
    Scale1X.CaptionPosX = 0
    Scale1X.CaptionPosY = 22
    Scale1X.CaptionAlignment = taCenter
    Scale1X.CaptionAnchor = uaSclCenter
    Scale1X.ColorScale = clBlack
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
    Scale1X.RangeHigh = 200
    Scale1X.ShortTicks = False
    Scale1X.ScalePos = 0
    Scale1X.Visible = True
    Scale1X.ScaleLocation = slBottom
    Scale1Y.CaptionPosX = 0
    Scale1Y.CaptionPosY = -16
    Scale1Y.CaptionAlignment = taLeftJustify
    Scale1Y.CaptionAnchor = uaSclTopLft
    Scale1Y.ColorScale = clBlack
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
    Scale1Y.RangeHigh = 10
    Scale1Y.ShortTicks = False
    Scale1Y.ScalePos = 0
    Scale1Y.Visible = True
    Scale1Y.ScaleLocation = slLeft
    Scale2X.CaptionPosX = 10
    Scale2X.CaptionPosY = 100
    Scale2X.CaptionAlignment = taCenter
    Scale2X.CaptionAnchor = uaSclCenter
    Scale2X.ColorScale = clMaroon
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
    Scale2X.RangeHigh = 1
    Scale2X.ShortTicks = True
    Scale2X.ScalePos = 0
    Scale2X.Visible = False
    Scale2X.ScaleLocation = slBottom
    Scale2Y.CaptionPosX = 10
    Scale2Y.CaptionPosY = 100
    Scale2Y.CaptionAlignment = taRightJustify
    Scale2Y.CaptionAnchor = uaSclTopLft
    Scale2Y.ColorScale = clMaroon
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
    Scale2Y.RangeHigh = 1
    Scale2Y.ShortTicks = True
    Scale2Y.ScalePos = 0
    Scale2Y.Visible = False
    Scale2Y.ScaleLocation = slLeft
    ShadowStyle = ssFlying
    ShadowColor = clGray
    ShadowBakColor = clSilver
    TextFontStyle = []
    TextBkStyle = tbClear
    TextBkColor = clWhite
    TextAlignment = taCenter
  end
  object RChart1: TRChart
    Left = 152
    Top = 1
    Width = 441
    Height = 240
    AllocSize = 1000
    AutoRedraw = False
    LRim = 60
    RRim = 20
    TRim = 20
    BRim = 40
    BackGroundImg.IncludePath = False
    BackGroundImg.FillMode = bfStretch
    ClassDefault = 0
    GridStyle = gsDotLines
    Isometric = False
    GridColor = clSilver
    JointLayers.L01xControlledBy = 1
    JointLayers.L01yControlledBy = 1
    JointLayers.L02xControlledBy = 2
    JointLayers.L02yControlledBy = 2
    Caption = 'Signal to be analysed'
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
    MouseAction = maNone
    MouseCursorFixed = True
    Scale1X.CaptionPosX = 0
    Scale1X.CaptionPosY = 22
    Scale1X.CaptionAlignment = taCenter
    Scale1X.CaptionAnchor = uaSclCenter
    Scale1X.ColorScale = clBlack
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
    Scale1X.RangeHigh = 500
    Scale1X.ShortTicks = False
    Scale1X.ScalePos = 0
    Scale1X.Visible = True
    Scale1X.ScaleLocation = slBottom
    Scale1Y.CaptionPosX = 0
    Scale1Y.CaptionPosY = -16
    Scale1Y.CaptionAlignment = taLeftJustify
    Scale1Y.CaptionAnchor = uaSclTopLft
    Scale1Y.ColorScale = clBlack
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
    Scale1Y.RangeLow = -40
    Scale1Y.RangeHigh = 40
    Scale1Y.ShortTicks = False
    Scale1Y.ScalePos = 0
    Scale1Y.Visible = True
    Scale1Y.ScaleLocation = slLeft
    Scale2X.CaptionPosX = 10
    Scale2X.CaptionPosY = 100
    Scale2X.CaptionAlignment = taCenter
    Scale2X.CaptionAnchor = uaSclCenter
    Scale2X.ColorScale = clMaroon
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
    Scale2X.RangeHigh = 1
    Scale2X.ShortTicks = True
    Scale2X.ScalePos = 0
    Scale2X.Visible = False
    Scale2X.ScaleLocation = slBottom
    Scale2Y.CaptionPosX = 10
    Scale2Y.CaptionPosY = 100
    Scale2Y.CaptionAlignment = taRightJustify
    Scale2Y.CaptionAnchor = uaSclTopLft
    Scale2Y.ColorScale = clMaroon
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
    Scale2Y.RangeHigh = 1
    Scale2Y.ShortTicks = True
    Scale2Y.ScalePos = 0
    Scale2Y.Visible = False
    Scale2Y.ScaleLocation = slLeft
    ShadowStyle = ssFlying
    ShadowColor = clGray
    ShadowBakColor = clSilver
    TextFontStyle = []
    TextBkStyle = tbClear
    TextBkColor = clWhite
    TextAlignment = taCenter
  end
  object SBFreq1: TScrollBar
    Left = 81
    Top = 33
    Width = 15
    Height = 152
    Kind = sbVertical
    PageSize = 0
    Position = 100
    TabOrder = 0
    OnChange = SBFreq1Change
  end
  object ScrollBar1: TScrollBar
    Left = 24
    Top = 33
    Width = 15
    Height = 152
    Kind = sbVertical
    PageSize = 0
    Position = 100
    TabOrder = 1
    OnChange = ScrollBar1Change
  end
  object CBoxWind: TComboBox
    Left = 8
    Top = 248
    Width = 137
    Height = 24
    Style = csDropDownList
    ItemHeight = 16
    Sorted = True
    TabOrder = 2
    OnChange = CBoxWindChange
    Items.Strings = (
      'Blackman'
      'cos2'
      'Gaussian'
      'Hamming'
      'Rectangle'
      'Triangle')
  end
  object CBLogY: TCheckBox
    Left = 8
    Top = 200
    Width = 89
    Height = 17
    Caption = 'log. y axis'
    TabOrder = 3
    OnClick = CBLogYClick
  end
  object BButExit: TBitBtn
    Left = 8
    Top = 448
    Width = 105
    Height = 33
    Caption = 'Exit'
    TabOrder = 4
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
  object RGSpecType: TRadioGroup
    Left = 8
    Top = 280
    Width = 137
    Height = 153
    Caption = ' Spectrum Type '
    ItemIndex = 0
    Items.Strings = (
      'Magnitude'
      'Power Spectrum'
      'Phase Angle'
      'Cosine Terms'
      'Sine Terms'
      'Real Spec'
      'Imag Spec')
    TabOrder = 5
    OnClick = RGSpecTypeClick
  end
  object FFT1: TFastFourier
    SpectrumSize = 512
    WeightingWindow = fwRectangle
    Left = 48
    Top = 128
  end
end
