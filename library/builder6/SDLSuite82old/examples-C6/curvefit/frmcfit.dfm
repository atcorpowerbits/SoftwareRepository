object Form1: TForm1
  Left = 321
  Top = 249
  Width = 755
  Height = 587
  Caption = 'Curve fitting using the class TCurveFit'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Scaled = False
  OnClose = FormClose
  OnMouseMove = FormMouseMove
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object RChart1: TRChart
    Left = 0
    Top = 41
    Width = 611
    Height = 518
    Align = alClient
    ShowHint = True
    AllocSize = 1000
    AutoRedraw = True
    RRim = 16
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
    MouseAction = maNone
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
    Scale1X.RangeHigh = 1
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
    Scale1Y.RangeHigh = 1
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
    OnMouseDown = RChart1MouseDown
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 747
    Height = 41
    Align = alTop
    TabOrder = 0
    object SBNewPnts: TSpeedButton
      Left = 40
      Top = 6
      Width = 29
      Height = 29
      Hint = 'Enter data points'
      AllowAllUp = True
      GroupIndex = 99
      Glyph.Data = {
        72010000424D7201000000000000760000002800000015000000150000000100
        040000000000FC00000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        88888888843B8888888888888888888885378888888888888888008889018888
        888888888880000888EE888888888888880E000883EE88888888888880E00088
        80338888888888880E00088881DC888888888880E000888886C4888888888800
        0008888880008888888880000088888880008888888800000888888884508888
        8880E0008888888880208888880E0008888888888201888880E0008888888888
        8920888800000888888888888199888030008888888888888FFF888003088888
        888888888BB8880300888888888888888FF6880088888888888888888D718088
        88888888888888888EEE888888888888888888888011}
      ParentShowHint = False
      ShowHint = True
      OnClick = SBNewPntsClick
    end
    object NLabFitQual: TNumLab
      Left = 592
      Top = 8
      Width = 145
      Height = 22
      Alignment = taCenter
      ColorLabBakG = clSilver
      ColorLabText = clBlack
      ColorOutBakG = clBtnFace
      ColorOutText = clNavy
      ColorScheme = csBWG
      Comma = False
      DisplayType = dtFixP
      DTFormat = 'mmm-dd, yyyy'
      Empty = False
      ForcePlusSign = False
      FrameStyle = fsLowered
      LabelWidth = 60
      LeftSpace = 80
      LeftText = 'quality of fit:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 4
      RightTextAlignment = taLeftJustify
      ShowHint = True
      StateText = 'undefined'
    end
    object SBClear: TSpeedButton
      Left = 8
      Top = 6
      Width = 29
      Height = 29
      Hint = 'Clear all data'
      Glyph.Data = {
        2E060000424D2E06000000000000360400002800000015000000150000000100
        080000000000F801000000000000000000000001000000010000000000000000
        80000080000000808000800000008000800080800000C0C0C000688DA200BBCC
        D500000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000DDE6EA00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00070707070707
        07070707070707070707070707070762656E0707070707070707070707070707
        0707070707070761726207070707070707070707070707070707070707070742
        6974070707F907070707070707070707070707F907070707070707070707F907
        07070707070707070707F9F9F907070000000707070707F90707070707070707
        07F9F9F9F907074804000707070707F9F907070707070707F9F9F9F907070700
        0000070707070707F9F90707070707F9F9F90707070707000000070707070707
        07F9F9070707F9F9F9070707070707F9F9F90707070707070707F9F907F9F907
        07070707070707000000070707070707070707F9F9F907070707070707070700
        00000707070707070707F9F9F9F9F90707070707070707000000070707070707
        F9F9F90707F9F9F9070707070707070000000707070707F9F90707070707F9F9
        F907070707070700000007070707F9F907070707070707F9F9F9F90707070700
        0000070707F907070707070707070707F9F9F9F9F90707000000070707070707
        070707070707070707F9F9F90707070000000707070707070707070707070707
        0707070707070700000007070707070707070707070707070707070707070700
        0000070707070707070707070707070707070707070707000000070707070707
        070707070707070707070707070707736B35}
      ParentShowHint = False
      ShowHint = True
      OnClick = SBClearClick
    end
    object LblFormula: TLabel
      Left = 96
      Top = 3
      Width = 353
      Height = 17
      AutoSize = False
      Caption = 'y = kx + d'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object LblParams: TLabel
      Left = 96
      Top = 22
      Width = 361
      Height = 16
      AutoSize = False
      Caption = '<---- click here to enter data'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel2: TPanel
    Left = 611
    Top = 41
    Width = 136
    Height = 518
    Align = alRight
    TabOrder = 1
    object LblPolyOrder: TLabel
      Left = 8
      Top = 131
      Width = 41
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'order:'
      Enabled = False
    end
    object BButSpline: TSpeedButton
      Left = 8
      Top = 328
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Smoothed Spline'
      OnClick = BButSplineClick
    end
    object LblSmoothSpline: TLabel
      Left = 8
      Top = 364
      Width = 105
      Height = 16
      Caption = 'Smoothing Factor'
      Enabled = False
    end
    object BButParabolFit: TSpeedButton
      Left = 8
      Top = 52
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Parabolic'
      OnClick = BButParabolFitClick
    end
    object BButCalcReciprLine: TSpeedButton
      Left = 8
      Top = 164
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Reciprocal'
      NumGlyphs = 2
      OnClick = BButCalcReciprLineClick
    end
    object BButHyper: TSpeedButton
      Left = 8
      Top = 204
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Hyperbolic'
      OnClick = BButHyperClick
    end
    object BButLogFit: TSpeedButton
      Left = 8
      Top = 244
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Logarithmic'
      OnClick = BButLogFitClick
    end
    object BButGaussFit: TSpeedButton
      Left = 8
      Top = 284
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Gaussian'
      OnClick = BButGaussFitClick
    end
    object BButLinFit: TSpeedButton
      Left = 8
      Top = 12
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Linear'
      OnClick = BButLinFitClick
    end
    object BButPolynomial: TSpeedButton
      Left = 8
      Top = 92
      Width = 121
      Height = 33
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Polynomial'
      OnClick = BButPolynomialClick
    end
    object BButExit: TBitBtn
      Left = 8
      Top = 476
      Width = 121
      Height = 33
      Caption = 'Exit'
      TabOrder = 0
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
    object SEPolyOrder: TCSpinEdit
      Left = 56
      Top = 128
      Width = 41
      Height = 26
      MaxValue = 8
      MinValue = 1
      TabOrder = 1
      Value = 4
      OnChange = BButPolynomialClick
    end
    object SBarSmoothSpline: TScrollBar
      Left = 8
      Top = 384
      Width = 121
      Height = 20
      Enabled = False
      Max = 1000
      PageSize = 0
      TabOrder = 2
      OnChange = SBarSmoothSplineChange
    end
  end
  object Stats1: TCurveFit
    Left = 64
    Top = 72
  end
end
