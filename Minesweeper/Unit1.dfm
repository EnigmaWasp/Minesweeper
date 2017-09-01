object Form1: TForm1
  Left = 362
  Top = 158
  BorderStyle = bsToolWindow
  Caption = 'Сапер'
  ClientHeight = 340
  ClientWidth = 380
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PoleCanvas: TPaintBox
    Left = 30
    Top = 5
    Width = 320
    Height = 320
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnMouseDown = PoleCanvasMouseDown
    OnPaint = PoleCanvasPaint
  end
  object MainMenu1: TMainMenu
    Left = 5
    Top = 5
    object N4: TMenuItem
      Caption = 'Файл'
      object N5: TMenuItem
        Caption = 'Выход'
        OnClick = N5Click
      end
    end
    object N1: TMenuItem
      Caption = 'Сложность'
      object N2: TMenuItem
        Caption = 'Легко'
        OnClick = N2Click
      end
      object N6: TMenuItem
        Caption = 'Средне'
        OnClick = N6Click
      end
      object N3: TMenuItem
        Caption = 'Сложно'
        OnClick = N3Click
      end
    end
  end
end
