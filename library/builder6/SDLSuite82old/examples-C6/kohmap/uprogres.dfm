object FrmProgress: TFrmProgress
  Left = 684
  Top = 477
  Width = 246
  Height = 254
  Caption = 'working ....'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Meter: TMeter
    Left = 8
    Top = 8
    Width = 217
    Height = 145
    AnchorSize = 24
    AnchorCovered = True
    BkgndFillMode = bfSimple
    Caption = '%'
    ColorBakG = clWhite
    ColorCover = clSilver
    ColorScale = clNavy
    ColorScheme = csBWG
    ColorSclBkLow = clLime
    ColorSclBkNorm = 33023
    ColorSclBkHigh = clRed
    FontCaption.Charset = DEFAULT_CHARSET
    FontCaption.Color = clWindowText
    FontCaption.Height = -13
    FontCaption.Name = 'MS Sans Serif'
    FontCaption.Style = []
    FrameStyle = fsRaised
    LimWatchHighOn = True
    LimWatchLowOn = True
    LimWatchActColor = clRed
    LimWatchPsvColor = clGray
    ThresholdHigh = 1
    MeterMaxValue = 100
    MeterDecPlaces = 0
    MeterNrTicks = 3
    MeterLayout = mlCirc120
    MeterShortTicks = True
    MeterScaleLine = True
    NeedleLayout.HeadSize = 20
    NeedleLayout.HeadAngle = 30
    NeedleLayout.HeadMidLeng = 20
    NeedleLayout.Thickness = 0
    NeedleLayout.ColorBody = clLime
    NeedleLayout.ColorOutline = clNavy
    NeedleLayout.PercentNeedleLength = 100
    NeedleLayout.ShadowDx = 0
    NeedleLayout.ShadowDy = 0
    NeedleLayout.ShadowColor = clGray
    NeedleLayout.Visible = True
    NeedleLayoutSec.HeadSize = 20
    NeedleLayoutSec.HeadAngle = 30
    NeedleLayoutSec.HeadMidLeng = 20
    NeedleLayoutSec.Thickness = 0
    NeedleLayoutSec.ColorBody = clSilver
    NeedleLayoutSec.ColorOutline = clBlack
    NeedleLayoutSec.PercentNeedleLength = 100
    NeedleLayoutSec.ShadowDx = 0
    NeedleLayoutSec.ShadowDy = 0
    NeedleLayoutSec.ShadowColor = clGray
    NeedleLayoutSec.Visible = False
    RimBottom = 10
    RimTop = 8
    RimSide = 10
    ScaleBkVisible = False
    ScaleVisible = True
  end
  object BButAbort: TBitBtn
    Left = 8
    Top = 184
    Width = 217
    Height = 41
    Caption = 'Abort'
    TabOrder = 0
    OnClick = BButAbortClick
  end
  object CBShowTraining: TCheckBox
    Left = 8
    Top = 156
    Width = 105
    Height = 17
    Caption = 'show training'
    TabOrder = 1
  end
end
