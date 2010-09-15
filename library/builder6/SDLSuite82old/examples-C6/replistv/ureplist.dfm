object Form1: TForm1
  Left = 307
  Top = 238
  Width = 700
  Height = 488
  Caption = 'Form1'
  Color = clBtnFace
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
  object Label1: TLabel
    Left = 536
    Top = 120
    Width = 145
    Height = 16
    AutoSize = False
    Caption = 'Text Color'
  end
  object Label2: TLabel
    Left = 536
    Top = 168
    Width = 145
    Height = 16
    AutoSize = False
    Caption = 'Background Color 1'
  end
  object Label3: TLabel
    Left = 536
    Top = 216
    Width = 145
    Height = 16
    AutoSize = False
    Caption = 'Background Color 2'
  end
  object Label4: TLabel
    Left = 536
    Top = 264
    Width = 118
    Height = 16
    Caption = 'Background Pattern'
  end
  object SpeedButton1: TSpeedButton
    Left = 660
    Top = 184
    Width = 21
    Height = 22
    Caption = '...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 660
    Top = 232
    Width = 21
    Height = 22
    Caption = '...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object RL1: TReportListView
    Left = 8
    Top = 8
    Width = 521
    Height = 441
    NrOfColumns = 4
    NrOfRows = 25
    AutoAdvance = True
    ColorHigh = 13408614
    ColorText = clNavy
    ColorBkgdNormal = clWhite
    ColorBkgdShaded = 15396067
    ColorHighText = clWhite
    ColorSelectedRow = 9747181
    ColorSelectedRowText = clNavy
    ColorSelectedCol = clBlack
    ColorSelectedColText = clBlack
    ColorSelectedBoth = clBlack
    ColorSelectedBothText = clBlack
    DefaultColWidth = 64
    DefaultRowHeight = 18
    HighLightBold = False
    HighLightRow = 0
    HighLightColumn = 0
    InterRowIndicatorColor = clRed
    InterRowIndicatorWidth = 3
    LeftCol = 0
    Options = [goFixedVertLine, goFixedHorzLine, goColSizing, goRowSelect, goThumbTracking]
    RowSelectMode = 1
    RowColPattern = 1
    TabOrder = 0
    SortEnabled = True
    TopRow = 1
    ColWidths = (
      56
      100
      107
      310)
    RowHeights = (
      20
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18
      18)
  end
  object BButAddRow: TBitBtn
    Left = 536
    Top = 8
    Width = 145
    Height = 33
    Caption = 'Add 100 customers'
    TabOrder = 1
    OnClick = BButAddRowClick
  end
  object BButUnsort: TBitBtn
    Left = 536
    Top = 56
    Width = 145
    Height = 33
    Caption = 'Unsort'
    TabOrder = 2
    OnClick = BButUnsortClick
  end
  object CSText: TColSel
    Left = 536
    Top = 136
    Width = 145
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clNavy
    TabOrder = 3
    OnChange = CSTextChange
  end
  object CSBkg1: TColSel
    Left = 536
    Top = 184
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clWhite
    TabOrder = 4
    OnChange = CSBkg1Change
  end
  object CSBkg2: TColSel
    Left = 536
    Top = 232
    Width = 121
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = 15396067
    TabOrder = 5
    OnChange = CSBkg2Change
  end
  object SBarRowPat: TScrollBar
    Left = 536
    Top = 282
    Width = 145
    Height = 17
    Max = 10
    PageSize = 0
    Position = 1
    TabOrder = 6
    OnChange = SBarRowPatChange
  end
  object BButExit: TBitBtn
    Left = 536
    Top = 416
    Width = 145
    Height = 33
    Caption = 'Exit'
    TabOrder = 7
    OnClick = BButExitClick
  end
  object CBVertLines: TCheckBox
    Left = 536
    Top = 312
    Width = 128
    Height = 17
    Caption = 'Vertical Lines'
    TabOrder = 8
    OnClick = CBVertLinesClick
  end
  object CBHorzLines: TCheckBox
    Left = 536
    Top = 328
    Width = 128
    Height = 17
    Caption = 'Horizontal Lines'
    TabOrder = 9
    OnClick = CBHorzLinesClick
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 472
    Top = 40
  end
end
