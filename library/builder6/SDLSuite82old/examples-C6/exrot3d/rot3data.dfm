object Form1: TForm1
  Left = 281
  Top = 168
  Width = 674
  Height = 507
  Caption = 'Form1'
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
    Left = 8
    Top = 8
    Width = 457
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'left click and drag the mouse cursor in the image below'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 24
    Width = 457
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'right click into image below to change mouse options'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Rot3D1: TRot3D
    Left = 8
    Top = 48
    Width = 457
    Height = 345
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ShowHint = True
    PopupMenu = PopupMenu1
    AllocSize = 1000
    CentX = 240
    CentY = 170
    ColorFrame = clOlive
    ColorChart = 16775392
    ColorScheme = csBWG
    ColorCubeFrame = clMaroon
    ColorCubeHidLin = 14342874
    ColorCubeFaceLow = 15658751
    ColorCubeFaceHigh = 16579839
    IsoMetric = False
    AutoOrigin = True
    AutoScale = True
    FrameStyle = fsLowered
    Magnification = 0.8
    MouseAction = maRotate
    MouseRot3Axes = True
    BoundBoxStyle = bbFaces
    BoundBoxSize = 700
    AxDir = adLeftHanded
    AxSize = 700
    AxNameX = 'X'
    AxNameY = 'Y'
    AxNameZ = 'Z'
    ShowAxes = True
    TextFontStyle = []
    TextMarkSize = 8
    ViewAngleX = 170
    ViewAngleY = -10
    ViewAngleZ = 15
    OnMouseMove = Rot3D1MouseMove
    OnMouseDown = Rot3D1MouseDown
    OnMouseUp = Rot3D1MouseUp
  end
  object NLabGamma: TNumLab
    Left = 280
    Top = 448
    Width = 129
    Height = 22
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
    LeftSpace = 35
    LeftText = 'Z:'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    Precision = 2
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 15
  end
  object NLabBeta: TNumLab
    Left = 280
    Top = 424
    Width = 129
    Height = 22
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
    LeftSpace = 35
    LeftText = 'Y:'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    Precision = 2
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 350
  end
  object NLabAlpha: TNumLab
    Left = 280
    Top = 400
    Width = 129
    Height = 22
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
    LeftSpace = 35
    LeftText = 'X:'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    Precision = 2
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 170
  end
  object SBAutoRot: TSpeedButton
    Left = 416
    Top = 438
    Width = 113
    Height = 33
    AllowAllUp = True
    GroupIndex = 99
    Caption = 'Auto Rotation'
    OnClick = SBAutoRotClick
  end
  object NumLab4: TNumLab
    Left = 512
    Top = 48
    Width = 145
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
    LabelWidth = 80
    LeftSpace = 50
    LeftText = 'Magnf.'
    LeftTextAlignment = taRightJustify
    OverflowIndicator = '*********'
    Precision = 2
    RightTextAlignment = taLeftJustify
    StateText = 'undefined'
    Value = 0.8
  end
  object ScrollBar4: TScrollBar
    Left = 473
    Top = 48
    Width = 13
    Height = 345
    Kind = sbVertical
    PageSize = 0
    Position = 20
    TabOrder = 0
    OnChange = ScrollBar4Change
  end
  object SBAngX: TScrollBar
    Left = 8
    Top = 400
    Width = 257
    Height = 16
    Max = 360
    PageSize = 0
    Position = 170
    TabOrder = 1
    OnChange = SBAngXChange
  end
  object SBAngY: TScrollBar
    Left = 8
    Top = 424
    Width = 257
    Height = 16
    Max = 360
    PageSize = 0
    Position = 350
    TabOrder = 2
    OnChange = SBAngYChange
  end
  object SBAngZ: TScrollBar
    Left = 8
    Top = 448
    Width = 257
    Height = 16
    Max = 360
    PageSize = 0
    Position = 15
    TabOrder = 3
    OnChange = SBAngZChange
  end
  object BButExit: TBitBtn
    Left = 544
    Top = 438
    Width = 113
    Height = 33
    Caption = 'Exit'
    TabOrder = 4
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
  object RadioGroup1: TRadioGroup
    Left = 504
    Top = 88
    Width = 153
    Height = 113
    Caption = ' Bounding Box '
    TabOrder = 5
  end
  object RadioButton1: TRadioButton
    Left = 512
    Top = 112
    Width = 137
    Height = 17
    Caption = 'No Bounding Box'
    TabOrder = 6
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 512
    Top = 128
    Width = 137
    Height = 17
    Caption = 'Wire Frame'
    TabOrder = 7
    OnClick = RadioButton2Click
  end
  object RadioButton3: TRadioButton
    Left = 512
    Top = 144
    Width = 137
    Height = 17
    Caption = 'Transparent Cube'
    Checked = True
    TabOrder = 8
    TabStop = True
    OnClick = RadioButton3Click
  end
  object SBBBSize: TScrollBar
    Left = 520
    Top = 176
    Width = 129
    Height = 13
    Max = 1000
    PageSize = 0
    Position = 400
    TabOrder = 9
    OnChange = SBBBSizeChange
  end
  object SBAxSize: TScrollBar
    Left = 504
    Top = 264
    Width = 153
    Height = 13
    Max = 1000
    PageSize = 0
    Position = 700
    TabOrder = 10
    OnChange = SBAxSizeChange
  end
  object CheckBox1: TCheckBox
    Left = 504
    Top = 224
    Width = 97
    Height = 17
    Caption = 'Axes Visible'
    Checked = True
    State = cbChecked
    TabOrder = 11
    OnClick = CheckBox1Click
  end
  object CBIsoMetric: TCheckBox
    Left = 504
    Top = 240
    Width = 121
    Height = 17
    Caption = 'Isometric Axes'
    TabOrder = 12
    OnClick = CBIsoMetricClick
  end
  object BButPrintit: TBitBtn
    Left = 544
    Top = 392
    Width = 113
    Height = 33
    Caption = 'Print It'
    TabOrder = 13
    OnClick = BButPrintitClick
  end
  object RGCoordSystem: TRadioGroup
    Left = 496
    Top = 288
    Width = 161
    Height = 57
    Caption = ' Coordinate System '
    ItemIndex = 0
    Items.Strings = (
      'Left Handed'
      'Right Handed')
    TabOrder = 14
    OnClick = RGCoordSystemClick
  end
  object PopupMenu1: TPopupMenu
    Left = 496
    Top = 360
    object Rotate1: TMenuItem
      Caption = 'Rotate'
      OnClick = Rotate1Click
    end
    object Zoom1: TMenuItem
      Caption = 'Zoom'
      OnClick = Zoom1Click
    end
    object Pan1: TMenuItem
      Caption = 'Pan'
      OnClick = Pan1Click
    end
    object copy1: TMenuItem
      Caption = 'copy'
      object ToClipboard1: TMenuItem
        Caption = 'To Clipboard'
        OnClick = ToClipboard1Click
      end
      object ToBMPFile1: TMenuItem
        Caption = 'To BMP File'
        OnClick = ToBMPFile1Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 496
    Top = 392
  end
end
