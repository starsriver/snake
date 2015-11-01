//Snake��Ϸ
#include<graphics.h>
#include<stdio.h>

#define N 200

int i,key;
int level;//�Ѷ� 
int score;//�÷� 
int gamespeed;//��Ϸ�ٶ� 

struct Food//ʳ��ṹ�� 
{
	int x;//ʳ������� 
	int y;//ʳ�������� 
	int yes;//�ж��Ƿ����ʳ�1Ϊ�ǣ�0Ϊ�� 
}food;
struct Snake//�߽ṹ�� 
{
	int x[N]; 
	int y[N];
	int node;//�ߵĽ��� 
	int direction;//�ߵķ��� 
	int life;//�ߵ�����ֵ��0���ţ�1���� 
}snake;

void Init(void);//��Ϸ��ʼ�� 
void Close(void);//��Ϸ�ر� 
void DrawK(void);//������ϷΧǽ 
void DrawAll(void);//������Ϸ���� 
void GameOver(void);//��Ϸ���� 
void Update(void);//��Ϸ���� 
void PrScore(void);//����ɼ� 
void PrScoreF(void);//����ɼ�

int main(void)
{
	Init();
	Update();
	return 0;
} 

//Init()��Ϸ��ʼ�� ��ʵ��
void Init(void)
{
	score=0;
	gamespeed=300;
	level=0;
	food.yes=1;
	snake.life=0;
	snake.direction=1;//�߳�ʼ��������
	snake.x[0]=100;
	snake.y[0]=100;//��ͷλ��
	snake.x[1]=110;
	snake.x[1]=100;
	snake.node=2;//�ߵĽ���
	initgraph(650,500);
	cleardevice();
	DrawK();
	return;
}

//Close();��Ϸ�ر�  ��ʵ��
void Close(void)
{
	closegraph();
	return;
}

//DrawK();������ϷΧǽ  ��ʵ��
void DrawK(void)
{
	//���ƻ��棬���Ͻ����꣨50,40�������½����꣨610,460�� ��Χǽ
	
	setbkcolor(BLACK);//ָ��������ɫΪ��ɫ 
	setcolor(LIGHTCYAN);//ָ��ǰ��ɫ����ɫ
	setlinestyle(SOLID_LINE,0,4,NULL);//��������
	
	for(i=50;i<=600;i+=10)//��Χǽ
	{
		rectangle(i,40,i+10,49);
		rectangle(i,451,i+10,460);
	}
	for(i=40;i<=450;i+=10)
	{
		rectangle(50,i,59,i+10);
		rectangle(601,i,610,i+10); 
	}
	return;
} 

//GameOver();��Ϸ���� ��ʵ��
void GameOver(void)
{
	cleardevice();//����
	PrScoreF();
	setcolor(RED);
	setfont(-100,0,"����");
	outtextxy(100,200,"GAME OVER");
	getch();
	return; 
} 

//Update();��Ϸ���� ��ʵ��
void Update(void)
{
	randomize();//�����������
	PrScore();//����ɼ� 
	while(snake.life==0)//��Ϸ��ѭ����������ESC������ 
	{
		DrawAll();
		if(kbhit())
		{
			key=getch();//���ܰ���
			if(key==27)
				break;
			else
			{
				//1,2,3,4��ʾ��,��,��,���ĸ�����
				if((key==87||key==119)&&snake.direction!=4)//�ж��Ƿ����෴�����ƶ�
					snake.direction=3;
				else if((key==68||key==100)&&snake.direction!=2)
					snake.direction=1;
				else if((key==65||key==97)&&snake.direction!=1)
					snake.direction=2;
				else if((key==83||key==115)&&snake.direction!=3)
					snake.direction=4;
			}
		}
		if(food.yes==1)//��Ҫ������ʳ�� 
		{
			food.x=random(500)+60;
			food.y=random(370)+50;
			while(food.x%10!=0)//ʳ���������������� 
				food.x++;
			while(food.y%10!=0)
				food.y++;
			food.yes=0;//����ʳ�����Ҫ��ʳ�� 
		}
			
		for(i=snake.node-1;i>0;i--)//�ߵ�ÿһ��ǰ��
		{
			snake.x[i]=snake.x[i-1];
			snake.y[i]=snake.y[i-1];
		}
		switch(snake.direction)//1,2,3,4��ʾ��,��,��,���ĸ�����,ͨ������ж����ƶ���ͷ
		{
			case 1:
				snake.x[0]+=10;
				break;
			case 2:
				snake.x[0]-=10;
				break;
			case 3:
				snake.y[0]-=10;
				break;
			case 4:
				snake.y[0]+=10;
				break;
			default:
				break; 
		} 
		for(i=3;i<snake.node;i++)//���ߵĵ��Ľڿ�ʼ�ж��Ƿ������Լ�����Ϊ��ͷΪ���ڣ������ڲ����ܹչ��� 
		{
			if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0]) 
			{
				snake.life=1;
				break;
			}
		}
		if(snake.x[0]<55||snake.x[0]>595||snake.y[0]<55||snake.y[0]>455)//�ж����Ƿ�����ǽ�� 
		{
			snake.life=1; 
		}
		if(snake.x[0]==food.x&&snake.y[0]==food.y) //�߳Ե�ʳ��
		{
			setcolor(BLACK);
			rectangle(food.x,food.y,food.x+10,food.y-10);
			snake.x[snake.node]=-20;
			snake.y[snake.node]=-20;//�µ�һ���ȷ��ڿ�������λ��,�´�ѭ����ȡǰһ�ڵ�λ��
			snake.node++;//�ߵĽ�������
			food.yes=1;//��Ҫ��ʳ��
			score+=10;
			PrScore();//����÷� 
		}
		if((score/10)==(10*level+5))//��Ϸ�ѶȻ��� 
		{	
			gamespeed-=50;
			if(gamespeed<=50)
				gamespeed=50;
			level++;
		}
		DrawAll();
		delay_ms(gamespeed);//��ʱ��������Ϸ�ٶ� 
	}
	GameOver();
	Close();
	return;
} 

//������Ϸ���� 
void DrawAll()
{
	if(food.yes==0)//��������ʳ��
	{
		setcolor(GREEN);
		rectangle(food.x,food.y,food.x+10,food.y-10);
	}
	setcolor(RED); 
	for(i=0;i<snake.node;i++)
		rectangle(snake.x[i],snake.y[i],snake.x[i]+10,snake.y[i]-10);
	setcolor(BLACK);
	rectangle(snake.x[snake.node-1],snake.y[snake.node-1],snake.x[snake.node-1]+10,snake.y[snake.node-1]-10);
	return;
}

//PrScore();����ɼ� ��ʵ��
void PrScore(void)
{
	char str[20];
	setcolor(YELLOW);
	setfont(-20,0,"����");
	sprintf(str,"score:%d  speed:%d",score,gamespeed);
	outtextxy(50,15,str);
	return;
} 
void PrScoreF(void)
{
	char str[10];
	setcolor(YELLOW);
	setfont(-20,0,"����");
	sprintf(str,"score:%d",score);
	outtextxy(280,300,str);
	return;
} 
