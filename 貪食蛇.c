#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void snake(int *ch,int h,int x,int y,int arr[43][22],char site[43][22]);//控制蛇的長度
void feedcheck(int *feed,int *h,int *fx,int *fy,int x,int y,char site[43][22]);//生產食物 
void gameovercheck(int *gameover,int path,int x,int y,char site[43][22]);//檢查遊戲是否結束 
void tab(int *speed,int h);//記分板 
void gamereset(int *x,int *y,int *path,int *speed,int *h,int *ch
,int *feed,int *gameover,int arr[43][22],char site[43][22]);
void control(int *keys,int *x,int *y,int *path,int h);//控制蛇的方向
void sitesetANDoutput(int x,int y,char site[43][22]);//場地設置 
void gotoxy(int x, int y);


int main(void){
	char site[43][22];//場地
	int arr[43][22]={0};
	int x=6,y=3;//座標變數
	int fx,fy;//食物的位置 
	int path=0;//控制蛇的方向
	int speed=150;//速度
	int h=1;//蛇的長度 
	int ch=1;//當吃到食物時 及時修正蛇的長度用的變數 
	int feed=0;//檢查有沒有食物 0=沒有 1=有 
	int keys;
	int gameover=0;//遊戲結束的判定 
	 
	sitesetANDoutput(x,y,site);
	
	srand(time(NULL));
	
	while(gameover==0){
        while(1){
        	tab(&speed,h);
        	control(&keys,&x,&y,&path,h);
        	gameovercheck(&gameover,path,x,y,site);
        	snake(&ch,h,x,y,arr,site);
        	feedcheck(&feed,&h,&fx,&fy,x,y,site);
        	if(gameover==1){
        		break;
        	}//end if
        	Sleep(speed);
       	}//end while
       	gamereset(&x,&y,&path,&speed,&h,&ch,&feed,&gameover
,arr,site);
    }//end while
	return 0;
}

void snake(int *ch,int h,int x,int y,int arr[43][22],char site[43][22]){//控制蛇的長度 
	if(site[x][y]!='#'){
		site[x][y]='B';
		arr[x][y]=h;
		gotoxy(x,y);
		printf("▉");
	}//end if
	
	for(x=0;x<43;x++) 
		for(y=0;y<22;y++)
			if(*ch!=h && site[x][y]=='B' &&arr[x][y]!=h)
				arr[x][y]++;
	*ch=h;

	for(x=0;x<43;x++){
		for(y=0;y<22;y++){
			if(arr[x][y]==0 && site[x][y]=='B'){
				site[x][y]='A';
				gotoxy(x,y);
				printf(" ");
			}//end if
			if(arr[x][y]!=0 && arr[x][y]==h-1){
				gotoxy(x,y);
				printf("▉");
			}//end if
			if(arr[x][y]!=0 && site[x][y]=='B')
				arr[x][y]--;
		}//end for
	}//end for


}//end function

void feedcheck(int *feed,int *h,int *fx,int *fy,int x,int y,char site[43][22]){//生產食物 

	if(*feed==1){
		if(site[*fx][*fy]=='B'){
			*h=*h+1;
			*feed=0;
		}//end if
	}//end if

	if(*feed==0){
		do{
			x=rand()%40+1;
			y=rand()%20+1;
			*fx=x;
			*fy=y;
		}while(*fx%2!=0 || site[*fx][*fy]=='B');//end do while

		site[x][y]='C';
		gotoxy(x,y);
		printf("●");
		*feed=1;
	}//end if
}//end function

void gameovercheck(int *gameover,int path,int x,int y,char site[43][22]){//檢查遊戲是否結束 
	if(site[x][y]=='#' || site[x][y]=='B' && path!=0)
		*gameover=1;
}//end function

void gamereset(int *x,int *y,int *path,int *speed,int *h,int *ch
,int *feed,int *gameover,int arr[43][22],char site[43][22]){
    int re;
    int rx,ry;
    while(*gameover==1){
            gotoxy(17,10);
        	printf("GAMEOVER!");
        	gotoxy(14,12);
        	printf("Play again?(Y/N)");
        	if(kbhit()){
                re=getch();
                if(re==121){//重設場地 
                    *gameover=0;
                    system("CLS");
	                char site[43][22];//重設場地	
                	*x=6;
                    *y=3;//座標變數
                	*path=0;//控制蛇的方向
                	*speed=150;//速度
                	*h=1;//蛇的長度 
                	*ch=1;//當吃到食物時 及時修正蛇的長度用的變數 
                	*feed=0;//檢查有沒有食物 0=沒有 1=有 
                	for(rx=0;rx<43;rx++)
                		for(ry=0;ry<22;ry++)
                            arr[rx][ry]=0;	
                	sitesetANDoutput(*x,*y,site);
                }//end if
                if(re==110){
                    *gameover=1;
                    gotoxy(14,14);
                    printf("即將離開遊戲...");
                    Sleep(1000);
                    break;
                }//end if
            }//end if
            Sleep(100);
        }//end while
}
void tab(int *speed,int h){//記分板 
	gotoxy(45,3);
	printf("吃下肚的食物:%d",(h-1));
	if(h<=11){
		gotoxy(45,5);
		printf("分數:%d",(h-1)*100);
		gotoxy(45,7);
		printf("當前速度:1x");
	}
	else if(h<=16){
		gotoxy(45,5);
		printf("分數:%d",(h-11)*150+1000);
		gotoxy(45,7);
		printf("當前速度:1.25x");
		*speed=120;
	}
	else if(h<=21){
		gotoxy(45,5);
		printf("分數:%d",(h-16)*200+2250);
		gotoxy(45,7);
		printf("當前速度:1.5x  ");
		*speed=100;
	}
	else if(h<=26){
		gotoxy(45,5);
		printf("分數:%d",(h-21)*250+3250);
		gotoxy(45,7);
		printf("當前速度:1.75x  ");
		*speed=85;
	}
	else if(h<=51){
		gotoxy(45,5);
		printf("分數:%d",(h-26)*300+4500);
		gotoxy(45,7);
		printf("當前速度:2.0x  ");
		*speed=75;
	}
	else if(h<=101){
		gotoxy(45,5);
		printf("分數:%d",(h-51)*500+12000);
		gotoxy(45,7);
		printf("當前速度:3.0x  ");
		*speed=50;
	}
	else {
		gotoxy(45,5);
		printf("分數:%d",(h-101)*2000+49500);
		gotoxy(45,7);
		printf("當前速度:4.0x  ");
		*speed=37;
	}
}//end function

void control(int *keys,int *x,int *y,int *path,int h){//控制蛇的方向 
	int keyf;//偵測按鍵的變數
	int keyt=80;
	if(kbhit()){//偵測按鍵
		keyf=getch();
		if(keyf==224){
			keyt=*keys;
			*keys=getch();
			if(h!=1 && keyt==72 && *keys==80)//上//當有蛇身時避免按反方向鍵  
				*keys=72;
			if(h!=1 && keyt==80 && *keys==72)//下//180度迴轉自殺的判定
				*keys=80;
			if(h!=1 && keyt==75 && *keys==77)//左 
				*keys=75;
			if(h!=1 && keyt==77 && *keys==75)//右 
				*keys=77;
			switch(*keys){
				case 72://上  
					*path=1;
					break;
				case 80://下 
					*path=2;
					break;
				case 75://左
					*path=3;
					break;
				case 77://右
					*path=4;
					break;
				default :
					break;
			}//end switch
		}//end if
	}//end if
	switch(*path){//當無動作時蛇往同個方向跑 
		case 1://上 
			*y=*y-1; 
			break;
		case 2://下 
			*y=*y+1; 
			break;
		case 3://左 
			*x=*x-2; 
			break;
		case 4://右 
			*x=*x+2; 
			break;
		default:
			break;
	}//end switch
}//end function

void sitesetANDoutput(int x,int y,char site[43][22]){//場地設置 
	for(x=0;x<43;x++){
		for(y=0;y<22;y++){
			site[x][y]='A';
			if(x==0 || x==42){
				site[x][y]='#';
				gotoxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				printf("○");
            }//end if
			else if(x%2==0 && y==0 || x%2==0 && y==21){
				site[x][y]='#';
				gotoxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				printf("○");
            }//end if 
		}//end for
	}//end for
}//end function

void gotoxy(int x, int y){//座標
  	COORD scrn;
  	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X=x; 
	scrn.Y=y;
  	SetConsoleCursorPosition(hOuput,scrn);
}//end function
