object frm_export_database: Tfrm_export_database
  Left = 445
  Top = 200
  Width = 636
  Height = 485
  Caption = 'SphygmoCor Export To Database'
  Color = 12228238
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl_select: TPanel
    Left = 0
    Top = 0
    Width = 628
    Height = 65
    Align = alTop
    BevelInner = bvLowered
    Color = clWhite
    TabOrder = 0
    object pnl_start: TPanel
      Left = 2
      Top = 2
      Width = 232
      Height = 61
      Align = alLeft
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 54
        Height = 15
        Caption = 'Start &Date'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 9515310
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object dtpk_start: TDateTimePicker
        Left = 8
        Top = 24
        Width = 148
        Height = 23
        CalAlignment = dtaLeft
        Date = 37557
        Format = 'dd MMMM yyyy'
        Time = 37557
        DateFormat = dfLong
        DateMode = dmUpDown
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        Kind = dtkDate
        ParseInput = False
        ParentFont = False
        TabOrder = 0
        OnChange = dtpk_startChange
      end
    end
    object pnl_end: TPanel
      Left = 234
      Top = 2
      Width = 392
      Height = 61
      Align = alClient
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 1
      object Label2: TLabel
        Left = 8
        Top = 8
        Width = 51
        Height = 15
        Caption = '&End Date'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 9515310
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object bbtn_get_studies: TSpeedButton
        Left = 224
        Top = 24
        Width = 91
        Height = 24
        Caption = '&Get Studies'
        Font.Charset = ANSI_CHARSET
        Font.Color = 9515310
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = bbtn_get_studiesClick
      end
      object dtpk_end: TDateTimePicker
        Left = 8
        Top = 24
        Width = 148
        Height = 23
        CalAlignment = dtaLeft
        Date = 37557
        Format = 'dd MMMM yyyy'
        Time = 37557
        DateFormat = dfLong
        DateMode = dmUpDown
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        Kind = dtkDate
        ParseInput = False
        ParentFont = False
        TabOrder = 0
        OnChange = dtpk_endChange
      end
    end
  end
  object pnl_status: TPanel
    Left = 0
    Top = 408
    Width = 628
    Height = 43
    Align = alBottom
    ParentColor = True
    TabOrder = 4
    Visible = False
    object status_bar: TStatusBar
      Left = 1
      Top = 1
      Width = 626
      Height = 41
      Align = alClient
      Panels = <
        item
          Text = 'Patient Info'
          Width = 400
        end
        item
          Text = '1/10'
          Width = 50
        end>
      ParentColor = True
      SimplePanel = False
    end
    object progress_bar: TProgressBar
      Left = 192
      Top = 24
      Width = 200
      Height = 13
      Min = 0
      Max = 100
      TabOrder = 2
    end
    object bbtn_cancel_export: TBitBtn
      Left = 448
      Top = 16
      Width = 107
      Height = 25
      Cancel = True
      Caption = 'Cancel E&xport'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 9515310
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = bbtn_cancel_exportClick
      NumGlyphs = 2
    end
  end
  object pnl_records: TPanel
    Left = 0
    Top = 65
    Width = 628
    Height = 177
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object pnl_studies: TPanel
      Left = 0
      Top = 0
      Width = 273
      Height = 177
      Align = alLeft
      BevelOuter = bvNone
      Color = 9515310
      TabOrder = 0
      object Label4: TLabel
        Left = 8
        Top = 8
        Width = 148
        Height = 15
        Caption = 'Available Studies for Export'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object lstbx_studies: TListBox
        Left = 8
        Top = 32
        Width = 258
        Height = 290
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 9515310
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        MultiSelect = True
        ParentFont = False
        TabOrder = 0
        OnClick = lstbx_studiesClick
      end
    end
    object pnl_exports: TPanel
      Left = 355
      Top = 0
      Width = 273
      Height = 177
      Align = alRight
      BevelOuter = bvNone
      Color = 9515310
      TabOrder = 2
      object Label5: TLabel
        Left = 8
        Top = 8
        Width = 147
        Height = 15
        Caption = 'Selected Studies for Export'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object lstbx_exports: TListBox
        Left = 8
        Top = 32
        Width = 258
        Height = 290
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 9515310
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        MultiSelect = True
        ParentFont = False
        TabOrder = 0
        OnClick = lstbx_exportsClick
      end
    end
    object pnl_centre: TPanel
      Left = 273
      Top = 0
      Width = 82
      Height = 177
      Align = alClient
      BevelInner = bvLowered
      Color = 9515310
      TabOrder = 1
      object Label7: TLabel
        Left = 2
        Top = 2
        Width = 78
        Height = 15
        Align = alTop
        Alignment = taCenter
        Caption = 'Studies'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object lbl_total_studies: TLabel
        Left = 2
        Top = 17
        Width = 78
        Height = 15
        Align = alTop
        Alignment = taCenter
        Caption = '??'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object spbtn_add: TSpeedButton
        Left = 26
        Top = 88
        Width = 23
        Height = 22
        Enabled = False
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333333333333333333333333333333333333333333333333333333333
          3333333333333333333333333333333333333333333FF3333333333333003333
          3333333333773FF3333333333309003333333333337F773FF333333333099900
          33333FFFFF7F33773FF30000000999990033777777733333773F099999999999
          99007FFFFFFF33333F7700000009999900337777777F333F7733333333099900
          33333333337F3F77333333333309003333333333337F77333333333333003333
          3333333333773333333333333333333333333333333333333333333333333333
          3333333333333333333333333333333333333333333333333333}
        NumGlyphs = 2
        OnClick = spbtn_addClick
      end
      object spbtn_addall: TSpeedButton
        Left = 26
        Top = 120
        Width = 23
        Height = 22
        Enabled = False
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          33333FF3333333333333447333333333333377FFF33333333333744473333333
          333337773FF3333333333444447333333333373F773FF3333333334444447333
          33333373F3773FF3333333744444447333333337F333773FF333333444444444
          733333373F3333773FF333334444444444733FFF7FFFFFFF77FF999999999999
          999977777777777733773333CCCCCCCCCC3333337333333F7733333CCCCCCCCC
          33333337F3333F773333333CCCCCCC3333333337333F7733333333CCCCCC3333
          333333733F77333333333CCCCC333333333337FF7733333333333CCC33333333
          33333777333333333333CC333333333333337733333333333333}
        NumGlyphs = 2
        OnClick = spbtn_addallClick
      end
      object spbtn_delete: TSpeedButton
        Left = 26
        Top = 192
        Width = 23
        Height = 22
        Enabled = False
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333333333333333333333333333333333333333333333333333333333
          3333333333333FF3333333333333003333333333333F77F33333333333009033
          333333333F7737F333333333009990333333333F773337FFFFFF330099999000
          00003F773333377777770099999999999990773FF33333FFFFF7330099999000
          000033773FF33777777733330099903333333333773FF7F33333333333009033
          33333333337737F3333333333333003333333333333377333333333333333333
          3333333333333333333333333333333333333333333333333333333333333333
          3333333333333333333333333333333333333333333333333333}
        NumGlyphs = 2
        OnClick = spbtn_deleteClick
      end
      object spbtn_deleteall: TSpeedButton
        Left = 26
        Top = 224
        Width = 23
        Height = 22
        Enabled = False
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          333333333333333333FF3333333333333744333333333333F773333333333337
          44473333333333F777F3333333333744444333333333F7733733333333374444
          4433333333F77333733333333744444447333333F7733337F333333744444444
          433333F77333333733333744444444443333377FFFFFFF7FFFFF999999999999
          9999733777777777777333CCCCCCCCCC33333773FF333373F3333333CCCCCCCC
          C333333773FF3337F333333333CCCCCCC33333333773FF373F3333333333CCCC
          CC333333333773FF73F33333333333CCCCC3333333333773F7F3333333333333
          CCC333333333333777FF33333333333333CC3333333333333773}
        NumGlyphs = 2
        OnClick = spbtn_deleteallClick
      end
      object lbl_progress_text: TLabel
        Left = 2
        Top = 32
        Width = 78
        Height = 15
        Align = alTop
        Alignment = taCenter
        Caption = '1 of ??'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
    end
  end
  object pnl_buttons: TPanel
    Left = 0
    Top = 242
    Width = 628
    Height = 64
    Align = alBottom
    BevelOuter = bvNone
    Color = 9515310
    TabOrder = 2
    DesignSize = (
      628
      64)
    object bbtn_export_all: TSpeedButton
      Left = 304
      Top = 24
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Export &All'
      Font.Charset = ANSI_CHARSET
      Font.Color = 9515310
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = bbtn_export_allClick
    end
    object bbtn_export_selected: TSpeedButton
      Left = 408
      Top = 24
      Width = 99
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Export &Selected'
      Font.Charset = ANSI_CHARSET
      Font.Color = 9515310
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = bbtn_export_selectedClick
    end
    object bbtn_cancel: TSpeedButton
      Left = 536
      Top = 24
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '&Cancel'
      Font.Charset = ANSI_CHARSET
      Font.Color = 9515310
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = bbtn_cancelClick
    end
  end
  object pnl_warnings: TPanel
    Left = 0
    Top = 306
    Width = 628
    Height = 102
    Align = alBottom
    BevelOuter = bvNone
    Color = 9515310
    TabOrder = 3
    Visible = False
    DesignSize = (
      628
      102)
    object Label3: TLabel
      Left = 8
      Top = 8
      Width = 88
      Height = 15
      Caption = 'Error Messages'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object BitBtn1: TSpeedButton
      Left = 528
      Top = 160
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '&Close'
      Font.Charset = ANSI_CHARSET
      Font.Color = 9515310
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = BitBtn1Click
    end
    object memMsg: TMemo
      Left = 8
      Top = 32
      Width = 401
      Height = 169
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Lines.Strings = (
        'memMsg')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
end
