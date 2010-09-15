object FrmSom: TFrmSom
  Left = 584
  Top = 329
  Width = 543
  Height = 610
  Caption = 'FrmSom'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object NoteBk: TTabbedNotebook
    Left = 0
    Top = 105
    Width = 535
    Height = 477
    Align = alClient
    PageIndex = 1
    TabFont.Charset = DEFAULT_CHARSET
    TabFont.Color = clBtnText
    TabFont.Height = -13
    TabFont.Name = 'MS Sans Serif'
    TabFont.Style = []
    TabOrder = 0
    object TTabPage
      Left = 4
      Top = 27
      Caption = 'Data Matrix'
      object TEData: TNTabEd
        Left = 0
        Top = 0
        Width = 527
        Height = 446
        Hint = 
          'NTabEd: Unregistered ShareWare Component'#10'(c) 1997 H. Lohninger, ' +
          'POB 123, A-1060 Vienna, Austria'#10'http://www.lohninger.com/'
        Align = alClient
        AutoAdvance = False
        AttribRowVisible = True
        AttribColVisible = False
        ColorBackground = clWindow
        ColorFixed = clBtnFace
        ColorNormal = clNavy
        ColorSelected = clWhite
        ColorMarkedA = clRed
        ColorMarkedB = clBlue
        ColorMarkedBoth = 13369531
        DefaultColWidth = 64
        NrOfColumns = 3
        NrOfRows = 4
        NumWidth = 1
        ColWidths = (
          80
          32
          64
          64
          64)
        RowHeights = (
          24
          24
          24
          24
          24)
      end
    end
    object TTabPage
      Left = 4
      Top = 27
      Caption = 'Kohonen Map'
      object RCKohMap: TRChart
        Left = 0
        Top = 0
        Width = 527
        Height = 446
        Hint = 
          'RChart: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, ' +
          'POB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
        Align = alClient
        ShowHint = True
        AllocSize = 1000
        AutoRedraw = True
        RRim = 20
        TRim = 20
        BRim = 40
        BackGroundImg.IncludePath = False
        BackGroundImg.FillMode = bfStretch
        ClassDefault = 0
        GridStyle = gsNone
        GridDx = 1
        GridDy = 1
        Isometric = False
        JointLayers.L01xControlledBy = 1
        JointLayers.L01yControlledBy = 1
        JointLayers.L02xControlledBy = 2
        JointLayers.L02yControlledBy = 2
        JointLayers.L03xControlledBy = 3
        JointLayers.L03yControlledBy = 3
        JointLayers.L04xControlledBy = 4
        JointLayers.L04yControlledBy = 4
        JointLayers.L05xControlledBy = 5
        JointLayers.L05yControlledBy = 5
        JointLayers.L06xControlledBy = 6
        JointLayers.L06yControlledBy = 6
        JointLayers.L07xControlledBy = 7
        JointLayers.L07yControlledBy = 7
        JointLayers.L08xControlledBy = 8
        JointLayers.L08yControlledBy = 8
        JointLayers.L09xControlledBy = 9
        JointLayers.L09yControlledBy = 9
        JointLayers.L10xControlledBy = 10
        JointLayers.L10yControlledBy = 10
        JointLayers.L11xControlledBy = 11
        JointLayers.L11yControlledBy = 11
        JointLayers.L12xControlledBy = 12
        JointLayers.L12yControlledBy = 12
        JointLayers.L13xControlledBy = 13
        JointLayers.L13yControlledBy = 13
        JointLayers.L14xControlledBy = 14
        JointLayers.L14yControlledBy = 14
        JointLayers.L15xControlledBy = 15
        JointLayers.L15yControlledBy = 15
        JointLayers.L16xControlledBy = 16
        JointLayers.L16yControlledBy = 16
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
        Scale1X.RangeHigh = 10
        Scale1X.ShortTicks = True
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
        Scale1Y.ShortTicks = True
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
        Scale3X.CaptionPosX = 10
        Scale3X.CaptionPosY = 100
        Scale3X.CaptionAlignment = taCenter
        Scale3X.CaptionAnchor = uaSclCenter
        Scale3X.ColorScale = clGreen
        Scale3X.DateFormat.TimeFormat = tfHHMMSS
        Scale3X.DateFormat.DateSeparator = '-'
        Scale3X.DateFormat.TimeSeparator = ':'
        Scale3X.DateFormat.YearLength = ylYYYY
        Scale3X.DateFormat.MonthName = True
        Scale3X.DateFormat.DateOrder = doDDMMYY
        Scale3X.DateFormat.DateForTime = dtOnePerDay
        Scale3X.DecPlaces = -2
        Scale3X.Font.Charset = DEFAULT_CHARSET
        Scale3X.Font.Color = clWindowText
        Scale3X.Font.Height = -13
        Scale3X.Font.Name = 'MS Sans Serif'
        Scale3X.Font.Style = []
        Scale3X.Logarithmic = False
        Scale3X.LabelType = ftNum
        Scale3X.MinTicks = 3
        Scale3X.MinRange = 1E-10
        Scale3X.RangeHigh = 1
        Scale3X.ShortTicks = True
        Scale3X.ScalePos = 0
        Scale3X.Visible = False
        Scale3X.ScaleLocation = slBottom
        Scale3Y.CaptionPosX = 10
        Scale3Y.CaptionPosY = 100
        Scale3Y.CaptionAlignment = taRightJustify
        Scale3Y.CaptionAnchor = uaSclTopLft
        Scale3Y.ColorScale = clGreen
        Scale3Y.DateFormat.TimeFormat = tfHHMMSS
        Scale3Y.DateFormat.DateSeparator = '-'
        Scale3Y.DateFormat.TimeSeparator = ':'
        Scale3Y.DateFormat.YearLength = ylYYYY
        Scale3Y.DateFormat.MonthName = True
        Scale3Y.DateFormat.DateOrder = doDDMMYY
        Scale3Y.DateFormat.DateForTime = dtOnePerDay
        Scale3Y.DecPlaces = -2
        Scale3Y.Font.Charset = DEFAULT_CHARSET
        Scale3Y.Font.Color = clWindowText
        Scale3Y.Font.Height = -13
        Scale3Y.Font.Name = 'MS Sans Serif'
        Scale3Y.Font.Style = []
        Scale3Y.Logarithmic = False
        Scale3Y.LabelType = ftNum
        Scale3Y.MinTicks = 3
        Scale3Y.MinRange = 1E-10
        Scale3Y.RangeHigh = 1
        Scale3Y.ShortTicks = True
        Scale3Y.ScalePos = 0
        Scale3Y.Visible = False
        Scale3Y.ScaleLocation = slLeft
        Scale4X.CaptionPosX = 10
        Scale4X.CaptionPosY = 100
        Scale4X.CaptionAlignment = taCenter
        Scale4X.CaptionAnchor = uaSclCenter
        Scale4X.ColorScale = clOlive
        Scale4X.DateFormat.TimeFormat = tfHHMMSS
        Scale4X.DateFormat.DateSeparator = '-'
        Scale4X.DateFormat.TimeSeparator = ':'
        Scale4X.DateFormat.YearLength = ylYYYY
        Scale4X.DateFormat.MonthName = True
        Scale4X.DateFormat.DateOrder = doDDMMYY
        Scale4X.DateFormat.DateForTime = dtOnePerDay
        Scale4X.DecPlaces = -2
        Scale4X.Font.Charset = DEFAULT_CHARSET
        Scale4X.Font.Color = clWindowText
        Scale4X.Font.Height = -13
        Scale4X.Font.Name = 'MS Sans Serif'
        Scale4X.Font.Style = []
        Scale4X.Logarithmic = False
        Scale4X.LabelType = ftNum
        Scale4X.MinTicks = 3
        Scale4X.MinRange = 1E-10
        Scale4X.RangeHigh = 1
        Scale4X.ShortTicks = True
        Scale4X.ScalePos = 0
        Scale4X.Visible = False
        Scale4X.ScaleLocation = slBottom
        Scale4Y.CaptionPosX = 10
        Scale4Y.CaptionPosY = 100
        Scale4Y.CaptionAlignment = taRightJustify
        Scale4Y.CaptionAnchor = uaSclTopLft
        Scale4Y.ColorScale = clOlive
        Scale4Y.DateFormat.TimeFormat = tfHHMMSS
        Scale4Y.DateFormat.DateSeparator = '-'
        Scale4Y.DateFormat.TimeSeparator = ':'
        Scale4Y.DateFormat.YearLength = ylYYYY
        Scale4Y.DateFormat.MonthName = True
        Scale4Y.DateFormat.DateOrder = doDDMMYY
        Scale4Y.DateFormat.DateForTime = dtOnePerDay
        Scale4Y.DecPlaces = -2
        Scale4Y.Font.Charset = DEFAULT_CHARSET
        Scale4Y.Font.Color = clWindowText
        Scale4Y.Font.Height = -13
        Scale4Y.Font.Name = 'MS Sans Serif'
        Scale4Y.Font.Style = []
        Scale4Y.Logarithmic = False
        Scale4Y.LabelType = ftNum
        Scale4Y.MinTicks = 3
        Scale4Y.MinRange = 1E-10
        Scale4Y.RangeHigh = 1
        Scale4Y.ShortTicks = True
        Scale4Y.ScalePos = 0
        Scale4Y.Visible = False
        Scale4Y.ScaleLocation = slLeft
        ShadowStyle = ssFlying
        ShadowColor = clGray
        ShadowBakColor = clSilver
        TextFontStyle = []
        TextBkStyle = tbClear
        TextBkColor = clWhite
        TextAlignment = taCenter
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 535
    Height = 105
    Align = alTop
    TabOrder = 1
    object NLAlpha: TNumLab
      Left = 376
      Top = 24
      Width = 145
      Height = 22
      Hint = 
        'NumLab: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, ' +
        'POB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
      Alignment = taCenter
      ColorLabBakG = clSilver
      ColorLabText = clBlack
      ColorOutBakG = clBtnFace
      ColorOutText = clBlack
      ColorScheme = csBWG
      Comma = False
      DisplayType = dtFixP
      DTFormat = 'mmm-dd, yyyy'
      Empty = False
      ForcePlusSign = False
      FrameStyle = fsLowered
      LabelWidth = 80
      LeftSpace = 55
      LeftText = 'alpha:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 2
      RightTextAlignment = taLeftJustify
      ShowHint = True
      StateText = 'undefined'
      Value = 1
    end
    object NLSteps: TNumLab
      Left = 376
      Top = 72
      Width = 145
      Height = 22
      Hint = 
        'NumLab: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, ' +
        'POB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
      Alignment = taCenter
      ColorLabBakG = clSilver
      ColorLabText = clBlack
      ColorOutBakG = clBtnFace
      ColorOutText = clBlack
      ColorScheme = csBWG
      Comma = False
      DisplayType = dtInt
      DTFormat = 'mmm-dd, yyyy'
      Empty = False
      ForcePlusSign = False
      FrameStyle = fsLowered
      LabelWidth = 80
      LeftSpace = 55
      LeftText = 'steps:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 2
      RightTextAlignment = taLeftJustify
      ShowHint = True
      StateText = 'undefined'
      Value = 500
    end
    object Label1: TLabel
      Left = 256
      Top = 11
      Width = 57
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'x size:'
    end
    object Label2: TLabel
      Left = 256
      Top = 35
      Width = 57
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'y size:'
    end
    object Label3: TLabel
      Left = 232
      Top = 73
      Width = 81
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = '# neighbors:'
    end
    object BButExit: TBitBtn
      Left = 8
      Top = 5
      Width = 104
      Height = 29
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
    object BButLoad: TBitBtn
      Left = 8
      Top = 37
      Width = 104
      Height = 29
      Caption = 'Load Data'
      TabOrder = 1
      OnClick = BButLoadClick
      Glyph.Data = {
        36010000424D3601000000000000760000002800000015000000100000000100
        040000000000C000000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFF000FFFFFFFFFFFFFFFFFFFFF000FFF0000000000000FFFFF000FF00
        8B8B8B8B8B8B0FFFF000FF0F08B8B8B8B8B80FFFF000FF0B0B8B8B8B8B8B80FF
        F000FF0FB0B8B8B8B8B8B0FFF000FF0BF08B8B8B8B8B8B0FF000FF0FBF000008
        B8B8B80FF000FF0BFBFBFBF0000000FFF000FF0FBFBFBFBFBFB0FFFFF000FF0B
        FBFBFBFBFBF0FFFFF000FF0FBFBF0000000FFFFFF000FFF00000FFFFFFFFFFFF
        F000FFFFFFFFFFFFFFFFFFFFF000FFFFFFFFFFFFFFFFFFFFF000}
    end
    object BButTrainIt: TBitBtn
      Left = 8
      Top = 69
      Width = 104
      Height = 29
      Caption = 'Start Training'
      Enabled = False
      TabOrder = 2
      OnClick = BButTrainItClick
    end
    object SBAlpha: TScrollBar
      Left = 392
      Top = 8
      Width = 121
      Height = 13
      PageSize = 0
      Position = 100
      TabOrder = 3
      OnChange = SBAlphaChange
    end
    object SBSteps: TScrollBar
      Left = 392
      Top = 56
      Width = 121
      Height = 13
      Max = 19
      Min = 1
      PageSize = 0
      Position = 11
      TabOrder = 4
      OnChange = SBStepsChange
    end
    object NIOysize: TNumIO
      Left = 320
      Top = 32
      Width = 50
      Height = 24
      Hint = 
        'NumIO: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, P' +
        'OB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
      Beep = False
      DecPlaceSep = dsDot
      FixPointDecPlaces = 2
      InputFormat = itInt
      RangeHigh = 1.7E308
      RangeLow = -1.7E308
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      Text = '4'
    end
    object NIOxsize: TNumIO
      Left = 320
      Top = 8
      Width = 50
      Height = 24
      Hint = 
        'NumIO: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, P' +
        'OB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
      Beep = False
      DecPlaceSep = dsDot
      FixPointDecPlaces = 2
      InputFormat = itInt
      RangeHigh = 1.7E308
      RangeLow = -1.7E308
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      Text = '4'
    end
    object NIONeighb: TNumIO
      Left = 320
      Top = 70
      Width = 50
      Height = 24
      Hint = 
        'NumIO: Unregistered ShareWare Component'#10'(c) 1998 H. Lohninger, P' +
        'OB 123, A-1061 Vienna, Austria'#10'http://www.lohninger.com/'
      Beep = False
      DecPlaceSep = dsDot
      FixPointDecPlaces = 2
      InputFormat = itInt
      RangeHigh = 1.7E308
      RangeLow = -1.7E308
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      Text = '2'
    end
    object BButStoreNet: TBitBtn
      Left = 120
      Top = 37
      Width = 104
      Height = 29
      Caption = 'Store Network'
      Enabled = False
      TabOrder = 8
      OnClick = BButStoreNetClick
    end
    object BButLoadNet: TBitBtn
      Left = 120
      Top = 5
      Width = 104
      Height = 29
      Caption = 'Load Network'
      TabOrder = 9
      OnClick = BButLoadNetClick
    end
    object BButContTrain: TBitBtn
      Left = 120
      Top = 69
      Width = 104
      Height = 29
      Caption = 'Continue Trng'
      Enabled = False
      TabOrder = 10
      OnClick = BButContTrainClick
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 484
    Top = 140
  end
  object KohMap1: TKohonen
    Cyclic = False
    InitialAlpha = 1
    InitialNeighbors = 2
    NrOfInSens = 1
    NrOfTrnSteps = 200
    SizeX = 1
    SizeY = 1
    OnFeedback = KohMap1Feedback
    Left = 488
    Top = 208
  end
  object RowVect: TVector
    NrOfElem = 1
    Left = 488
    Top = 240
  end
  object SaveDialog1: TSaveDialog
    Left = 488
    Top = 176
  end
end
