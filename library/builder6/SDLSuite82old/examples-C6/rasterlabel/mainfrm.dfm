object FrmMain: TFrmMain
  Left = 384
  Top = 494
  Width = 739
  Height = 73
  Caption = 'Right-click into panel to set up parameters'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object RLab1: TRasterLab
    Left = 0
    Top = 0
    Width = 731
    Height = 45
    Align = alClient
    AutoHeight = True
    AutoCenter = False
    ColorLabBakG = clBlack
    ColorDotOn = clLime
    ColorDotOff = 4210752
    ColorScheme = csBWG
    DotSpacing = 1
    DotSize = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Default'
    Font.Style = []
    FrameStyle = fsLowered
    ParentFont = False
    ParentShowHint = False
    PosX = 2
    PosY = 1
    Proportional = False
    ScrollMode = rdsmRight
    ScrollInterval = 100
    ScrollIncrement = 1
    ScrollLoop = True
    CharBlockMode = rdbmOn
    ShowHint = True
    Text = '<pctday>% of the day is gone'
    OnMouseMove = RLab1MouseMove
    OnMouseDown = RLab1MouseDown
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 584
    Top = 32
  end
end
