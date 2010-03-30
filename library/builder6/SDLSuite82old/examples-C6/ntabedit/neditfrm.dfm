object Form1: TForm1
  Left = 284
  Top = 171
  Width = 677
  Height = 540
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 669
    Height = 41
    Align = alTop
    TabOrder = 0
    object SBExit: TSpeedButton
      Left = 8
      Top = 6
      Width = 81
      Height = 29
      Hint = 'Exit'
      Caption = 'Exit'
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
      OnClick = SBExitClick
    end
    object SBInput: TSpeedButton
      Left = 96
      Top = 6
      Width = 81
      Height = 29
      AllowAllUp = True
      GroupIndex = 99
      Caption = 'Edit'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000010000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000000
        000033333377777777773333330FFFFFFFF03FF3FF7FF33F3FF700300000FF0F
        00F077F777773F737737E00BFBFB0FFFFFF07773333F7F3333F7E0BFBF000FFF
        F0F077F3337773F3F737E0FBFBFBF0F00FF077F3333FF7F77F37E0BFBF00000B
        0FF077F3337777737337E0FBFBFBFBF0FFF077F33FFFFFF73337E0BF0000000F
        FFF077FF777777733FF7000BFB00B0FF00F07773FF77373377373330000B0FFF
        FFF03337777373333FF7333330B0FFFF00003333373733FF777733330B0FF00F
        0FF03333737F37737F373330B00FFFFF0F033337F77F33337F733309030FFFFF
        00333377737FFFFF773333303300000003333337337777777333}
      NumGlyphs = 2
      OnClick = SBInputClick
    end
    object SBImport: TSpeedButton
      Left = 184
      Top = 6
      Width = 81
      Height = 29
      Caption = 'Import'
      Glyph.Data = {
        72010000424D7201000000000000760000002800000015000000150000000100
        040000000000FC00000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        888888888DDD8888888888888888888886EE888888888880008888888EFE8888
        88888007F088888882B38888888007FFF7088888833388888007FFFFFF088888
        8FFF888880F9999FFF70888886668888807F999FFFF088888BBB88888809999F
        FFF708888E8E888888999F9FFFFF08888CEC88888999FFFFFF00708888888888
        89907FFF000FF0888CCC888899880F000FFFF708822288899888070FFFFFFF08
        80108889888880F00FFF700880808899888880F00F700888800088988888880F
        7008888883338898888888000888888880008888888888888888888888888888
        88888888888888888606888888888888888888888222}
      OnClick = SBImportClick
    end
    object SBRandFill: TSpeedButton
      Left = 368
      Top = 6
      Width = 81
      Height = 29
      Caption = 'Random Fill'
      OnClick = SBRandFillClick
    end
    object SBColAtt: TSpeedButton
      Left = 584
      Top = 6
      Width = 33
      Height = 29
      AllowAllUp = True
      GroupIndex = 99
      Down = True
      Caption = 'C'
      OnClick = SBColAttClick
    end
    object SBRowAtt: TSpeedButton
      Left = 624
      Top = 6
      Width = 33
      Height = 29
      AllowAllUp = True
      GroupIndex = 98
      Down = True
      Caption = 'R'
      OnClick = SBRowAttClick
    end
    object SBExport: TSpeedButton
      Left = 272
      Top = 6
      Width = 81
      Height = 29
      Caption = 'Export'
      Glyph.Data = {
        72010000424D7201000000000000760000002800000015000000150000000100
        040000000000FC00000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        888888888EAE888888888888888888888CCC8888888888800088888886268888
        88888007F08888888C5C8888888007FFF7088888819188888007FFF0FF088888
        8332888880FF0C0FFF7088888FBF8888807CCFF000F088888000888888CCFF0F
        0FF708888BB988888CC7F000FFFF08888E0E88888CC0FF0FFF0070888CCC8888
        CC807FFF000FF0888FEB8888CC880F000FFFF7088CCC888CCC88070FFFFFFF08
        8622888CCC8880F00FFF70088ED68CCCCCCC80F00F70088883B388CCCCC8880F
        700888888233888CCC888800088888888FFF8888C88888888888888880008888
        888888888888888889BB888888888888888888888E8E}
      OnClick = SBExportClick
    end
    object SBAutoSize: TSpeedButton
      Left = 456
      Top = 6
      Width = 81
      Height = 29
      Caption = 'Autosize'
      OnClick = SBAutoSizeClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 487
    Width = 669
    Height = 25
    Align = alBottom
    Alignment = taLeftJustify
    BorderStyle = bsSingle
    Caption = '  use right mouse button to activate the pop-up menu '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object NTabEd1: TNTabEd
    Left = 0
    Top = 41
    Width = 669
    Height = 446
    Align = alClient
    AutoAdvance = True
    AttribRowVisible = True
    AttribColVisible = True
    ColorBackground = 15329769
    ColorFixed = 13419703
    ColorNormal = 8192
    ColorSelected = clWhite
    ColorMarkedA = clRed
    ColorMarkedB = clBlue
    ColorMarkedBoth = 13369531
    DefaultColWidth = 50
    DefaultRowHeight = 20
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    NrOfColumns = 7
    NrOfRows = 20
    NumWidth = 1
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing]
    OnChangeSetup = NTabEd1ChangeSetup
    ColWidths = (
      80
      32
      45
      43
      40
      39
      39
      39
      39)
    RowHeights = (
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20)
  end
  object OpenDialog1: TOpenDialog
    Filter = 'ASC Format Files|*.asc'
    Left = 512
    Top = 104
  end
  object SaveDialog1: TSaveDialog
    Filter = 'ASC Format Files|*.asc'
    Left = 512
    Top = 144
  end
end
