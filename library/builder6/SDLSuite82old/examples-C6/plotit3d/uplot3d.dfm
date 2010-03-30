object Form1: TForm1
  Left = 303
  Top = 249
  Width = 1005
  Height = 730
  Caption = 'Plot3D Sample Application'
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
  object Plot3D1: TPlot3D
    Left = 0
    Top = 0
    Width = 702
    Height = 703
    Cursor = crHandPoint
    Align = alClient
    ShowHint = False
    PopupMenu = popMenMouse
    ParentShowHint = False
    BoundBoxStyle = bbFaces
    CentX = 300
    CentY = 350
    ColorFrame = clGray
    ColorBakGnd = clNavy
    ColorCodeAvg = False
    ColorCubeFrame = 4210752
    ColorCubeHidLin = 11579568
    ColorCubeFaceLow = clSilver
    ColorCubeFaceHigh = 16707310
    ColorXCoords = clWhite
    ColorYCoords = clYellow
    ColorZCoords = clFuchsia
    ColorMesh = clMaroon
    ColorHigh = clYellow
    ColorMid = clWhite
    ColorLow = clFuchsia
    ColorScaleHigh = 14
    ColorScaleLow = -5
    ColorCodingMode = ccmTwoColors
    ColorScheme = csBWG
    DecPlaceX = 1
    DecPlaceY = 0
    DecPlaceZ = 2
    FrameStyle = fsLowered
    MeshVisible = True
    Magnification = 1
    MouseAction = maRotate
    MinTickX = 3
    MinTickY = 3
    MinTickZ = 3
    RangeXLow = -1
    RangeYLow = -1.2
    RangeZLow = -5
    RangeXHigh = 10
    RangeYHigh = 1.2
    RangeZHigh = 15
    ScaleFactX = 1
    ScaleFactY = 1
    ScaleFactZ = 1
    ViewAngleX = 66
    ViewAngleZ = 135
    VisibleXCoords = True
    VisibleYCoords = True
    VisibleZCoords = True
    OnDataRendered = Plot3D1DataRendered
    OnMouseAction = Plot3D1MouseAction
    OnBeforeRenderPolygon = Plot3D1BeforeRenderPolygon
    OnMouseMoveOverPlot = Plot3D1MouseMoveOverPlot
  end
  object Panel2: TPanel
    Left = 702
    Top = 0
    Width = 295
    Height = 703
    Align = alRight
    TabOrder = 0
    object NLabZ: TNumLab
      Left = 160
      Top = 7
      Width = 133
      Height = 22
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
      LabelWidth = 67
      LeftSpace = 60
      LeftText = 'Angle Z:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 2
      RightTextAlignment = taLeftJustify
      ShowHint = True
      StateText = 'undefined'
      Value = 135
    end
    object NLabX: TNumLab
      Left = 8
      Top = 8
      Width = 133
      Height = 22
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
      LabelWidth = 67
      LeftSpace = 60
      LeftText = 'Angle X:'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 2
      RightTextAlignment = taLeftJustify
      ShowHint = True
      StateText = 'undefined'
      Value = 66
    end
    object Label1: TLabel
      Left = 172
      Top = 280
      Width = 109
      Height = 16
      AutoSize = False
      Caption = 'Mesh Color'
    end
    object NLabMag: TNumLab
      Left = 7
      Top = 93
      Width = 133
      Height = 22
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
      LabelWidth = 67
      LeftSpace = 60
      LeftText = 'Magnif.'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      Precision = 3
      RightTextAlignment = taLeftJustify
      StateText = 'undefined'
      Value = 1
    end
    object Label2: TLabel
      Left = 12
      Top = 280
      Width = 149
      Height = 16
      AutoSize = False
      Caption = 'Surface Colors'
    end
    object Label3: TLabel
      Left = 8
      Top = 345
      Width = 33
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'high'
    end
    object LblColMid: TLabel
      Left = 8
      Top = 322
      Width = 33
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'mid'
      Enabled = False
    end
    object Label5: TLabel
      Left = 8
      Top = 298
      Width = 33
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'low'
    end
    object Label4: TLabel
      Left = 12
      Top = 402
      Width = 76
      Height = 16
      Caption = 'Color Range'
    end
    object SbAutoscale: TSpeedButton
      Left = 10
      Top = 632
      Width = 135
      Height = 31
      Caption = 'AutoScale'
      OnClick = SbAutoscaleClick
    end
    object SBReset: TSpeedButton
      Left = 152
      Top = 632
      Width = 135
      Height = 31
      Caption = 'Reset'
      OnClick = SBResetClick
    end
    object Label6: TLabel
      Left = 168
      Top = 76
      Width = 110
      Height = 16
      Caption = 'indiv. scale factors'
    end
    object NLabCellX: TNumLab
      Left = 184
      Top = 208
      Width = 100
      Height = 22
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
      ForcePlusSign = False
      FrameStyle = fsLowered
      LabelWidth = 40
      LeftSpace = 50
      LeftText = 'Cell X'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 0
      RightTextAlignment = taLeftJustify
      ShowHint = False
      StateText = 'undefined'
    end
    object NLabCellY: TNumLab
      Left = 184
      Top = 232
      Width = 100
      Height = 22
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
      ForcePlusSign = False
      FrameStyle = fsLowered
      LabelWidth = 40
      LeftSpace = 50
      LeftText = 'Cell Y'
      LeftTextAlignment = taRightJustify
      OverflowIndicator = '*********'
      ParentShowHint = False
      Precision = 0
      RightTextAlignment = taLeftJustify
      ShowHint = False
      StateText = 'undefined'
    end
    object Label9: TLabel
      Left = 16
      Top = 464
      Width = 129
      Height = 16
      Caption = 'Colors of Coordinates'
    end
    object ScrBarAngleZ: TScrollBar
      Left = 165
      Top = 34
      Width = 124
      Height = 20
      Max = 360
      PageSize = 0
      Position = 135
      TabOrder = 0
      OnChange = ScrBarAngleZChange
    end
    object ScrBarAngleX: TScrollBar
      Left = 13
      Top = 34
      Width = 124
      Height = 20
      Max = 360
      PageSize = 0
      Position = 66
      TabOrder = 1
      OnChange = ScrBarAngleXChange
    end
    object CSelHigh: TColSel
      Left = 45
      Top = 296
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clYellow
      ShowHint = True
      TabOrder = 2
      OnChange = CSelHighChange
    end
    object CSelLow: TColSel
      Left = 45
      Top = 344
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clFuchsia
      ShowHint = True
      TabOrder = 3
      OnChange = CSelLowChange
    end
    object CSelGrid: TColSel
      Left = 173
      Top = 297
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clMaroon
      ShowHint = True
      TabOrder = 4
      OnChange = CSelGridChange
    end
    object ScrBarMagnif: TScrollBar
      Left = 13
      Top = 119
      Width = 124
      Height = 20
      Max = 200
      PageSize = 0
      Position = 100
      TabOrder = 5
      OnChange = ScrBarMagnifChange
    end
    object BButExit: TBitBtn
      Left = 10
      Top = 666
      Width = 279
      Height = 31
      Caption = 'Exit'
      TabOrder = 6
      OnClick = BButExitClick
      Glyph.Data = {
        72010000424D7201000000000000760000002800000015000000150000000100
        040000000000FC00000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        888888888000880000000000000008888000880EEEEEEEEEEE00088880008806
        66666666E0008888800088066666666E000888888000880666666666E0888888
        80008806666666666E088888800088066666666666E088888000880666666666
        666E088880008806666666666666E088800088066446666666666E0880008806
        40446666666666E0800088040004466666666600000088000080446666666000
        8000880008880446666600088000880088888044666000888000888888888804
        4600088880008888888888804000888880008888888888880008888880008888
        88888888808888888000888888888888888888888000}
    end
    object CBoxMesh: TCheckBox
      Left = 172
      Top = 320
      Width = 109
      Height = 17
      Caption = 'Mesh Visible'
      Checked = True
      State = cbChecked
      TabOrder = 7
      OnClick = CBoxMeshClick
    end
    object CselMid: TColSel
      Left = 45
      Top = 320
      Width = 109
      Height = 22
      Color = clBtnFace
      ColorBarWidth = 30
      Enabled = False
      NumColors = 20
      SelColor = clWhite
      TabOrder = 8
      OnChange = CselMidChange
    end
    object ScrBarColorHigh: TScrollBar
      Left = 13
      Top = 424
      Width = 140
      Height = 20
      Max = 200
      PageSize = 0
      Position = 50
      TabOrder = 9
      OnChange = ScrBarColorHighChange
    end
    object CBox3colmod: TCheckBox
      Left = 16
      Top = 372
      Width = 129
      Height = 17
      Caption = '3 Color Model'
      TabOrder = 10
      OnClick = CBox3colmodClick
    end
    object ScrBarSclZ: TScrollBar
      Left = 165
      Top = 143
      Width = 124
      Height = 20
      Max = 200
      Min = 20
      PageSize = 0
      Position = 100
      TabOrder = 11
      OnChange = ScrBarSclZChange
    end
    object ScrBarSclY: TScrollBar
      Left = 165
      Top = 120
      Width = 124
      Height = 20
      Max = 200
      Min = 20
      PageSize = 0
      Position = 100
      TabOrder = 12
      OnChange = ScrBarSclYChange
    end
    object ScrBarSclX: TScrollBar
      Left = 165
      Top = 96
      Width = 124
      Height = 20
      Max = 200
      Min = 20
      PageSize = 0
      Position = 100
      TabOrder = 13
      OnChange = ScrBarSclXChange
    end
    object RGFrameMode: TRadioGroup
      Left = 8
      Top = 184
      Width = 129
      Height = 73
      Caption = ' Frame Mode '
      ItemIndex = 2
      Items.Strings = (
        'No Frame'
        'Wire Frame'
        'Cube Faces')
      TabOrder = 14
      OnClick = RGFrameModeClick
    end
    object CBoxGridCursor: TCheckBox
      Left = 172
      Top = 184
      Width = 105
      Height = 17
      Caption = 'Cell Cursor'
      TabOrder = 15
    end
    object ColSelX: TColSel
      Left = 45
      Top = 485
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clWhite
      ShowHint = False
      TabOrder = 16
      OnChange = ColSelXChange
    end
    object ColSelY: TColSel
      Left = 45
      Top = 509
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clYellow
      ShowHint = False
      TabOrder = 17
      OnChange = ColSelYChange
    end
    object ColSelZ: TColSel
      Left = 45
      Top = 533
      Width = 109
      Height = 22
      ColorBarWidth = 30
      NumColors = 20
      ParentShowHint = False
      SelColor = clFuchsia
      ShowHint = False
      TabOrder = 18
      OnChange = ColSelZChange
    end
    object CBoxXCoords: TCheckBox
      Left = 160
      Top = 488
      Width = 129
      Height = 17
      Caption = 'X-Coords Visible'
      Checked = True
      State = cbChecked
      TabOrder = 19
      OnClick = CBoxZCoordsClick
    end
    object CBoxYCoords: TCheckBox
      Left = 160
      Top = 512
      Width = 129
      Height = 17
      Caption = 'Y-Coords Visible'
      Checked = True
      State = cbChecked
      TabOrder = 20
      OnClick = CBoxZCoordsClick
    end
    object CBoxZCoords: TCheckBox
      Left = 160
      Top = 536
      Width = 129
      Height = 17
      Caption = 'Z-Coords Visible'
      Checked = True
      State = cbChecked
      TabOrder = 21
      OnClick = CBoxZCoordsClick
    end
  end
  object popMenMouse: TPopupMenu
    Left = 64
    Top = 48
    object Rotate1: TMenuItem
      Caption = 'Rotate'
      OnClick = Rotate1Click
    end
    object Pan1: TMenuItem
      Caption = 'Pan'
      OnClick = Pan1Click
    end
    object Zoom1: TMenuItem
      Caption = 'Zoom'
      OnClick = Zoom1Click
    end
    object RotateandZoom1: TMenuItem
      Caption = 'Rotate and Zoom'
      OnClick = RotateandZoom1Click
    end
    object RotXOnly1: TMenuItem
      Caption = 'Rot X Only'
      OnClick = RotXOnly1Click
    end
    object RotZOnly1: TMenuItem
      Caption = 'Rot Z Only'
      OnClick = RotZOnly1Click
    end
  end
end
