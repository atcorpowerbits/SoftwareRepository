object FrmGradFill: TFrmGradFill
  Left = 481
  Top = 242
  BorderStyle = bsDialog
  Caption = 'Gradient Fill Example'
  ClientHeight = 399
  ClientWidth = 489
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 120
  TextHeight = 16
  object SBToggleColors: TSpeedButton
    Left = 144
    Top = 56
    Width = 41
    Height = 46
    AllowAllUp = True
    GroupIndex = 99
    Glyph.Data = {
      12010000424D12010000000000007600000028000000130000000D0000000100
      0400000000009C00000000000000000000001000000010000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFF00000FFFFFFFFCFCFFFFFFFF00000FFF1FFFFCFCFFFF1FFF00000FFF1
      1FFFCFCFFF11FFF00000FFF111FFCFCFF111FFF00000FFF1111FCFCF1111FFF0
      0000F1111111CFC1111111F00000FFF1111FCFCF1111FFF00000FFF111FFCFCF
      F111FFF00000FFF11FFFCFCFFF11FFF00000FFF1FFFFCFCFFFF1FFF00000FFFF
      FFFFCFCFFFFFFFF00000FFFFFFFFFFFFFFFFFFF00000}
    OnClick = SBToggleColorsClick
  end
  object Label2: TLabel
    Left = 19
    Top = 115
    Width = 78
    Height = 16
    Alignment = taRightJustify
    Caption = 'No. of colors:'
  end
  object GradFill3: TGradFill
    Left = 0
    Top = 336
    Width = 481
    Height = 57
    ColorFlipped = True
    ColorFirst = 8676936
    ColorLast = 12898528
    FillType = gtVert
    GridColor = clNavy
    GridMode = gmNone
    NrColors = 64
  end
  object GFQuad: TGradFill
    Left = 192
    Top = 56
    Width = 289
    Height = 273
    ColorFlipped = False
    ColorFirst = clYellow
    ColorLast = clFuchsia
    GridColor = clNavy
    GridMode = gmNone
    NrColors = 32
  end
  object Label3: TLabel
    Left = 8
    Top = 364
    Width = 345
    Height = 25
    AutoSize = False
    Caption = 'http://www.lohninger.com'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -23
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object Label1: TLabel
    Left = 368
    Top = 330
    Width = 113
    Height = 67
    Caption = 'SDL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -60
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Transparent = True
  end
  object Label4: TLabel
    Left = 192
    Top = 8
    Width = 60
    Height = 16
    Caption = 'GridMode'
  end
  object Label5: TLabel
    Left = 344
    Top = 8
    Width = 57
    Height = 16
    Caption = 'GridColor'
  end
  object BButExit: TBitBtn
    Left = 8
    Top = 8
    Width = 89
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
  object ColSel1: TColSel
    Left = 8
    Top = 56
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clYellow
    TabOrder = 1
    OnChange = ColSel1Change
  end
  object ColSel2: TColSel
    Left = 8
    Top = 80
    Width = 129
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clFuchsia
    TabOrder = 2
    OnChange = ColSel2Change
  end
  object NIONumColors: TNumIO
    Left = 104
    Top = 112
    Width = 57
    Height = 24
    Beep = False
    DecPlaceSep = dsDot
    FixPointDecPlaces = 2
    InputFormat = itInt
    RangeHigh = 256
    RangeLow = -1.7E308
    TabOrder = 3
    Text = '32'
    OnChange = NIONumColorsChange
  end
  object CBoxGridMode: TComboBox
    Left = 192
    Top = 24
    Width = 145
    Height = 24
    Style = csDropDownList
    ItemHeight = 16
    TabOrder = 4
    OnClick = CBoxGridModeClick
    Items.Strings = (
      'None'
      'Horizontal'
      'Vertical'
      'Both')
  end
  object CselGrid: TColSel
    Left = 344
    Top = 24
    Width = 135
    Height = 22
    ColorBarWidth = 30
    NumColors = 20
    SelColor = clTeal
    TabOrder = 5
    OnClick = CselGridClick
  end
  object RGSelect: TRadioGroup
    Left = 8
    Top = 144
    Width = 177
    Height = 185
    Caption = ' Select Gradient '
    ItemIndex = 0
    Items.Strings = (
      'Horizontal'
      'Vertical'
      'MidBandHoriz'
      'MidBandVert'
      'EllipticFull'
      'EllipticFit'
      'Radial'
      'DiagGrid'
      'Rectangle')
    TabOrder = 6
    OnClick = RGSelectClick
  end
end
