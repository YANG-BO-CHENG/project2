#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void snake(int *ch,int h,int x,int y,int arr[43][22],char site[43][22]);//����D������
void feedcheck(int *feed,int *h,int *fx,int *fy,int x,int y,char site[43][22]);//�Ͳ����� 
void gameovercheck(int *gameover,int path,int x,int y,char site[43][22]);//�ˬd�C���O�_���� 
void tab(int *speed,int h);//�O���O 
void gamereset(int *x,int *y,int *path,int *speed,int *h,int *ch
,int *feed,int *gameover,int arr[43][22],char site[43][22]);
void control(int *keys,int *x,int *y,int *path,int h);//����D����V
void sitesetANDoutput(int x,int y,char site[43][22]);//���a�]�m 
void gotoxy(int x, int y);


int main(void){
	char site[43][22];//���a
	int arr[43][22]={0};
	int x=6,y=3;//�y���ܼ�
	int fx,fy;//��������m 
	int path=0;//����D����V
	int speed=150;//�t��
	int h=1;//�D������ 
	int ch=1;//��Y�쭹���� �ήɭץ��D�����ץΪ��ܼ� 
	int feed=0;//�ˬd���S������ 0=�S�� 1=�� 
	int keys;
	int gameover=0;//�C���������P�w 
	 
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

void snake(int *ch,int h,int x,int y,int arr[43][22],char site[43][22]){//����D������ 
	if(site[x][y]!='#'){
		site[x][y]='B';
		arr[x][y]=h;
		gotoxy(x,y);
		printf("�p");
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
				printf("�p");
			}//end if
			if(arr[x][y]!=0 && site[x][y]=='B')
				arr[x][y]--;
		}//end for
	}//end for


}//end function

void feedcheck(int *feed,int *h,int *fx,int *fy,int x,int y,char site[43][22]){//�Ͳ����� 

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
		printf("��");
		*feed=1;
	}//end if
}//end function

void gameovercheck(int *gameover,int path,int x,int y,char site[43][22]){//�ˬd�C���O�_���� 
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
                if(re==121){//���]���a 
                    *gameover=0;
                    system("CLS");
	                char site[43][22];//���]���a	
                	*x=6;
                    *y=3;//�y���ܼ�
                	*path=0;//����D����V
                	*speed=150;//�t��
                	*h=1;//�D������ 
                	*ch=1;//��Y�쭹���� �ήɭץ��D�����ץΪ��ܼ� 
                	*feed=0;//�ˬd���S������ 0=�S�� 1=�� 
                	for(rx=0;rx<43;rx++)
                		for(ry=0;ry<22;ry++)
                            arr[rx][ry]=0;	
                	sitesetANDoutput(*x,*y,site);
                }//end if
                if(re==110){
                    *gameover=1;
                    gotoxy(14,14);
                    printf("�Y�N���}�C��...");
                    Sleep(1000);
                    break;
                }//end if
            }//end if
            Sleep(100);
        }//end while
}
void tab(int *speed,int h){//�O���O 
	gotoxy(45,3);
	printf("�Y�U�{������:%d",(h-1));
	if(h<=11){
		gotoxy(45,5);
		printf("����:%d",(h-1)*100);
		gotoxy(45,7);
		printf("��e�t��:1x");
	}
	else if(h<=16){
		gotoxy(45,5);
		printf("����:%d",(h-11)*150+1000);
		gotoxy(45,7);
		printf("��e�t��:1.25x");
		*speed=120;
	}
	else if(h<=21){
		gotoxy(45,5);
		printf("����:%d",(h-16)*200+2250);
		gotoxy(45,7);
		printf("��e�t��:1.5x  ");
		*speed=100;
	}
	else if(h<=26){
		gotoxy(45,5);
		printf("����:%d",(h-21)*250+3250);
		gotoxy(45,7);
		printf("��e�t��:1.75x  ");
		*speed=85;
	}
	else if(h<=51){
		gotoxy(45,5);
		printf("����:%d",(h-26)*300+4500);
		gotoxy(45,7);
		printf("��e�t��:2.0x  ");
		*speed=75;
	}
	else if(h<=101){
		gotoxy(45,5);
		printf("����:%d",(h-51)*500+12000);
		gotoxy(45,7);
		printf("��e�t��:3.0x  ");
		*speed=50;
	}
	else {
		gotoxy(45,5);
		printf("����:%d",(h-101)*2000+49500);
		gotoxy(45,7);
		printf("��e�t��:4.0x  ");
		*speed=37;
	}
}//end function

void control(int *keys,int *x,int *y,int *path,int h){//����D����V 
	int keyf;//�������䪺�ܼ�
	int keyt=80;
	if(kbhit()){//��������
		keyf=getch();
		if(keyf==224){
			keyt=*keys;
			*keys=getch();
			if(h!=1 && keyt==72 && *keys==80)//�W//���D�����קK���Ϥ�V��  
				*keys=72;
			if(h!=1 && keyt==80 && *keys==72)//�U//180�װj��۱����P�w
				*keys=80;
			if(h!=1 && keyt==75 && *keys==77)//�� 
				*keys=75;
			if(h!=1 && keyt==77 && *keys==75)//�k 
				*keys=77;
			switch(*keys){
				case 72://�W  
					*path=1;
					break;
				case 80://�U 
					*path=2;
					break;
				case 75://��
					*path=3;
					break;
				case 77://�k
					*path=4;
					break;
				default :
					break;
			}//end switch
		}//end if
	}//end if
	switch(*path){//��L�ʧ@�ɳD���P�Ӥ�V�] 
		case 1://�W 
			*y=*y-1; 
			break;
		case 2://�U 
			*y=*y+1; 
			break;
		case 3://�� 
			*x=*x-2; 
			break;
		case 4://�k 
			*x=*x+2; 
			break;
		default:
			break;
	}//end switch
}//end function

void sitesetANDoutput(int x,int y,char site[43][22]){//���a�]�m 
	for(x=0;x<43;x++){
		for(y=0;y<22;y++){
			site[x][y]='A';
			if(x==0 || x==42){
				site[x][y]='#';
				gotoxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				printf("��");
            }//end if
			else if(x%2==0 && y==0 || x%2==0 && y==21){
				site[x][y]='#';
				gotoxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				printf("��");
            }//end if 
		}//end for
	}//end for
}//end function

void gotoxy(int x, int y){//�y��
  	COORD scrn;
  	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X=x; 
	scrn.Y=y;
  	SetConsoleCursorPosition(hOuput,scrn);
}//end function
