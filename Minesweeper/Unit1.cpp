//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
class Cell
{
public:
int BombCol;
bool Opened;
bool Checked;
bool Mined;
};

Cell Pole[100][100];
Graphics::TBitmap*BombPicture;
int BombKol,BombLeft;
TForm1 *Form1;
int Razmer;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Razmer=16;
BombPicture=new Graphics::TBitmap();
BombPicture->LoadFromFile("Bomb.bmp");
BombPicture->Transparent=true;
for(int j=0;j<Razmer;j++)
        for(int i=0;i<Razmer;i++)
                {
                Pole[i][j].Opened=false;
                Pole[i][j].BombCol=0;
                Pole[i][j].Checked=false;
                Pole[i][j].Mined=false;
                }
BombKol=40;
BombLeft=BombKol;
RandomizeBomb();
UpdateCaption();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::DrawCell(int x, int y)
{
PoleCanvas->Canvas->Pen->Color=clGray;


if(!Pole[x][y].Opened)
{
PoleCanvas->Canvas->Brush->Color=clSilver;
PoleCanvas->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
if(Pole[x][y].Checked)
{                               //Флажок
PoleCanvas->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
PoleCanvas->Canvas->Brush->Color=clRed;
PoleCanvas->Canvas->Rectangle(x*20+5,y*20+5,x*20+15,y*20+10);
PoleCanvas->Canvas->Rectangle(x*20+13,y*20+5,x*20+15,y*20+17);
}
}else
{
PoleCanvas->Canvas->Brush->Color=RGB(130,130,130);
PoleCanvas->Canvas->Rectangle(x*20,y*20,x*20+20,y*20+20);
if(Pole[x][y].Mined)
        {
        PoleCanvas->Canvas->Draw(x*20,y*20,BombPicture);
        }else
        if(Pole[x][y].BombCol>0)
        {
        PoleCanvas->Canvas->TextOutA(x*20+4,y*20+0,IntToStr(Pole[x][y].BombCol));
        }
}

}
void __fastcall TForm1::PoleCanvasPaint(TObject *Sender)
{
PoleCanvas->Canvas->Font->Size=13;
PoleCanvas->Canvas->Font->Color=clGreen;
for(int j=0;j<Razmer;j++)
        for(int i=0;i<Razmer;i++)
        {
        DrawCell(i,j);
        }
}
//---------------------------------------------------------------------------


TForm1::RandomizeBomb()
{
randomize();
        TList*list=new TList();
        for(int i=0;i<Razmer*(long)Razmer;i++)list->Add((void*)i);
        for(int i=0;i<BombKol;i++)
                {
                int pos=random(list->Count);
                int mesto=(int)list->Items[pos];
                    list->Delete(pos);
                int y=mesto/Razmer;
                int x=mesto-(y*Razmer);
                Pole[x][y].Mined=true;
                }
CountBombsNearCells();
return 1;
}

TForm1::CountBombsNearCells()
{int num=0;
       for(int j=1;j<Razmer-1;j++)
        for(int i=1;i<Razmer-1;i++,num=0)
                {
                if(Pole[i+1][j].Mined)num++;  if(Pole[i-1][j].Mined)num++;
                if(Pole[i][j+1].Mined)num++;  if(Pole[i][j-1].Mined)num++;
                if(Pole[i+1][j+1].Mined)num++;if(Pole[i+1][j-1].Mined)num++;
                if(Pole[i-1][j-1].Mined)num++;//Центр
                if(Pole[i-1][j+1].Mined)num++;
                Pole[i][j].BombCol=num;
                }
         for(int i=1;i<Razmer-1;i++,num=0)
                {
                if(Pole[0][i-1].Mined)num++;if(Pole[0][i+1].Mined)num++;
                if(Pole[1][i-1].Mined)num++;if(Pole[1][i+1].Mined)num++;
                if(Pole[1][i].Mined)num++;
                Pole[0][i].BombCol=num;      //Левый край
                }
         for(int i=1;i<Razmer-1;i++,num=0)
                {
                if(Pole[Razmer-1][i-1].Mined)num++;if(Pole[Razmer-1][i+1].Mined)num++;
                if(Pole[Razmer-2][i-1].Mined)num++;if(Pole[Razmer-2][i+1].Mined)num++;
                if(Pole[Razmer-2][i].Mined)num++;   //Правый край
                Pole[Razmer-1][i].BombCol=num;
                }
         for(int i=1;i<Razmer-1;i++,num=0)
                {
                if(Pole[i-1][0].Mined)num++;if(Pole[i+1][0].Mined)num++;
                if(Pole[i+1][1].Mined)num++;if(Pole[i][1].Mined)num++;
                if(Pole[i-1][1].Mined)num++; //Верх
                Pole[i][0].BombCol=num;
                }
         for(int i=1;i<Razmer-1;i++,num=0)
                {
                if(Pole[i-1][Razmer-1].Mined)num++;if(Pole[i+1][Razmer-1].Mined)num++;
                if(Pole[i+1][Razmer-2].Mined)num++;if(Pole[i][Razmer-2].Mined)num++;
                if(Pole[i-1][Razmer-2].Mined)num++;
                Pole[i][Razmer-1].BombCol=num;      //Низ
                }
         num=0;
         if(Pole[0][1].Mined)num++;
         if(Pole[1][0].Mined)num++;
         if(Pole[1][1].Mined)num++;
         Pole[0][0].BombCol=num;

         num=0;
         if(Pole[0][Razmer-2].Mined)num++;
         if(Pole[1][Razmer-2].Mined)num++;
         if(Pole[1][Razmer-1].Mined)num++;
         Pole[0][Razmer-1].BombCol=num;

         num=0;
         if(Pole[Razmer-2][0].Mined)num++;
         if(Pole[Razmer-2][1].Mined)num++;
         if(Pole[Razmer-1][1].Mined)num++;
         Pole[Razmer-1][0].BombCol=num;

         num=0;
         if(Pole[Razmer-1][Razmer-2].Mined)num++;
         if(Pole[Razmer-2][Razmer-2].Mined)num++;
         if(Pole[Razmer-2][Razmer-1].Mined)num++;
         Pole[Razmer-1][Razmer-1].BombCol=num;

       return 1;
}
void __fastcall TForm1::PoleCanvasMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int XPos=X/20;
int YPos=Y/20;
if(Button==mbLeft)
        {
        if(Pole[XPos][YPos].BombCol==0)
                {
                CheckRekursively(XPos,YPos);
                Repaint();
                }
        Pole[XPos][YPos].Opened=true;
        DrawCell(XPos,YPos);
        if(Pole[XPos][YPos].Mined)
                {
                Sleep(500);
                DrawAll();
                ShowMessage("Вы проиграли");
                New(Razmer,BombKol);
                }
        }
if(Button==mbRight)
        {
        if(!Pole[XPos][YPos].Opened)
        {
        if(Pole[XPos][YPos].Checked)
                {
                Pole[XPos][YPos].Checked=false;
                BombLeft++;
                }else
                {
                Pole[XPos][YPos].Checked=true;
                BombLeft--;
                }
        DrawCell(XPos,YPos);
        }
        }
UpdateCaption();
if(CheckWin())
        {
        ShowMessage("Победа!!!!!!!!");
        New(Razmer,BombKol);
        }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::New(int R, int BC)
{
Razmer=R;

for(int j=0;j<Razmer;j++)
        for(int i=0;i<Razmer;i++)
                {
                Pole[i][j].Opened=false;
                Pole[i][j].BombCol=0;
                Pole[i][j].Checked=false;
                Pole[i][j].Mined=false;
                }
BombKol=BC;
BombLeft=BombKol;
RandomizeBomb();
PoleCanvas->Width=20*Razmer;
PoleCanvas->Height=20*Razmer;
Form1->ClientWidth=20*Razmer+60;
Form1->ClientHeight=20*Razmer+20;
UpdateCaption();
Repaint();
}
void __fastcall TForm1::N5Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
New(9,10);
Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
New(30,99);
Repaint();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DrawAll()
{
PoleCanvas->Canvas->Font->Size=13;
PoleCanvas->Canvas->Font->Color=clGreen;
for(int j=0;j<Razmer;j++)
        for(int i=0;i<Razmer;i++)
        {
        Pole[i][j].Opened=true;
        DrawCell(i,j);
        }
}

void __fastcall TForm1::UpdateCaption()
{
        Caption="Сапер         Бомб="+IntToStr(BombLeft)+"    ";
}

bool __fastcall TForm1::CheckWin()
{
        for(int j=0;j<Razmer;j++)
                for(int i=0;i<Razmer;i++)
                        {
                        if((Pole[i][j].Mined)&&(!Pole[i][j].Checked))
                        return false;
                        }
return true;
}
void __fastcall TForm1::N6Click(TObject *Sender)
{
New(16,40);
Repaint();

}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckRekursively(int x, int y)
{
        if((x>Razmer-1)||(x<0)||(y>Razmer-1)||(y<0))return;

if(!Pole[x][y].Opened)
        {
        Pole[x][y].Opened=true;
        if(Pole[x][y].BombCol==0)
                {
                CheckRekursively(x+1,y);
                CheckRekursively(x-1,y);
                CheckRekursively(x,y+1);
                CheckRekursively(x,y-1);

                CheckRekursively(x+1,y+1);
                CheckRekursively(x-1,y-1);
                CheckRekursively(x-1,y+1);
                CheckRekursively(x+1,y-1);
                }
        }
}