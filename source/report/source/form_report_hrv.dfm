object frm_report_hrv: Tfrm_report_hrv
  Left = 0
  Top = 88
  Width = 1024
  Height = 704
  Caption = 'SphygmoCor Heart Rate Variability Report'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl_form: TPanel
    Left = 0
    Top = 0
    Width = 1016
    Height = 670
    Align = alClient
    Color = 12228238
    TabOrder = 0
    object pnl_grid: TPanel
      Left = 1
      Top = 1
      Width = 242
      Height = 668
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object pnl_assessments: TPanel
        Left = 0
        Top = 377
        Width = 242
        Height = 291
        Align = alClient
        BevelInner = bvLowered
        Color = clWhite
        TabOrder = 0
        object lbl_assessments_title: TLabel
          Left = 2
          Top = 2
          Width = 238
          Height = 22
          Align = alTop
          Caption = ' Assessment'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object grd_report: TDBGrid
          Left = 2
          Top = 24
          Width = 238
          Height = 265
          Align = alClient
          BorderStyle = bsNone
          Color = clWhite
          FixedColor = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -13
          TitleFont.Name = 'Arial'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'DATETIME'
              Title.Caption = 'Study Time'
              Width = 238
              Visible = True
            end>
        end
      end
      object pnl_study_information: TPanel
        Left = 0
        Top = 131
        Width = 242
        Height = 246
        Align = alTop
        BevelInner = bvLowered
        Color = clWhite
        TabOrder = 1
        object Label35: TLabel
          Left = 2
          Top = 6
          Width = 153
          Height = 22
          Caption = ' Study Information'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_operator_title: TLabel
          Left = 9
          Top = 34
          Width = 54
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Operator:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object lbl_operator: TLabel
          Left = 88
          Top = 34
          Width = 50
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Operator'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object lbl_hwbmi_title: TLabel
          Left = 9
          Top = 56
          Width = 125
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Height, Weight (BMI):'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object lbl_hwbmi: TLabel
          Left = 9
          Top = 75
          Width = 87
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Hgt, Wgt (BMI)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object lbl_med_title: TLabel
          Left = 9
          Top = 97
          Width = 74
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Medications:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object lbl_notes_title: TLabel
          Left = 9
          Top = 170
          Width = 38
          Height = 16
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          Caption = 'Notes:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object edt_notes: TMemo
          Left = 5
          Top = 189
          Width = 236
          Height = 48
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          TabStop = False
          BevelEdges = []
          BevelInner = bvNone
          BevelOuter = bvNone
          BorderStyle = bsNone
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Lines.Strings = (
            'Notes')
          MaxLength = 100
          ParentFont = False
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 0
          OnClick = bbtn_modifyClick
        end
        object edt_med: TMemo
          Left = 5
          Top = 116
          Width = 236
          Height = 48
          Cursor = crHandPoint
          Hint = 'Click here to modify'
          TabStop = False
          BevelEdges = []
          BevelInner = bvNone
          BevelOuter = bvNone
          BorderStyle = bsNone
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Lines.Strings = (
            'Medications')
          MaxLength = 100
          ParentFont = False
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 1
          OnClick = bbtn_modifyClick
        end
      end
      object pnl_patient_information: TPanel
        Left = 0
        Top = 0
        Width = 242
        Height = 131
        Align = alTop
        BevelInner = bvLowered
        Color = clWhite
        TabOrder = 2
        object Label36: TLabel
          Left = 2
          Top = 6
          Width = 163
          Height = 22
          Caption = ' Patient Information'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_pname: TLabel
          Left = 9
          Top = 34
          Width = 42
          Height = 18
          Caption = 'Name'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Transparent = True
        end
        object lbl_pid_title: TLabel
          Left = 9
          Top = 58
          Width = 61
          Height = 16
          Caption = 'Patient ID:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_pid: TLabel
          Left = 89
          Top = 58
          Width = 21
          Height = 16
          Caption = 'PID'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_birth_date_title: TLabel
          Left = 9
          Top = 80
          Width = 62
          Height = 16
          Caption = 'Birth Date:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_age_title: TLabel
          Left = 9
          Top = 102
          Width = 27
          Height = 16
          Caption = 'Age:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_sex_title: TLabel
          Left = 89
          Top = 102
          Width = 27
          Height = 16
          Caption = 'Sex:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_age: TLabel
          Left = 49
          Top = 102
          Width = 23
          Height = 16
          Caption = 'Age'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_birth_date: TLabel
          Left = 89
          Top = 80
          Width = 58
          Height = 16
          Caption = 'Birth Date'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
        object lbl_sex: TLabel
          Left = 129
          Top = 102
          Width = 23
          Height = 16
          Caption = 'Sex'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 9515310
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
        end
      end
    end
    object pnl_main: TPanel
      Left = 243
      Top = 1
      Width = 772
      Height = 668
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object pgctrl_reports: TPageControl
        Left = 0
        Top = 0
        Width = 772
        Height = 572
        ActivePage = tbsht_time
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        Style = tsFlatButtons
        TabHeight = 17
        TabIndex = 0
        TabOrder = 1
        OnChange = pgctrl_reportsChange
        object tbsht_time: TTabSheet
          Hint = 'TIME'
          Caption = 'Time'
          OnResize = tbsht_timeResize
          object pnl_waveform: TPanel
            Left = 0
            Top = 0
            Width = 764
            Height = 293
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 0
            object chrt_time_rtor: TChart
              Left = 0
              Top = 0
              Width = 764
              Height = 201
              Hint = 'R to R Intervals'
              BackWall.Brush.Color = clWhite
              BackWall.Color = clWhite
              BackWall.Transparent = False
              Gradient.EndColor = 16053492
              Gradient.StartColor = 11969664
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 1
              MarginRight = 2
              MarginTop = 2
              Title.Font.Color = clWhite
              Title.Font.Height = -12
              Title.Text.Strings = (
                'R to R Intervals')
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Pulse Number'
              BottomAxis.Title.Font.Color = clWhite
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'Interval (ms)'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Brush.Color = clBlack
              Zoom.Brush.Style = bsSolid
              Zoom.Pen.Color = clGray
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              object srs_rtor: TLineSeries
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = 9515310
                Title = 'R to R Interval'
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object srs_highlow_rtor: TPointSeries
                Marks.ArrowLength = 0
                Marks.Visible = False
                SeriesColor = 2956990
                ShowInLegend = False
                Title = 'HighLow RtoR'
                ClickableLine = False
                Pointer.HorizSize = 3
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 2956990
                Pointer.Style = psStar
                Pointer.VertSize = 3
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
            object chrt_ecg_report: TChart
              Left = 0
              Top = 201
              Width = 764
              Height = 92
              BackImageMode = pbmTile
              BackWall.Color = clBlack
              BackWall.Pen.Color = 12228238
              BackWall.Transparent = False
              Legend.Alignment = laBottom
              Legend.Bevel = bvRaised
              Legend.CheckBoxes = True
              Legend.Color = 12615680
              Legend.FontSeriesColor = True
              Legend.LegendStyle = lsSeries
              Legend.TopPos = 5
              Legend.Visible = False
              MarginBottom = 1
              MarginLeft = 1
              MarginRight = 1
              MarginTop = 1
              Title.Font.Charset = ANSI_CHARSET
              Title.Font.Color = clWhite
              Title.Font.Height = -12
              Title.Text.Strings = (
                'ECG Data')
              BottomAxis.Axis.Color = clTeal
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.LabelStyle = talValue
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Time (sec)'
              BottomAxis.Title.Font.Charset = ANSI_CHARSET
              BottomAxis.Title.Font.Color = clWhite
              Frame.Color = 12228238
              LeftAxis.Axis.Color = clTeal
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'ECG (Digital Units)'
              LeftAxis.Title.Font.Charset = ANSI_CHARSET
              LeftAxis.Title.Font.Color = clWhite
              LeftAxis.Title.Font.OutLine.Color = 16777088
              RightAxis.Automatic = False
              RightAxis.AutomaticMaximum = False
              RightAxis.AutomaticMinimum = False
              RightAxis.Axis.Color = clTeal
              RightAxis.Grid.Visible = False
              RightAxis.LabelsFont.Color = clAqua
              RightAxis.Maximum = 2600
              RightAxis.Minimum = 300
              RightAxis.MinorTickCount = 1
              RightAxis.Title.Font.Charset = ANSI_CHARSET
              RightAxis.Title.Font.Color = clAqua
              RightAxis.Title.Font.Height = -9
              RightAxis.Visible = False
              TopAxis.Axis.Color = clTeal
              View3D = False
              Align = alBottom
              BevelOuter = bvNone
              Color = clBlack
              UseDockManager = False
              TabOrder = 1
              PrintMargins = (
                15
                39
                15
                39)
              object srs_ecg: TFastLineSeries
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = clYellow
                Title = 'ECG'
                LinePen.Color = clYellow
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
          object pnl_analysis: TPanel
            Left = 0
            Top = 293
            Width = 764
            Height = 164
            Align = alBottom
            BevelOuter = bvNone
            TabOrder = 1
            object chrt_time_rtor_bar: TChart
              Left = 0
              Top = 0
              Width = 260
              Height = 164
              Hint = 'Histogram'
              BackWall.Brush.Color = clWhite
              BackWall.Color = clWhite
              BackWall.Gradient.EndColor = clWhite
              BackWall.Transparent = False
              Gradient.EndColor = 11969664
              Gradient.StartColor = 16053492
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 5
              MarginRight = 5
              MarginTop = 5
              Title.Font.Color = clMaroon
              Title.Font.Style = [fsBold]
              Title.Text.Strings = (
                'Histogram')
              Title.Visible = False
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.Maximum = 1800
              BottomAxis.Minimum = 400
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'RtoR (ms)'
              BottomAxis.Title.Font.Color = clWhite
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'RtoR#'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Allow = False
              Zoom.Pen.Color = clGray
              Align = alLeft
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              object srs_histogram: TAreaSeries
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = 9515310
                Title = 'R to R Intervals'
                AreaLinesPen.Color = 8404992
                DrawArea = True
                LinePen.Color = 8404992
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 9515310
                Pointer.Style = psRectangle
                Pointer.Visible = False
                Stairs = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
            object chrt_poincare: TChart
              Left = 504
              Top = 0
              Width = 260
              Height = 164
              Hint = 'Poincare Plot'
              BackWall.Brush.Color = clWhite
              BackWall.Brush.Style = bsClear
              BackWall.Color = clWhite
              BackWall.Gradient.EndColor = clWhite
              BackWall.Gradient.Visible = True
              BackWall.Transparent = False
              Gradient.EndColor = 11969664
              Gradient.StartColor = 16053492
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 5
              MarginRight = 2
              MarginTop = 5
              Title.Text.Strings = (
                'Poincare Plot')
              Title.Visible = False
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.Maximum = 1800
              BottomAxis.Minimum = 400
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'RtoRn (ms)'
              BottomAxis.Title.Font.Color = clWhite
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.LabelsFont.Height = -9
              LeftAxis.Maximum = 1800
              LeftAxis.Minimum = 400
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'R to R n + 1'
              RightAxis.Automatic = False
              RightAxis.AutomaticMaximum = False
              RightAxis.AutomaticMinimum = False
              RightAxis.Axis.Visible = False
              RightAxis.Grid.Color = 12228238
              RightAxis.LabelsFont.Color = clWhite
              RightAxis.Maximum = 1800
              RightAxis.Minimum = 400
              RightAxis.Title.Caption = 'RtoRn+1'
              RightAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Allow = False
              Align = alRight
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              object srs_poincare: TPointSeries
                Marks.ArrowLength = 0
                Marks.Visible = False
                SeriesColor = 9515310
                Title = 'Poincare'
                VertAxis = aRightAxis
                ClickableLine = False
                Pointer.HorizSize = 2
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 9515310
                Pointer.Style = psCircle
                Pointer.VertSize = 2
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
            object pnl_key_params: TPanel
              Left = 260
              Top = 0
              Width = 244
              Height = 164
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              TabOrder = 2
              object pnl_hr_title: TPanel
                Left = 0
                Top = 0
                Width = 244
                Height = 16
                Align = alTop
                BevelOuter = bvNone
                Caption = 'Heart Rate'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Verdana'
                Font.Style = []
                ParentColor = True
                ParentFont = False
                TabOrder = 0
              end
              object pnl_hr: TPanel
                Left = 0
                Top = 16
                Width = 244
                Height = 24
                Align = alTop
                BevelOuter = bvNone
                Caption = '??'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -21
                Font.Name = 'Verdana'
                Font.Style = [fsBold]
                ParentColor = True
                ParentFont = False
                TabOrder = 1
              end
              object pnl_rmssdd_title: TPanel
                Left = 0
                Top = 40
                Width = 244
                Height = 16
                Align = alTop
                BevelOuter = bvNone
                Caption = 'RMSSD'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Verdana'
                Font.Style = []
                ParentColor = True
                ParentFont = False
                TabOrder = 2
              end
              object pnl_rmssdd: TPanel
                Left = 0
                Top = 56
                Width = 244
                Height = 24
                Align = alTop
                BevelOuter = bvNone
                Caption = '??'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -21
                Font.Name = 'Verdana'
                Font.Style = [fsBold]
                ParentColor = True
                ParentFont = False
                TabOrder = 3
              end
              object pnl_hrv_index_title: TPanel
                Left = 0
                Top = 80
                Width = 244
                Height = 16
                Align = alTop
                BevelOuter = bvNone
                Caption = 'HRV Triangular Index'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Verdana'
                Font.Style = []
                ParentColor = True
                ParentFont = False
                TabOrder = 4
              end
              object pnl_hrv_index: TPanel
                Left = 0
                Top = 96
                Width = 244
                Height = 24
                Align = alTop
                BevelOuter = bvNone
                Caption = '??'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -21
                Font.Name = 'Verdana'
                Font.Style = [fsBold]
                ParentColor = True
                ParentFont = False
                TabOrder = 5
              end
              object pnl_pnn50_title: TPanel
                Left = 0
                Top = 120
                Width = 244
                Height = 16
                Align = alTop
                BevelOuter = bvNone
                Caption = 'PNN50'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Verdana'
                Font.Style = []
                ParentColor = True
                ParentFont = False
                TabOrder = 6
              end
              object pnl_pnn50: TPanel
                Left = 0
                Top = 136
                Width = 244
                Height = 26
                Align = alTop
                BevelOuter = bvNone
                Caption = '??'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -21
                Font.Name = 'Verdana'
                Font.Style = [fsBold]
                ParentColor = True
                ParentFont = False
                TabOrder = 7
              end
            end
          end
          object pnl_bottom: TPanel
            Left = 0
            Top = 457
            Width = 764
            Height = 88
            Align = alBottom
            Anchors = [akLeft, akBottom]
            BevelOuter = bvNone
            Color = 12228238
            TabOrder = 2
            OnResize = pnl_bottomResize
            object pnl_parameters: TPanel
              Left = 0
              Top = 0
              Width = 570
              Height = 88
              Align = alClient
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              object pnl_title: TPanel
                Left = 0
                Top = 0
                Width = 570
                Height = 16
                Align = alTop
                BevelOuter = bvNone
                ParentColor = True
                TabOrder = 0
                object lbl_hrv_time_params: TLabel
                  Left = 0
                  Top = 1
                  Width = 570
                  Height = 15
                  Align = alBottom
                  Alignment = taCenter
                  Caption = 'Time Parameters'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
              end
              object pnl_left: TPanel
                Left = 0
                Top = 16
                Width = 194
                Height = 72
                Align = alLeft
                BevelOuter = bvNone
                ParentColor = True
                TabOrder = 1
                object Label2: TLabel
                  Left = 13
                  Top = 6
                  Width = 31
                  Height = 14
                  Caption = 'Range'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_rtor_range: TLabel
                  Left = 70
                  Top = 6
                  Width = 67
                  Height = 15
                  Caption = 'RtoR_range'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label5: TLabel
                  Left = 13
                  Top = 21
                  Width = 44
                  Height = 14
                  Caption = 'Maximum'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object Label7: TLabel
                  Left = 13
                  Top = 36
                  Width = 40
                  Height = 14
                  Caption = 'Minimum'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_max: TLabel
                  Left = 70
                  Top = 21
                  Width = 56
                  Height = 15
                  Caption = 'Maximum'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object lbl_min: TLabel
                  Left = 70
                  Top = 36
                  Width = 52
                  Height = 15
                  Caption = 'Minimum'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label10: TLabel
                  Left = 13
                  Top = 51
                  Width = 45
                  Height = 14
                  Caption = 'Max./Min.'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_maxmin: TLabel
                  Left = 70
                  Top = 51
                  Width = 47
                  Height = 15
                  Caption = 'Max/Min'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
              end
              object pnl_middle_left: TPanel
                Left = 194
                Top = 16
                Width = 194
                Height = 72
                Align = alLeft
                BevelOuter = bvNone
                ParentColor = True
                TabOrder = 2
                object Label3: TLabel
                  Left = 2
                  Top = 21
                  Width = 94
                  Height = 14
                  Caption = 'Number of Pulses   '
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_pulses: TLabel
                  Left = 97
                  Top = 21
                  Width = 39
                  Height = 15
                  Caption = 'Pulses'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label8: TLabel
                  Left = 2
                  Top = 6
                  Width = 63
                  Height = 14
                  Caption = 'Capture Time'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_cap_time: TLabel
                  Left = 97
                  Top = 6
                  Width = 28
                  Height = 15
                  Caption = 'Time'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label12: TLabel
                  Left = 2
                  Top = 36
                  Width = 77
                  Height = 14
                  Caption = 'Rejected Pulses'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_high_low: TLabel
                  Left = 97
                  Top = 36
                  Width = 50
                  Height = 15
                  Caption = 'Rejected'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label20: TLabel
                  Left = 2
                  Top = 51
                  Width = 26
                  Height = 14
                  Caption = 'Mode'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_mode: TLabel
                  Left = 97
                  Top = 51
                  Width = 31
                  Height = 15
                  Caption = 'Mode'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
              end
              object pnl_middle_right: TPanel
                Left = 388
                Top = 16
                Width = 182
                Height = 72
                Align = alClient
                BevelOuter = bvNone
                ParentColor = True
                TabOrder = 3
                object Label6: TLabel
                  Left = 2
                  Top = 36
                  Width = 26
                  Height = 14
                  Caption = 'NN50'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_nn50: TLabel
                  Left = 105
                  Top = 36
                  Width = 30
                  Height = 15
                  Caption = 'NN50'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label13: TLabel
                  Left = 2
                  Top = 51
                  Width = 22
                  Height = 14
                  Caption = 'TINN'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_tri_index: TLabel
                  Left = 105
                  Top = 51
                  Width = 96
                  Height = 15
                  Caption = 'Triangular_Index'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label4: TLabel
                  Left = 2
                  Top = 21
                  Width = 28
                  Height = 14
                  Caption = 'SDNN'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_rtor_sd: TLabel
                  Left = 105
                  Top = 21
                  Width = 50
                  Height = 15
                  Caption = 'RtoR_SD'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object Label1: TLabel
                  Left = 2
                  Top = 6
                  Width = 26
                  Height = 14
                  Caption = 'Mean'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWhite
                  Font.Height = -11
                  Font.Name = 'Arial'
                  Font.Style = []
                  ParentFont = False
                end
                object lbl_rtor_mean: TLabel
                  Left = 105
                  Top = 6
                  Width = 66
                  Height = 15
                  Caption = 'RtoR_mean'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = 9515310
                  Font.Height = -12
                  Font.Name = 'Arial'
                  Font.Style = [fsBold]
                  ParentFont = False
                end
              end
            end
            object pnl_right: TPanel
              Left = 570
              Top = 0
              Width = 194
              Height = 88
              Align = alRight
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 1
              object Label14: TLabel
                Left = 8
                Top = 35
                Width = 80
                Height = 14
                Caption = 'No. of Segments'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -11
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object Label15: TLabel
                Left = 8
                Top = 67
                Width = 36
                Height = 14
                Caption = 'SDANN'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -11
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object Label16: TLabel
                Left = 8
                Top = 51
                Width = 57
                Height = 14
                Caption = 'SDNN Index'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -11
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_segment_length: TLabel
                Left = 100
                Top = 19
                Width = 93
                Height = 15
                Caption = 'Segment_length'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_no_segments: TLabel
                Left = 100
                Top = 35
                Width = 97
                Height = 15
                Caption = 'No_of_segments'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_sdann: TLabel
                Left = 100
                Top = 67
                Width = 40
                Height = 15
                Caption = 'SDANN'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_sdnn: TLabel
                Left = 100
                Top = 51
                Width = 32
                Height = 15
                Caption = 'SDNN'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label11: TLabel
                Left = 8
                Top = 19
                Width = 78
                Height = 14
                Caption = 'Segment Length'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -11
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object Label17: TLabel
                Left = 27
                Top = 0
                Width = 94
                Height = 15
                Caption = 'Segmented Data'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clBlack
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
            end
          end
        end
        object tbsht_frequency: TTabSheet
          Hint = 'FREQUENCY'
          Caption = 'Frequency'
          ImageIndex = 1
          object pnl_fcharts: TPanel
            Left = 0
            Top = 0
            Width = 764
            Height = 384
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 0
            OnResize = pnl_fchartsResize
            object chrt_freq_spectrum: TChart
              Left = 0
              Top = 0
              Width = 512
              Height = 384
              Hint = 'Frequency Spectrum'
              BackWall.Brush.Color = clWhite
              BackWall.Color = clWhite
              BackWall.Transparent = False
              Gradient.EndColor = 11969664
              Gradient.StartColor = 16053492
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 1
              MarginRight = 2
              MarginTop = 2
              Title.Font.Color = clWhite
              Title.Font.Height = -15
              Title.Text.Strings = (
                'Power Spectrum')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.Maximum = 0.5
              BottomAxis.Minimum = 0.01
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Frequency (Hz)'
              BottomAxis.Title.Font.Color = clWhite
              Chart3DPercent = 20
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'Power (ms'#178')'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              object srs_spectrum: TAreaSeries
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = clGray
                Title = 'Spectrum'
                AreaLinesPen.Visible = False
                Dark3D = False
                DrawArea = True
                LinePen.Visible = False
                Pointer.Draw3D = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
            object chrt_lfhf_pie: TChart
              Left = 512
              Top = 0
              Width = 252
              Height = 384
              Hint = 'Low Frequency to High Frequency Pie Chart'
              AllowPanning = pmNone
              BackWall.Brush.Color = clWhite
              BackWall.Brush.Style = bsClear
              BackWall.Color = clGray
              BackWall.Pen.Visible = False
              Gradient.EndColor = 11969664
              Gradient.StartColor = 16053492
              Legend.Alignment = laBottom
              Legend.LegendStyle = lsValues
              Legend.TextStyle = ltsLeftPercent
              MarginRight = 10
              Title.Font.Color = clWhite
              Title.Font.Height = -15
              Title.Text.Strings = (
                'Low Frequency To High Frequency Ratio')
              AxisVisible = False
              ClipPoints = False
              Frame.Visible = False
              View3DOptions.Elevation = 315
              View3DOptions.HorizOffset = 14
              View3DOptions.Orthogonal = False
              View3DOptions.Perspective = 0
              View3DOptions.Rotation = 360
              View3DOptions.VertOffset = -14
              View3DOptions.Zoom = 102
              View3DWalls = False
              Zoom.Allow = False
              Align = alRight
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              object srs_frequency_per: TPieSeries
                Marks.ArrowLength = 4
                Marks.Style = smsLabelPercent
                Marks.Visible = False
                PercentFormat = '##0.# %'
                SeriesColor = clRed
                Title = 'Frequency Percent'
                ValueFormat = '0.0'
                Circled = True
                CircleBackColor = 8453888
                ExplodeBiggest = 15
                PiePen.Color = 11969664
                PieValues.DateTime = False
                PieValues.Name = 'Pie'
                PieValues.Order = loNone
                Shadow.Color = clSilver
              end
            end
          end
          object pnl_freq_params: TPanel
            Left = 0
            Top = 384
            Width = 764
            Height = 161
            Align = alBottom
            BevelOuter = bvNone
            Color = 12228238
            TabOrder = 1
            object lbl_lf_mx_freq_title: TLabel
              Left = 26
              Top = 14
              Width = 164
              Height = 15
              Caption = 'Low Frequency Maximum (Hz)'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_lf_mx_freq: TLabel
              Left = 82
              Top = 29
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_hf_mx_freq_title: TLabel
              Left = 25
              Top = 61
              Width = 167
              Height = 15
              Caption = 'High Frequency Maximum (Hz)'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_hf_mx_freq: TLabel
              Left = 82
              Top = 77
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_lf_hf_ratio_title: TLabel
              Left = 344
              Top = 109
              Width = 65
              Height = 15
              Caption = 'LF/HF Ratio'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_lf_hf_ratio: TLabel
              Left = 350
              Top = 125
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_lf_pnorm: TLabel
              Left = 350
              Top = 29
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_hf_pnorm: TLabel
              Left = 350
              Top = 77
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_lf_pnorm_title: TLabel
              Left = 282
              Top = 14
              Width = 189
              Height = 15
              Caption = 'Low Frequency Power Normalised'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_hf_pnorm_title: TLabel
              Left = 280
              Top = 61
              Width = 192
              Height = 15
              Caption = 'High Frequency Power Normalised'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_freq_total_power_title: TLabel
              Left = 592
              Top = 109
              Width = 98
              Height = 15
              Caption = 'Total Power (ms'#178')'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_freq_total_power: TLabel
              Left = 615
              Top = 125
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_lf_power: TLabel
              Left = 615
              Top = 29
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_hf_power: TLabel
              Left = 615
              Top = 77
              Width = 52
              Height = 24
              Caption = '????'
              Font.Charset = ANSI_CHARSET
              Font.Color = 9515310
              Font.Height = -21
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_lf_power_title: TLabel
              Left = 539
              Top = 14
              Width = 205
              Height = 15
              Caption = 'Absolute Low Frequency Power (ms'#178')'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_hf_power_title: TLabel
              Left = 537
              Top = 61
              Width = 208
              Height = 15
              Caption = 'Absolute High Frequency Power (ms'#178')'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
        end
        object tbsht_clinical: TTabSheet
          Hint = 'CLINICAL'
          Caption = 'Clinical'
          ImageIndex = 2
          object pnl_clinical_graphs: TPanel
            Left = 0
            Top = 65
            Width = 764
            Height = 480
            Align = alClient
            BevelOuter = bvNone
            Caption = 
              'CLINICAL NORMALS ARE NOT VALIDATED FOR MEASUREMENTS LESS THAN 5 ' +
              'MINUTES'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object chrt_vagal_index: TChart
              Left = 0
              Top = 0
              Width = 764
              Height = 480
              Hint = 'Normal Vagal Index Chart'
              BackWall.Brush.Color = clWhite
              BackWall.Color = 16053492
              BackWall.Transparent = False
              BottomWall.Color = clSilver
              Gradient.EndColor = 16053492
              Gradient.StartColor = 11969664
              LeftWall.Color = clSilver
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 2
              MarginRight = 2
              MarginTop = 2
              RightWall.Visible = True
              Title.Font.Color = clWhite
              Title.Font.Height = -15
              Title.Text.Strings = (
                'Vagal Index Reference Range')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.Maximum = 100
              BottomAxis.Minimum = 10
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Age (Years)'
              BottomAxis.Title.Font.Color = clWhite
              Chart3DPercent = 20
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.Maximum = 60
              LeftAxis.Minimum = 5
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'RMSSD (ms)'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Allow = False
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              object srs_area_vagal_index: TAreaSeries
                Gradient.EndColor = 8421631
                Gradient.StartColor = 2956990
                Gradient.Visible = True
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = 4227327
                Title = 'VagalIndexNormals'
                DrawArea = True
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                Stairs = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object srs_point_vagal_index: TPointSeries
                Marks.Arrow.Color = clGray
                Marks.ArrowLength = 8
                Marks.Style = smsValue
                Marks.Visible = False
                SeriesColor = 9515310
                Title = 'VagalIndex'
                ClickableLine = False
                Pointer.Brush.Color = 9515310
                Pointer.Dark3D = False
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 9515310
                Pointer.Style = psDiamond
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
          object pnl_patient_details: TPanel
            Left = 0
            Top = 0
            Width = 764
            Height = 40
            Align = alTop
            BevelInner = bvLowered
            Color = clWhite
            TabOrder = 1
            object lbl_patient_title: TLabel
              Left = 5
              Top = 2
              Width = 69
              Height = 15
              Caption = 'Patient Data'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_pcode_title: TLabel
              Left = 5
              Top = 18
              Width = 74
              Height = 15
              Caption = 'Patient Code:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_pcode: TLabel
              Left = 118
              Top = 18
              Width = 43
              Height = 15
              Caption = 'PCODE'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_add_title: TLabel
              Left = 302
              Top = 2
              Width = 49
              Height = 15
              Caption = 'Address:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address1: TLabel
              Left = 376
              Top = 2
              Width = 46
              Height = 15
              Caption = 'Address'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address2: TLabel
              Left = 376
              Top = 18
              Width = 21
              Height = 15
              Caption = 'add'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address3: TLabel
              Left = 540
              Top = 18
              Width = 21
              Height = 15
              Caption = 'add'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object pnl_study_details: TPanel
            Left = 0
            Top = 40
            Width = 764
            Height = 25
            Align = alTop
            BevelInner = bvLowered
            Color = clWhite
            TabOrder = 2
            object lbl_study_title: TLabel
              Left = 5
              Top = 2
              Width = 61
              Height = 15
              Caption = 'Study Data'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_date: TLabel
              Left = 118
              Top = 2
              Width = 26
              Height = 15
              Caption = 'Date'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_time: TLabel
              Left = 196
              Top = 2
              Width = 28
              Height = 15
              Caption = 'Time'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_pressure_title: TLabel
              Left = 302
              Top = 2
              Width = 64
              Height = 15
              Cursor = crHandPoint
              Hint = 'Click here to modify'
              Caption = 'Sp/Dp (Mp):'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              OnClick = bbtn_modifyClick
            end
            object lblSpDpMp: TLabel
              Left = 376
              Top = 2
              Width = 61
              Height = 15
              Cursor = crHandPoint
              Hint = 'Click here to modify'
              Caption = 'Sp/Dp (Mp)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              OnClick = bbtn_modifyClick
            end
          end
        end
        object tbsht_manoeuvre: TTabSheet
          Hint = 'MANOEUVRE'
          Caption = 'Manoeuvre'
          ImageIndex = 3
          object pnl_manoeuvre_bottom: TPanel
            Left = 0
            Top = 408
            Width = 764
            Height = 137
            Align = alBottom
            BevelOuter = bvNone
            Color = 12228238
            TabOrder = 0
            object pnl_manoeuvre: TPanel
              Left = 0
              Top = 0
              Width = 216
              Height = 137
              Align = alLeft
              BevelOuter = bvNone
              ParentColor = True
              TabOrder = 0
              object lbl_low_title: TLabel
                Left = 10
                Top = 21
                Width = 102
                Height = 17
                Caption = 'Manoeuvre Low'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_low_manoeuvre: TLabel
                Left = 137
                Top = 21
                Width = 29
                Height = 18
                Caption = 'Low'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_high_title: TLabel
                Left = 10
                Top = 6
                Width = 104
                Height = 17
                Caption = 'Manoeuvre High'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_high_manoeuvre: TLabel
                Left = 137
                Top = 6
                Width = 33
                Height = 18
                Caption = 'High'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_ratio_title: TLabel
                Left = 10
                Top = 36
                Width = 109
                Height = 17
                Caption = 'Manoeuvre Ratio'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_ratio_manoeuvre: TLabel
                Left = 137
                Top = 36
                Width = 37
                Height = 18
                Caption = 'Ratio'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -15
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label24: TLabel
                Left = 10
                Top = 69
                Width = 109
                Height = 15
                Caption = 'Number of Pulses   '
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_pulses_manoeuvre: TLabel
                Left = 137
                Top = 69
                Width = 39
                Height = 15
                Caption = 'Pulses'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label26: TLabel
                Left = 10
                Top = 54
                Width = 75
                Height = 15
                Caption = 'Capture Time'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_cap_time_manoeuvre: TLabel
                Left = 137
                Top = 54
                Width = 28
                Height = 15
                Caption = 'Time'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label9: TLabel
                Left = 10
                Top = 85
                Width = 106
                Height = 15
                Caption = 'Average Heart Rate'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_hr_manoeuvre: TLabel
                Left = 137
                Top = 85
                Width = 64
                Height = 15
                Caption = 'Heart_Rate'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label19: TLabel
                Left = 10
                Top = 100
                Width = 67
                Height = 15
                Caption = 'Mean R to R'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object Label21: TLabel
                Left = 10
                Top = 116
                Width = 74
                Height = 15
                Caption = 'R to R Range'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWhite
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = []
                ParentFont = False
              end
              object lbl_rtor_mean_manoeuvre: TLabel
                Left = 137
                Top = 100
                Width = 66
                Height = 15
                Caption = 'RtoR_mean'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lbl_rtor_range_manoeuvre: TLabel
                Left = 137
                Top = 116
                Width = 67
                Height = 15
                Caption = 'RtoR_range'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = 9515310
                Font.Height = -12
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
            end
            object chrt_manoeuvre_normals: TChart
              Left = 216
              Top = 0
              Width = 548
              Height = 137
              Hint = 'Normals Chart'
              BackWall.Brush.Color = clWhite
              BackWall.Color = 16053492
              BackWall.Transparent = False
              BottomWall.Color = clSilver
              Gradient.EndColor = 16053492
              Gradient.StartColor = 11969664
              LeftWall.Color = clSilver
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 2
              MarginRight = 5
              MarginTop = 2
              RightWall.Visible = True
              Title.Font.Color = clWhite
              Title.Font.Height = -12
              Title.Text.Strings = (
                'Manoeuvre Ratio Reference Range')
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.Maximum = 100
              BottomAxis.Minimum = 10
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Age (Years)'
              BottomAxis.Title.Font.Color = clWhite
              Chart3DPercent = 20
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.Maximum = 2.5
              LeftAxis.Minimum = 1
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'Manoeuvre Ratio'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Allow = False
              Zoom.Brush.Color = clBlack
              Zoom.Brush.Style = bsSolid
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              object srs_manoeuvre_ratio_normals: TAreaSeries
                Gradient.Direction = gdBottomTop
                Gradient.EndColor = 2956990
                Gradient.StartColor = 8421631
                Gradient.Visible = True
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = 4227327
                Title = 'ManoeuvreNormals'
                DrawArea = True
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object srs_manoeuvre_ratio: TPointSeries
                Marks.Arrow.Color = clGray
                Marks.ArrowLength = 8
                Marks.Style = smsValue
                Marks.Visible = False
                SeriesColor = 9515310
                Title = 'Manoeuvre'
                ClickableLine = False
                Pointer.Dark3D = False
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 9515310
                Pointer.Style = psDiamond
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
          object pnl_manoeuvre_waveform: TPanel
            Left = 0
            Top = 65
            Width = 764
            Height = 343
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 1
            object chrt_manoeuvre: TChart
              Left = 0
              Top = 0
              Width = 764
              Height = 251
              Hint = 'Heart Rate Chart'
              BackWall.Brush.Color = clWhite
              BackWall.Color = clWhite
              BackWall.Transparent = False
              Gradient.EndColor = 16053492
              Gradient.StartColor = 11969664
              Legend.Visible = False
              MarginBottom = 2
              MarginLeft = 1
              MarginRight = 2
              MarginTop = 2
              Title.Font.Color = clWhite
              Title.Font.Height = -12
              Title.Text.Strings = (
                'Manoeuvre')
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Time (seconds)'
              BottomAxis.Title.Font.Color = clWhite
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'Heart Rate (bpm)'
              LeftAxis.Title.Font.Color = clWhite
              View3D = False
              Zoom.Brush.Color = clBlack
              Zoom.Brush.Style = bsSolid
              Zoom.Pen.Color = clGray
              Align = alClient
              BevelOuter = bvNone
              Color = 12228238
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              object srs_hr_manoeuvre: TLineSeries
                ColorEachLine = False
                Marks.Arrow.Color = clGray
                Marks.ArrowLength = 8
                Marks.BackColor = 14811135
                Marks.Color = 14811135
                Marks.ShadowSize = 0
                Marks.Visible = True
                SeriesColor = 9515310
                Title = 'Heart Rate'
                BeforeDrawValues = srs_hr_manoeuvreBeforeDrawValues
                OnGetMarkText = srs_hr_manoeuvreGetMarkText
                Dark3D = False
                Pointer.Brush.Color = 9515310
                Pointer.HorizSize = 2
                Pointer.InflateMargins = True
                Pointer.Pen.Color = 9515310
                Pointer.Style = psRectangle
                Pointer.VertSize = 2
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
              object srs_manoeuvre_highlow: TPointSeries
                Marks.ArrowLength = 0
                Marks.Visible = False
                SeriesColor = 2956990
                Title = 'HighLow RtoR'
                ClickableLine = False
                Pointer.HorizSize = 2
                Pointer.InflateMargins = True
                Pointer.Style = psStar
                Pointer.VertSize = 2
                Pointer.Visible = True
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
            object chrt_manoeuvre_ecg: TChart
              Left = 0
              Top = 251
              Width = 764
              Height = 92
              BackImageMode = pbmTile
              BackWall.Color = clBlack
              BackWall.Pen.Color = 12228238
              BackWall.Transparent = False
              Legend.Alignment = laBottom
              Legend.Bevel = bvRaised
              Legend.CheckBoxes = True
              Legend.Color = 12615680
              Legend.FontSeriesColor = True
              Legend.LegendStyle = lsSeries
              Legend.TopPos = 5
              Legend.Visible = False
              MarginBottom = 1
              MarginLeft = 1
              MarginRight = 1
              MarginTop = 1
              Title.Font.Charset = ANSI_CHARSET
              Title.Font.Color = clWhite
              Title.Font.Height = -12
              Title.Text.Strings = (
                'ECG Data')
              BottomAxis.Axis.Color = clTeal
              BottomAxis.Axis.Visible = False
              BottomAxis.Grid.Color = 12228238
              BottomAxis.LabelsFont.Color = clWhite
              BottomAxis.LabelStyle = talValue
              BottomAxis.MinorTickCount = 1
              BottomAxis.Title.Caption = 'Time (sec)'
              BottomAxis.Title.Font.Charset = ANSI_CHARSET
              BottomAxis.Title.Font.Color = clWhite
              BottomAxis.Title.Font.Height = -12
              Frame.Color = 12228238
              LeftAxis.Axis.Color = clTeal
              LeftAxis.Axis.Visible = False
              LeftAxis.Grid.Color = 12228238
              LeftAxis.LabelsFont.Color = clWhite
              LeftAxis.MinorTickCount = 1
              LeftAxis.Title.Caption = 'ECG (Digital Units)'
              LeftAxis.Title.Font.Charset = ANSI_CHARSET
              LeftAxis.Title.Font.Color = clWhite
              LeftAxis.Title.Font.OutLine.Color = 16777088
              RightAxis.Automatic = False
              RightAxis.AutomaticMaximum = False
              RightAxis.AutomaticMinimum = False
              RightAxis.Axis.Color = clTeal
              RightAxis.Grid.Visible = False
              RightAxis.LabelsFont.Color = clAqua
              RightAxis.Maximum = 2600
              RightAxis.Minimum = 300
              RightAxis.MinorTickCount = 1
              RightAxis.Title.Font.Charset = ANSI_CHARSET
              RightAxis.Title.Font.Color = clAqua
              RightAxis.Title.Font.Height = -9
              RightAxis.Visible = False
              TopAxis.Axis.Color = clTeal
              View3D = False
              Zoom.Pen.Color = clGray
              Align = alBottom
              BevelOuter = bvNone
              Color = clBlack
              UseDockManager = False
              TabOrder = 1
              PrintMargins = (
                15
                39
                15
                39)
              object srs_manoeuvre_ecg: TFastLineSeries
                Marks.ArrowLength = 8
                Marks.Visible = False
                SeriesColor = clYellow
                Title = 'ECG'
                LinePen.Color = clYellow
                XValues.DateTime = False
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.DateTime = False
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
          object pnl_patient_manoeuvre: TPanel
            Left = 0
            Top = 0
            Width = 764
            Height = 40
            Align = alTop
            BevelInner = bvLowered
            Color = clWhite
            TabOrder = 2
            object lbl_patient_title_manoeuvre: TLabel
              Left = 5
              Top = 2
              Width = 69
              Height = 15
              Caption = 'Patient Data'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_pcode_title_manoeuvre: TLabel
              Left = 5
              Top = 18
              Width = 74
              Height = 15
              Caption = 'Patient Code:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_pcode_manoeuvre: TLabel
              Left = 118
              Top = 18
              Width = 43
              Height = 15
              Caption = 'PCODE'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_add_title_manoeuvre: TLabel
              Left = 302
              Top = 2
              Width = 49
              Height = 15
              Caption = 'Address:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address1_manoeuvre: TLabel
              Left = 376
              Top = 2
              Width = 46
              Height = 15
              Caption = 'Address'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address2_manoeuvre: TLabel
              Left = 376
              Top = 18
              Width = 21
              Height = 15
              Caption = 'add'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
            object lbl_address3_manoeuvre: TLabel
              Left = 540
              Top = 18
              Width = 21
              Height = 15
              Caption = 'add'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
            end
          end
          object pnl_study_manoeuvre: TPanel
            Left = 0
            Top = 40
            Width = 764
            Height = 25
            Align = alTop
            BevelInner = bvLowered
            Color = clWhite
            TabOrder = 3
            object lbl_study_title_manoeuvre: TLabel
              Left = 5
              Top = 2
              Width = 61
              Height = 15
              Caption = 'Study Data'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_date_manoeuvre: TLabel
              Left = 118
              Top = 2
              Width = 26
              Height = 15
              Caption = 'Date'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_time_manoeuvre: TLabel
              Left = 196
              Top = 2
              Width = 28
              Height = 15
              Caption = 'Time'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object lbl_pressure_title_manoeuvre: TLabel
              Left = 302
              Top = 2
              Width = 64
              Height = 15
              Cursor = crHandPoint
              Hint = 'Click here to modify'
              Caption = 'Sp/Dp (Mp):'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              OnClick = bbtn_modifyClick
            end
            object lblSpDpMp_manoeuvre: TLabel
              Left = 376
              Top = 2
              Width = 61
              Height = 15
              Cursor = crHandPoint
              Hint = 'Click here to modify'
              Caption = 'Sp/Dp (Mp)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = 9515310
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              OnClick = bbtn_modifyClick
            end
          end
        end
      end
      object pnl_status_bar: TPanel
        Left = 0
        Top = 572
        Width = 772
        Height = 48
        Align = alBottom
        BevelOuter = bvNone
        Color = 12228238
        TabOrder = 2
        Visible = False
        DesignSize = (
          772
          48)
        object lbl_message2: TLabel
          Left = 15
          Top = 2
          Width = 79
          Height = 19
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Message 2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
        object lbl_message1: TLabel
          Left = 327
          Top = 2
          Width = 79
          Height = 19
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Message 1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          Transparent = True
        end
        object lbl_message3: TLabel
          Left = 327
          Top = 26
          Width = 64
          Height = 16
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Message 3'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
        object lbl_message4: TLabel
          Left = 15
          Top = 26
          Width = 64
          Height = 16
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Message 4'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
      end
      object pnl_report_buttons: TPanel
        Left = 0
        Top = 620
        Width = 772
        Height = 48
        Align = alBottom
        BevelOuter = bvNone
        Color = 12228238
        TabOrder = 0
        object bbtn_ecg: TSpeedButton
          Left = 208
          Top = 7
          Width = 119
          Height = 34
          Caption = 'Show &ECG'
          Font.Charset = ANSI_CHARSET
          Font.Color = 9515310
          Font.Height = -20
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_ecgClick
        end
        object bbtn_modify: TSpeedButton
          Left = 334
          Top = 7
          Width = 101
          Height = 34
          Hint = 'Modify the Current Report'
          Caption = 'M&odify'
          Font.Charset = ANSI_CHARSET
          Font.Color = 9515310
          Font.Height = -20
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_modifyClick
        end
        object bbtn_delete: TSpeedButton
          Left = 442
          Top = 7
          Width = 101
          Height = 34
          Hint = 'Delete the Current Report'
          Caption = '&Delete'
          Font.Charset = ANSI_CHARSET
          Font.Color = 9515310
          Font.Height = -20
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_deleteClick
        end
        object bbtn_export: TSpeedButton
          Left = 550
          Top = 7
          Width = 101
          Height = 34
          Hint = 'Right-Click for Export Options'
          Caption = 'E&xport'
          Font.Charset = ANSI_CHARSET
          Font.Color = 9515310
          Font.Height = -20
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          PopupMenu = ppmnu_report
          ShowHint = True
          OnClick = mnu_graphicClick
        end
        object bbtn_print: TSpeedButton
          Left = 658
          Top = 7
          Width = 101
          Height = 34
          Hint = 'Print the Current Report'
          Caption = 'Pri&nt'
          Font.Charset = ANSI_CHARSET
          Font.Color = 9515310
          Font.Height = -20
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          OnClick = bbtn_printClick
        end
      end
    end
  end
  object ppmnu_report: TPopupMenu
    Left = 122
    Top = 222
    object mnu_text: TMenuItem
      Caption = 'As T&ext'
      OnClick = mnu_textClick
    end
    object mnu_graphic: TMenuItem
      Caption = 'As &Graphic'
      Hint = 
        'Export the HRV report in graphics format for documents and email' +
        's'
      OnClick = mnu_graphicClick
    end
    object mnu_all: TMenuItem
      Caption = '&All'
      Hint = 'Export the HRV report in multiple formats'
      OnClick = mnu_allClick
    end
  end
end
