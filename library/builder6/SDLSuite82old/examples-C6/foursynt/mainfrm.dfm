object Form1: TForm1
  Left = 295
  Top = 197
  Width = 663
  Height = 476
  Caption = 'Fourier Synthesis by Inverse FFT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 12
    Top = 144
    Width = 181
    Height = 16
    AutoSize = False
    Caption = 'x0    x1    x2   x3   x4    x5   x6    x7'
  end
  object RChart1: TRChart
    Left = 208
    Top = 16
    Width = 441
    Height = 421
    AllocSize = 1000
    AutoRedraw = True
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
    MouseAction = maZoomDrag
    MouseCursorFixed = False
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
    Scale1Y.RangeLow = -5
    Scale1Y.RangeHigh = 5
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
    ShadowWidth = 10
    ShadowStyle = ssFlying
    ShadowColor = clGray
    ShadowBakColor = clBtnFace
    TextFontStyle = []
    TextBkStyle = tbClear
    TextBkColor = clWhite
    TextAlignment = taCenter
  end
  object ScrollBar1: TScrollBar
    Left = 12
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 0
    OnChange = ScrollBar1Change
  end
  object ScrollBar2: TScrollBar
    Left = 35
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 1
    OnChange = ScrollBar1Change
  end
  object ScrollBar3: TScrollBar
    Left = 59
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 2
    OnChange = ScrollBar1Change
  end
  object ScrollBar4: TScrollBar
    Left = 82
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 3
    OnChange = ScrollBar1Change
  end
  object ScrollBar5: TScrollBar
    Left = 106
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 4
    OnChange = ScrollBar1Change
  end
  object ScrollBar6: TScrollBar
    Left = 129
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 5
    OnChange = ScrollBar1Change
  end
  object ScrollBar7: TScrollBar
    Left = 153
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 6
    OnChange = ScrollBar1Change
  end
  object ScrollBar8: TScrollBar
    Left = 176
    Top = 10
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 7
    OnChange = ScrollBar1Change
  end
  object ScrollBar10: TScrollBar
    Left = 35
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 8
    OnChange = ScrollBar1Change
  end
  object ScrollBar11: TScrollBar
    Left = 59
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 9
    OnChange = ScrollBar1Change
  end
  object ScrollBar12: TScrollBar
    Left = 82
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 10
    OnChange = ScrollBar1Change
  end
  object ScrollBar13: TScrollBar
    Left = 106
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 11
    OnChange = ScrollBar1Change
  end
  object ScrollBar14: TScrollBar
    Left = 129
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 12
    OnChange = ScrollBar1Change
  end
  object ScrollBar15: TScrollBar
    Left = 153
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 13
    OnChange = ScrollBar1Change
  end
  object ScrollBar16: TScrollBar
    Left = 176
    Top = 170
    Width = 13
    Height = 121
    Kind = sbVertical
    Min = -100
    PageSize = 0
    TabOrder = 14
    OnChange = ScrollBar1Change
  end
  object BButSquare: TBitBtn
    Left = 12
    Top = 312
    Width = 89
    Height = 28
    Caption = 'Square'
    TabOrder = 15
    OnClick = BButSquareClick
  end
  object BButHalfSine: TBitBtn
    Left = 104
    Top = 312
    Width = 89
    Height = 28
    Caption = 'Half Sine'
    TabOrder = 16
    OnClick = BButHalfSineClick
  end
  object BButTriangle: TBitBtn
    Left = 104
    Top = 344
    Width = 89
    Height = 28
    Caption = 'Triangle'
    TabOrder = 17
    OnClick = BButTriangleClick
  end
  object BButSaw: TBitBtn
    Left = 12
    Top = 344
    Width = 89
    Height = 28
    Caption = 'Saw Tooth'
    TabOrder = 18
    OnClick = BButSawClick
  end
  object BButExit: TBitBtn
    Left = 12
    Top = 392
    Width = 89
    Height = 28
    Caption = 'Exit'
    TabOrder = 19
    OnClick = BButExitClick
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
  end
  object BButReset: TBitBtn
    Left = 104
    Top = 392
    Width = 89
    Height = 28
    Caption = 'Reset'
    TabOrder = 20
    OnClick = BButResetClick
  end
  object FastFourier1: TFastFourier
    SpectrumSize = 256
    WeightingWindow = fwTriangle
    Left = 616
    Top = 416
  end
end