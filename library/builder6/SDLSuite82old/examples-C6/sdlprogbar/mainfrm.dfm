object Form1: TForm1
  Left = 705
  Top = 221
  Width = 541
  Height = 679
  Caption = 'SDL Progress Bar Demo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object PBar1: TProgBar
    Left = 56
    Top = 64
    Width = 433
    Height = 289
    ColorBackGnd = clMaroon
    ColorMapMode = cgmStretch
    ColorGrid = clNavy
    ColorMargin = clSilver
    ColorScheme = csBWG
    ColorMin = clLime
    ColorMax = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -30
    Font.Name = 'Times New Roman'
    Font.Pitch = fpFixed
    Font.Style = [fsBold, fsItalic]
    FrameStyleOuter = fsRaised
    FrameStyleInner = fsLowered
    GridDist = 0
    MarginBottom = 14
    MarginLeft = 24
    MarginRight = 8
    MarginTop = 38
    Max = 100
    ParentFont = False
    Direction = dirRightward
    ShowColorGradient = True
    TextAlignment = taCenter
    TextAngle = 45
    TextDecPlaces = 0
    TextPosX = 216
    TextPosY = 160
    TextVisible = True
    Value = 70
    OnShowValue = PBar1ShowValue
  end
  object PBar2: TProgBar
    Left = 496
    Top = 64
    Width = 25
    Height = 289
    ColorBackGnd = clSilver
    ColorMapMode = cgmStretch
    ColorGrid = clBtnFace
    ColorMargin = clSilver
    ColorScheme = csBWG
    ColorMin = clBlue
    ColorMax = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -17
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    FrameStyleOuter = fsRaised
    FrameStyleInner = fsNone
    GridDist = 10
    MarginBottom = 4
    MarginLeft = 4
    MarginRight = 4
    MarginTop = 80
    Max = 500
    ParentFont = False
    Direction = dirUpward
    ShowColorGradient = False
    TextAlignment = taRightJustify
    TextAngle = 90
    TextDecPlaces = 0
    TextPosX = 12
    TextPosY = 6
    TextVisible = True
    Value = 350
  end
  object PBar3: TProgBar
    Left = 8
    Top = 64
    Width = 41
    Height = 289
    ColorBackGnd = clSilver
    ColorMapMode = cgmStretch
    ColorGrid = clBlack
    ColorMargin = clSilver
    ColorScheme = csBWG
    ColorMin = clBlue
    ColorMax = clRed
    FrameStyleOuter = fsRaised
    FrameStyleInner = fsLowered
    GridDist = 0
    MarginBottom = 4
    MarginLeft = 29
    MarginRight = 4
    MarginTop = 20
    Max = 500
    Direction = dirUpward
    ShowColorGradient = True
    TextAlignment = taCenter
    TextAngle = 0
    TextDecPlaces = 1
    TextPosX = 20
    TextPosY = 10
    TextVisible = True
    Value = 350
  end
  object PBar4: TProgBar
    Left = 8
    Top = 8
    Width = 257
    Height = 44
    ColorBackGnd = clSilver
    ColorMapMode = cgmStretch
    ColorGrid = clBlack
    ColorMargin = clSilver
    ColorScheme = csBWG
    ColorMin = clBlue
    ColorMax = clRed
    FrameStyleOuter = fsNone
    FrameStyleInner = fsNone
    GridDist = 0
    MarginBottom = 4
    MarginLeft = 4
    MarginRight = 0
    MarginTop = 4
    Max = 500
    Direction = dirLeftward
    ShowColorGradient = True
    TextAlignment = taCenter
    TextAngle = 0
    TextDecPlaces = 0
    TextPosX = 10
    TextPosY = 10
    TextVisible = False
    Value = 350
  end
  object PBar5: TProgBar
    Left = 264
    Top = 8
    Width = 257
    Height = 44
    ColorBackGnd = clSilver
    ColorMapMode = cgmStretch
    ColorGrid = clBlack
    ColorMargin = clSilver
    ColorScheme = csBWG
    ColorMin = clBlue
    ColorMax = clLime
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    FrameStyleOuter = fsNone
    FrameStyleInner = fsNone
    GridDist = 0
    MarginBottom = 4
    MarginLeft = 0
    MarginRight = 4
    MarginTop = 4
    Max = 500
    ParentFont = False
    Direction = dirRightward
    ShowColorGradient = True
    TextAlignment = taCenter
    TextAngle = 0
    TextDecPlaces = 0
    TextPosX = 10
    TextPosY = 10
    TextVisible = False
    Value = 350
  end
  object Label1: TLabel
    Left = 376
    Top = 388
    Width = 113
    Height = 16
    AutoSize = False
    Caption = 'Rotation Angle'
  end
  object Label2: TLabel
    Left = 8
    Top = 360
    Width = 121
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = 'Progress Bar Value'
  end
  object Label3: TLabel
    Left = 376
    Top = 440
    Width = 108
    Height = 16
    Caption = 'Background Color'
  end
  object Label4: TLabel
    Left = 168
    Top = 388
    Width = 48
    Height = 16
    Caption = 'Margins'
  end
  object ScrollBar1: TScrollBar
    Left = 136
    Top = 360
    Width = 385
    Height = 16
    Max = 500
    PageSize = 0
    Position = 350
    TabOrder = 0
    OnChange = ScrollBar1Change
  end
  object RGDirection: TRadioGroup
    Left = 376
    Top = 552
    Width = 145
    Height = 89
    Caption = ' Direction '
    ItemIndex = 3
    Items.Strings = (
      'upward'
      'downward'
      'leftward'
      'rightward')
    TabOrder = 1
    OnClick = RGDirectionClick
  end
  object CBoxGradient: TCheckBox
    Left = 8
    Top = 438
    Width = 137
    Height = 17
    Caption = 'Show Gradient'
    Checked = True
    State = cbChecked
    TabOrder = 2
    OnClick = CBoxGradientClick
  end
  object ColSelMin: TColSel
    Left = 8
    Top = 456
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clLime
    TabOrder = 3
    OnChange = ColSelMinChange
  end
  object ColSelMax: TColSel
    Left = 8
    Top = 480
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clYellow
    TabOrder = 4
    OnChange = ColSelMaxChange
  end
  object RGGradMode: TRadioGroup
    Left = 8
    Top = 512
    Width = 145
    Height = 73
    Caption = ' Gradient Mode '
    ItemIndex = 1
    Items.Strings = (
      'cgmCover'
      'cgmStretch'
      'cgmMove')
    TabOrder = 5
    OnClick = RGGradModeClick
  end
  object SBarTextAngle: TScrollBar
    Left = 376
    Top = 408
    Width = 145
    Height = 16
    Max = 360
    PageSize = 0
    Position = 45
    TabOrder = 6
    OnChange = SBarTextAngleChange
  end
  object BButLoadImage: TBitBtn
    Left = 376
    Top = 488
    Width = 145
    Height = 25
    Caption = 'Load Bkgnd Image'
    TabOrder = 7
    OnClick = BButLoadImageClick
  end
  object BButSpecialCurtain1: TBitBtn
    Left = 8
    Top = 592
    Width = 145
    Height = 25
    Caption = 'Special Curtain 1'
    TabOrder = 8
    OnClick = BButSpecialCurtain1Click
  end
  object BButNoImage: TBitBtn
    Left = 376
    Top = 514
    Width = 145
    Height = 25
    Caption = 'No Bkgnd Image'
    TabOrder = 9
    OnClick = BButNoImageClick
  end
  object CSelBakgnd: TColSel
    Left = 376
    Top = 456
    Width = 145
    Height = 22
    ColorBarWidth = 30
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    NumColors = 20
    ParentFont = False
    SelColor = clMaroon
    TabOrder = 10
    OnChange = CSelBakgndChange
  end
  object RGOutFrame: TRadioGroup
    Left = 168
    Top = 488
    Width = 193
    Height = 73
    Caption = ' Outer Frame '
    Columns = 2
    ItemIndex = 3
    Items.Strings = (
      'None'
      'Simple'
      'Lowered'
      'Raised'
      'Embossed'
      'Engraved')
    TabOrder = 11
    OnClick = RGOutFrameClick
  end
  object RGInnerFrame: TRadioGroup
    Left = 168
    Top = 568
    Width = 193
    Height = 73
    Caption = ' Inner Frame '
    Columns = 2
    ItemIndex = 2
    Items.Strings = (
      'None'
      'Simple'
      'Lowered'
      'Raised'
      'Embossed'
      'Engraved')
    TabOrder = 12
    OnClick = RGInnerFrameClick
  end
  object BButSpecialCurtain2: TBitBtn
    Left = 8
    Top = 618
    Width = 145
    Height = 25
    Caption = 'Special Curtain 2'
    TabOrder = 13
    OnClick = BButSpecialCurtain2Click
  end
  object SBarMarginTop: TScrollBar
    Left = 168
    Top = 408
    Width = 193
    Height = 16
    PageSize = 0
    Position = 38
    TabOrder = 14
    OnChange = SBarMarginTopChange
  end
  object SBarMarginBottom: TScrollBar
    Left = 168
    Top = 426
    Width = 193
    Height = 16
    PageSize = 0
    Position = 14
    TabOrder = 15
    OnChange = SBarMarginBottomChange
  end
  object SBarMarginLeft: TScrollBar
    Left = 168
    Top = 444
    Width = 193
    Height = 16
    PageSize = 0
    Position = 24
    TabOrder = 16
    OnChange = SBarMarginLeftChange
  end
  object SBarMarginRight: TScrollBar
    Left = 168
    Top = 462
    Width = 193
    Height = 16
    PageSize = 0
    Position = 8
    TabOrder = 17
    OnChange = SBarMarginRightChange
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 8
  end
end
