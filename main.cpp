#include<iostream>
#include<graphics.h>
#include<windows.h>
#include<ctime>
#include "p_path.h"
#include<mmsystem.h>
#include<vector>
#include<stack>

using namespace std;

int n,nb[4]={0},ny[4]={0},b[4]={0},y[4]={0};
int nr[4]={0},r[4]={0};
int ng[4]={0},g[4]={0};
int play=0;
POINT cursorPosition;
int mx,my;


struct player
{
    char color;
    struct positions pos[4];
    int score=0;
};

struct player pl[4];

// function's declaration77
int  first_page();
int  select_players();
void initialize_positions();
void board();
void reset_dice();
void display_dice(int n);
void display_diceimg(int n);
void get_mouse();
int check_click_area(int p_x,int p_y,int dist);
int mouse_pos(int p_x,int p_y,int dist);
void open_blue_tocken();
void move_blue_tocken();
void open_yellow_tocken();
void move_yellow_tocken();
void move_green_tocken();
void move_red_tocken();
void roll_dice();
void cut_tocken(int p);
void backto_positions(int m ,int x);
void winner();


int main()
{

    initwindow(1300,700,"LUDO GAME");
    int p=1;
    set_blue_path();
    set_yellow_path();
    set_red_path();
    set_green_path();
    initialize_positions();
    /*first_page();
    delay(3000);
    cleardevice();*/
    while(play==0)
    play=select_players();
    PlaySound(TEXT("click.wav"),NULL,SND_SYNC);
    delay(500);
    board();
    while(p)
    {
        if(p==4 && play <=4)
        {
            readimagefile("blue.jpg",1000,150,1030,180);
            roll_dice();
            if(n==6)
            {
                    move_blue_tocken();
                    p=4;
            }
            else if(b[0]==1 || b[1]==1 || b[2]==1 || b[3]==1)
            {
                 move_blue_tocken();
                 p=1;
            }
            else
            {
                p=1;
            }
        }
        else if(p==1 && play>=1)
        {
            readimagefile("yellow.jpg",1000,150,1030,180);
            roll_dice();
            if(n==6)
            {
                move_yellow_tocken();
                p--;
            }
            else if(y[0]==1 || y[1]==1 || y[2]==1 || y[3]==1)
            {
                 move_yellow_tocken();
            }
            p++;
        }
        else if(p==3 && play >=3)
        {
            readimagefile("red.jpg",1000,150,1030,180);
            roll_dice();
            if(n==6)
            {
                move_red_tocken();
                p=3;
            }
            else if(r[0]==1 || r[1]==1 || r[2]==1 || r[3]==1)
            {
                 move_red_tocken();
            }
            if(play==3 && n!=6)
            {
                p=1;
            }
            else if(n!=6)
            p++;

        }
        else if(p==2  && play >=2)
        {
            readimagefile("green.jpg",1000,150,1030,180);
            roll_dice();
            if(n==6)
            {
                move_green_tocken();
                p=2;
            }
            else if(g[0]==1 || g[1]==1 || g[2]==1 || g[3]==1)
            {
                 move_green_tocken();

            }
            if(play==2 && n!=6)
            {
                p=1;
            }
            else if(n!=6)
                p++;

        }
        winner();
    }
    getch();
    return 0;
}

//Function's defination.
int  first_page()
{
    readimagefile("NEW GAME.jpg",500,100,700,200);
    readimagefile("CONTINUE.jpg",500,250,700,350);
    readimagefile("ABOUT.jpg",500,400,700,500);
    if(check_click_area(500,100,100))
        return 1;
    else if (check_click_area(500,250,100))
        return 2;
    else if (check_click_area(500,400,100))
        return 3;


}

void winner()
{
    if(nb[0]+nb[1]+nb[2]+nb[3]==224)
        outtextxy(1000,800,"Blue is first");
    else if(ny[0]+ny[1]+ny[2]+ny[3]==224)
        outtextxy(1000,800,"Yellow is first");
    else if(nr[0]+nr[1]+nr[2]+nr[3]==224)
        outtextxy(1000,800,"Red is first");
    else if(ng[0]+ng[1]+ng[2]+ng[3]==224)
        outtextxy(1000,800,"green is first");

}

int  select_players()
{
    int r=0;
    readimagefile("2 PLAYERS.jpg",500,100,700,200);
    readimagefile("3 PLAYERS.jpg",500,250,700,350);
    readimagefile("4 PLAYERS.jpg",500,400,700,500);
    while(r==0)
    {
        get_mouse();
        if(check_click_area(500,100,100))
        {
                r=2;
        }
        else  if(check_click_area(500,250,100))
                {

                r=3;
                }
        else if(check_click_area(500,400,100))
            {
            r=4;
            }
    }
    return r;


}

void initialize_positions()
{
    pl[0].pos[0].x=200;
    pl[0].pos[0].y=100;
    pl[0].pos[1].x=100;
    pl[0].pos[1].y=100;
    pl[0].pos[2].x=100;
    pl[0].pos[2].y=200;
    pl[0].pos[3].x=200;
    pl[0].pos[3].y=200;
    pl[1].pos[0].x=200;
    pl[1].pos[0].y=500;
    pl[1].pos[1].x=100;
    pl[1].pos[1].y=500;
    pl[1].pos[2].x=100;
    pl[1].pos[2].y=600;
    pl[1].pos[3].x=200;
    pl[1].pos[3].y=600;
    pl[2].pos[0].x=490;
    pl[2].pos[0].y=100;
    pl[2].pos[1].x=590;
    pl[2].pos[1].y=100;
    pl[2].pos[2].x=490;
    pl[2].pos[2].y=200;
    pl[2].pos[3].x=590;
    pl[2].pos[3].y=200;
    pl[3].pos[0].x=490;
    pl[3].pos[0].y=500;
    pl[3].pos[1].x=590;
    pl[3].pos[1].y=500;
    pl[3].pos[2].x=490;
    pl[3].pos[2].y=600;
    pl[3].pos[3].x=590;
    pl[3].pos[3].y=600;

}

void backto_positions(int m ,int x)
{
    while(nb[x]>0 || ny[x]>0|| nr[x]>0 || ng[x]>0)
    {
        if(m==0)
        {
            nb[x]--;
            pl[0].pos[x].x=blue_path[nb[x]].x;
            pl[0].pos[x].y=blue_path[nb[x]].y;
        }
        else if(m==1)
        {
            ny[x]--;
            pl[1].pos[x].x=yellow_path[ny[x]].x;
            pl[1].pos[x].y=yellow_path[ny[x]].y;

        }
        else if(m==2)
        {
            nr[x]--;
            pl[2].pos[x].x=red_path[nr[x]].x;
            pl[2].pos[x].y=red_path[nr[x]].y;
        }
        else if(m==3)
        {
            ng[x]--;
            pl[3].pos[x].x=green_path[ng[x]].x;
            pl[3].pos[x].y=green_path[ng[x]].y;
        }
          board();
    }
}

void reset_positions(int m ,int x)
{
    if(x==0 && m==0)
    {
    pl[0].pos[0].x=200;
    pl[0].pos[0].y=100;
    nb[0]=0;b[0]=0;

    }
    else if(m==0 && x==1)
    {
    pl[0].pos[1].x=100;
    pl[0].pos[1].y=100;
    nb[1]=0;b[1]=0;
    }
    else if(m==0 && x==2)
    {
    pl[0].pos[2].x=100;
    pl[0].pos[2].y=200;
    nb[2]=0;b[2]=0;
    }
    else if(m==0 && x==3)
    {
    pl[0].pos[3].x=200;
    pl[0].pos[3].y=200;
    nb[3]=0;b[3]=0;
    }
    else if(m==1 && x==0)
    {
    pl[1].pos[0].x=200;
    pl[1].pos[0].y=500;
    ny[0]=0;y[0]=0;

    }
    else if(m==1 && x==1)
    {
         pl[1].pos[1].x=100;
    pl[1].pos[1].y=500;
    ny[1]=0;y[1]=0;
    }
    else if(m==1 && x==2)
    {
            pl[1].pos[2].x=100;
    pl[1].pos[2].y=600;
    ny[2]=0;y[2]=0;
    }
   else if(m==1 && x==3)
   {
       pl[1].pos[3].x=200;
    pl[1].pos[3].y=600;
    ny[3]=0;y[3]=0;
   }
   else if(m==2 && x==0)
   {
        pl[2].pos[0].x=490;
    pl[2].pos[0].y=100;
    nr[0]=0;r[0]=0;
   }
else if(m==2 && x==1)
{
    pl[2].pos[1].x=590;
    pl[2].pos[1].y=100;
    nr[1]=0;r[1]=0;
}
    else if(m==2 && x==2)
    {
        pl[2].pos[2].x=490;
    pl[2].pos[2].y=200;
    nr[2]=0;r[2]=0;
    }
    else if(m==2 && x==3)
    {
        pl[2].pos[3].x=590;
    pl[2].pos[3].y=200;
    nr[3]=0;r[3]=0;
    }
    else if(m==3 && x==0)
    {
    pl[3].pos[0].x=490;
    pl[3].pos[0].y=500;
    ng[0]=0;g[0]=0;
    }
    else if(m==3 && x==1)
    {
    pl[3].pos[1].x=590;
    pl[3].pos[1].y=500;
    ng[1]=0;g[1]=0;
    }
    else if(m==3 && x==2)
    {
        pl[3].pos[2].x=490;
    pl[3].pos[2].y=600;
    ng[2]=0;g[2]=0;
    }
   else if(m==3 && x==3)
   {
       pl[3].pos[3].x=590;
    pl[3].pos[3].y=600;
    ng[3]=0;g[3]=0;
   }

}

void board()
{
      readimagefile("Ludo_board.jpg",10,10,700,700);
      if(play==4)
      {
      readimagefile("blue.jpg",pl[0].pos[0].x,pl[0].pos[0].y,pl[0].pos[0].x+30,pl[0].pos[0].y+30);
      readimagefile("blue.jpg",pl[0].pos[1].x,pl[0].pos[1].y,pl[0].pos[1].x+30,pl[0].pos[1].y+30);
      readimagefile("blue.jpg",pl[0].pos[2].x,pl[0].pos[2].y,pl[0].pos[2].x+30,pl[0].pos[2].y+30);
      readimagefile("blue.jpg",pl[0].pos[3].x,pl[0].pos[3].y,pl[0].pos[3].x+30,pl[0].pos[3].y+30);
      }
      if(play>=1)
      {
      readimagefile("yellow.jpg",pl[1].pos[0].x,pl[1].pos[0].y,pl[1].pos[0].x+30,pl[1].pos[0].y+30);
      readimagefile("yellow.jpg",pl[1].pos[1].x,pl[1].pos[1].y,pl[1].pos[1].x+30,pl[1].pos[1].y+30);
      readimagefile("yellow.jpg",pl[1].pos[2].x,pl[1].pos[2].y,pl[1].pos[2].x+30,pl[1].pos[2].y+30);
      readimagefile("yellow.jpg",pl[1].pos[3].x,pl[1].pos[3].y,pl[1].pos[3].x+30,pl[1].pos[3].y+30);
      }
      if(play>=3)
      {
      readimagefile("red.jpg",pl[2].pos[0].x,pl[2].pos[0].y,pl[2].pos[0].x+30,pl[2].pos[0].y+30);
      readimagefile("red.jpg",pl[2].pos[1].x,pl[2].pos[1].y,pl[2].pos[1].x+30,pl[2].pos[1].y+30);
      readimagefile("red.jpg",pl[2].pos[2].x,pl[2].pos[2].y,pl[2].pos[2].x+30,pl[2].pos[2].y+30);
      readimagefile("red.jpg",pl[2].pos[3].x,pl[2].pos[3].y,pl[2].pos[3].x+30,pl[2].pos[3].y+30);
      }
      if(play>=2)
      {
          readimagefile("green.jpg",pl[3].pos[0].x,pl[3].pos[0].y,pl[3].pos[0].x+30,pl[3].pos[0].y+30);
      readimagefile("green.jpg",pl[3].pos[1].x,pl[3].pos[1].y,pl[3].pos[1].x+30,pl[3].pos[1].y+30);
      readimagefile("green.jpg",pl[3].pos[2].x,pl[3].pos[2].y,pl[3].pos[2].x+30,pl[3].pos[2].y+30);
      readimagefile("green.jpg",pl[3].pos[3].x,pl[3].pos[3].y,pl[3].pos[3].x+30,pl[3].pos[3].y+30);
      }
      readimagefile("back.jpg",900,50,1200,500);
      outtextxy(1050,150,"Chance");
     // outtextxy(1000,250,"EXIT");
      outtextxy(1000,300,"Roll Dice:");
      readimagefile("d5.jpg",1000,350,1100,450);
      //readimagefile("red.jpg",490,100,520,130);
     // readimagefile("blue.jpg",255+45,295-45,255+30+45,325-45);

}

void reset_dice()
{
    readimagefile("d2.jpg",1000,350,1100,450);
}

void display_dice(int n)
{
    switch(n)
    {
        case 1:readimagefile("1.jpg",1000,350,1100,450);
               break;
        case 2:readimagefile("2.jpg",1000,350,1100,450);
               break;
        case 3:readimagefile("3.jpg",1000,350,1100,450);
               break;
        case 4:readimagefile("4.jpg",1000,350,1100,450);
               break;
        case 5:readimagefile("5.jpg",1000,350,1100,450);
               break;
        case 6:readimagefile("6.jpg",1000,350,1100,450);
               break;
        default:readimagefile("6.jpg",1000,350,1100,450);
                break;
    }
}

void display_diceimg(int n)
{
    switch(n)
    {
        case 1:readimagefile("d1.jpg",1000,350,1100,450);
               break;
        case 2:readimagefile("d2.jpg",1000,350,1100,450);
               break;
        case 3:readimagefile("d3.jpg",1000,350,1100,450);
               break;
        case 4:readimagefile("d4.jpg",1000,350,1100,450);
               break;
        case 5:readimagefile("d5.jpg",1000,350,1100,450);
               break;
        case 6:readimagefile("d6.jpg",1000,350,1100,450);
               break;
        case 7:readimagefile("d7.jpg",1000,350,1100,450);
               break;
        default:readimagefile("d7.jpg",1000,350,1100,450);
                break;
    }
}


void get_mouse()
{
    GetCursorPos(&cursorPosition);
    mx=cursorPosition.x;
    my=cursorPosition.y;
}

int check_click_area(int p_x,int p_y,int dist)
{
        if(GetAsyncKeyState(VK_LBUTTON)&& mx>p_x && mx<p_x+dist+5 && my>p_y+15 && my<p_y+dist+15)
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

int mouse_pos(int p_x,int p_y,int dist)
{
        if(mx>p_x && mx<p_x+dist+5 && my>p_y+15 && my<p_y+dist+15)
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

void move_blue_tocken()
{
    int c=0;
    while(c==0)
    {
        GetCursorPos(&cursorPosition);
        mx=cursorPosition.x;
        my=cursorPosition.y;
        if(check_click_area(pl[0].pos[0].x,pl[0].pos[0].y,30) && b[0]==0 && n==6)
        {
            c=1;

            pl[0].pos[0].x=blue_path[0].x;
            pl[0].pos[0].y=blue_path[0].y;
            b[0]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[0].pos[1].x,pl[0].pos[1].y,30) && b[1]==0 && n==6)
        {
            c=1;

            pl[0].pos[1].x=blue_path[0].x;
            pl[0].pos[1].y=blue_path[0].y;
            b[1]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[0].pos[2].x,pl[0].pos[2].y,30) && b[2]==0 && n==6)
        {
            c=1;

            pl[0].pos[2].x=blue_path[0].x;
            pl[0].pos[2].y=blue_path[0].y;
            b[2]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[0].pos[3].x,pl[0].pos[3].y,30) && b[3]==0 && n==6)
        {
            c=1;

            pl[0].pos[3].x=blue_path[0].x;
            pl[0].pos[3].y=blue_path[0].y;
            b[3]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[0].pos[0].x,pl[0].pos[0].y,30) && b[0]==1 && nb[0]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nb[0]=nb[0]+1;
                pl[0].pos[0].x=blue_path[nb[0]].x;
                pl[0].pos[0].y=blue_path[nb[0]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
        else if(check_click_area(pl[0].pos[1].x,pl[0].pos[1].y,30) && b[1]==1 && nb[1]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nb[1]=nb[1]+1;
                pl[0].pos[1].x=blue_path[nb[1]].x;
                pl[0].pos[1].y=blue_path[nb[1]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
        else if(check_click_area(pl[0].pos[2].x,pl[0].pos[2].y,30) && b[2]==1 && nb[2]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nb[2]=nb[2]+1;
                pl[0].pos[2].x=blue_path[nb[2]].x;
                pl[0].pos[2].y=blue_path[nb[2]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
        else if(check_click_area(pl[0].pos[3].x,pl[0].pos[3].y,30) && b[3]==1 && nb[3]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nb[3]=nb[3]+1;
                pl[0].pos[3].x=blue_path[nb[3]].x;
                pl[0].pos[3].y=blue_path[nb[3]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
    }
    cut_tocken(0);
}

void move_green_tocken()
{
    int c=0;
    while(c==0)
    {
        GetCursorPos(&cursorPosition);
        mx=cursorPosition.x;
        my=cursorPosition.y;
        if(check_click_area(pl[3].pos[0].x,pl[3].pos[0].y,30) && g[0]==0 && n==6)
        {
            c=1;

            pl[3].pos[0].x=green_path[0].x;
            pl[3].pos[0].y=green_path[0].y;
            g[0]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[3].pos[1].x,pl[3].pos[1].y,30) && g[1]==0 && n==6)
        {
            c=1;

            pl[3].pos[1].x=green_path[0].x;
            pl[3].pos[1].y=green_path[0].y;
            g[1]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[3].pos[2].x,pl[3].pos[2].y,30) && g[2]==0 && n==6)
        {
            c=1;

            pl[3].pos[2].x=green_path[0].x;
            pl[3].pos[2].y=green_path[0].y;
            g[2]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[3].pos[3].x,pl[3].pos[3].y,30) && g[3]==0 && n==6)
        {
            c=1;

            pl[3].pos[3].x=green_path[0].x;
            pl[3].pos[3].y=green_path[0].y;
            g[3]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[3].pos[0].x,pl[3].pos[0].y,30) && g[0]==1 && ng[0]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ng[0]=ng[0]+1;
                pl[3].pos[0].x=green_path[ng[0]].x;
                pl[3].pos[0].y=green_path[ng[0]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[3].pos[1].x,pl[3].pos[1].y,30) && g[1]==1 && ng[1]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ng[1]=ng[1]+1;
                pl[3].pos[1].x=green_path[ng[1]].x;
                pl[3].pos[1].y=green_path[ng[1]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[3].pos[2].x,pl[3].pos[2].y,30) && g[2]==1 && ng[2]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ng[2]=ng[2]+1;
                pl[3].pos[2].x=green_path[ng[2]].x;
                pl[3].pos[2].y=green_path[ng[2]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[3].pos[3].x,pl[3].pos[3].y,30) && g[3]==1 && ng[3]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ng[3]=ng[3]+1;
                pl[3].pos[3].x=green_path[ng[3]].x;
                pl[3].pos[3].y=green_path[ng[3]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
    }
    cut_tocken(3);
}



void move_yellow_tocken()
{
    int c=0;
     while(c==0)
    {
        GetCursorPos(&cursorPosition);
        mx=cursorPosition.x;
        my=cursorPosition.y;
        if(check_click_area(pl[1].pos[0].x,pl[1].pos[0].y,30) && y[0]==0 && n==6)
        {
            c=1;

            pl[1].pos[0].x=yellow_path[0].x;
            pl[1].pos[0].y=yellow_path[0].y;
            y[0]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[1].pos[1].x,pl[1].pos[1].y,30) && y[1]==0 && n==6)
        {
            c=1;

            pl[1].pos[1].x=yellow_path[0].x;
            pl[1].pos[1].y=yellow_path[0].y;
            y[1]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[1].pos[2].x,pl[1].pos[2].y,30) && y[2]==0 && n==6)
        {
            c=1;

            pl[1].pos[2].x=yellow_path[0].x;
            pl[1].pos[2].y=yellow_path[0].y;
            y[2]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[1].pos[3].x,pl[1].pos[3].y,30) && y[3]==0 && n==6)
        {
            c=1;

            pl[1].pos[3].x=yellow_path[0].x;
            pl[1].pos[3].y=yellow_path[0].y;
            y[3]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[1].pos[0].x,pl[1].pos[0].y,30) && y[0]==1 && ny[0]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ny[0]=ny[0]+1;
                pl[1].pos[0].x=yellow_path[ny[0]].x;
                pl[1].pos[0].y=yellow_path[ny[0]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
        else if(check_click_area(pl[1].pos[1].x,pl[1].pos[1].y,30) && y[1]==1 && ny[1]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ny[1]=ny[1]+1;
                pl[1].pos[1].x=yellow_path[ny[1]].x;
                pl[1].pos[1].y=yellow_path[ny[1]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }

        }
        else if(check_click_area(pl[1].pos[2].x,pl[1].pos[2].y,30) && y[2]==1 && ny[2]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ny[2]=ny[2]+1;
                pl[1].pos[2].x=yellow_path[ny[2]].x;
                pl[1].pos[2].y=yellow_path[ny[2]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[1].pos[3].x,pl[1].pos[3].y,30) && y[3]==1 && ny[3]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                ny[3]=ny[3]+1;
                pl[1].pos[3].x=yellow_path[ny[3]].x;
                pl[1].pos[3].y=yellow_path[ny[3]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
    }
    cut_tocken(1);
}

void move_red_tocken()
{
    int c=0;
    while(c==0)
    {
        GetCursorPos(&cursorPosition);
        mx=cursorPosition.x;
        my=cursorPosition.y;
        if(check_click_area(pl[2].pos[0].x,pl[2].pos[0].y,30) && r[0]==0 && n==6)
        {
            c=1;

            pl[2].pos[0].x=red_path[0].x;
            pl[2].pos[0].y=red_path[0].y;
            r[0]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[2].pos[1].x,pl[2].pos[1].y,30) && r[1]==0 && n==6)
        {
            c=1;

            pl[2].pos[1].x=red_path[0].x;
            pl[2].pos[1].y=red_path[0].y;
            r[1]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[2].pos[2].x,pl[2].pos[2].y,30) && r[2]==0 && n==6)
        {
            c=1;

            pl[2].pos[2].x=red_path[0].x;
            pl[2].pos[2].y=red_path[0].y;
            r[2]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[2].pos[3].x,pl[2].pos[3].y,30) && r[3]==0 && n==6)
        {
            c=1;

            pl[2].pos[3].x=red_path[0].x;
            pl[2].pos[3].y=red_path[0].y;
            r[3]=1;
            board();
            PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
        }
        else if(check_click_area(pl[2].pos[0].x,pl[2].pos[0].y,30) && r[0]==1 && nr[0]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nr[0]=nr[0]+1;
                pl[2].pos[0].x=red_path[nr[0]].x;
                pl[2].pos[0].y=red_path[nr[0]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[2].pos[1].x,pl[2].pos[1].y,30) && r[1]==1 && nr[1]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nr[1]=nr[1]+1;
                pl[2].pos[1].x=red_path[nr[1]].x;
                pl[2].pos[1].y=red_path[nr[1]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[2].pos[2].x,pl[2].pos[2].y,30) && r[2]==1 && nr[2]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nr[2]=nr[2]+1;
                pl[2].pos[2].x=red_path[nr[2]].x;
                pl[2].pos[2].y=red_path[nr[2]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
        else if(check_click_area(pl[2].pos[3].x,pl[2].pos[3].y,30) && r[3]==1 && nr[3]+n<57)
        {
            c=1;

            for(int i=1;i<=n;i++)
            {
                nr[3]=nr[3]+1;
                pl[2].pos[3].x=red_path[nr[3]].x;
                pl[2].pos[3].y=red_path[nr[3]].y;
                board();
                PlaySound(TEXT("token.wav"),NULL,SND_SYNC);
            }
        }
    }
    cut_tocken(2);
}

void roll_dice()
{
    int c=0;
    while(c==0)
    {
        get_mouse();
        if(check_click_area(1000,350,100))
        {
            for(int i=1;i<=7;i++)
            {
                delay(20);
                display_diceimg(i);
            }
            srand(time(NULL));
            n=rand()%6+1;
            display_dice(n);
            PlaySound(TEXT("diceroll.wav"),NULL,SND_SYNC);
            c=1;
        }

    }
}


void cut_tocken(int p)
{
    for(int i=0;i<4;i++)
    {
            for(int k=0;k<=3;k++)
                if(k!=p)
        for(int j=0;j<=3;j++)
        {
            if(pl[p].pos[i].x==pl[k].pos[j].x && pl[p].pos[i].y==pl[k].pos[j].y)
            {
                //backto_positions(k,j);
                reset_positions(k,j);
                board();
            }
        }
    }
}
