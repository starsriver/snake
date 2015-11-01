//Snake游戏
#include<graphics.h>
#include<stdio.h>

#define N 200

int i,key;
int level;//难度 
int score;//得分 
int gamespeed;//游戏速度 

struct Food//食物结构体 
{
	int x;//食物横坐标 
	int y;//食物纵坐标 
	int yes;//判定是否出现食物，1为是，0为否 
}food;
struct Snake//蛇结构体 
{
	int x[N]; 
	int y[N];
	int node;//蛇的节数 
	int direction;//蛇的方向 
	int life;//蛇的生命值。0活着，1死亡 
}snake;

void Init(void);//游戏初始化 
void Close(void);//游戏关闭 
void DrawK(void);//绘制游戏围墙 
void DrawAll(void);//绘制游戏对象 
void GameOver(void);//游戏结束 
void Update(void);//游戏主体 
void PrScore(void);//输出成绩 
void PrScoreF(void);//输出成绩

int main(void)
{
	Init();
	Update();
	return 0;
} 

//Init()游戏初始化 的实现
void Init(void)
{
	score=0;
	gamespeed=300;
	level=0;
	food.yes=1;
	snake.life=0;
	snake.direction=1;//蛇初始方向向右
	snake.x[0]=100;
	snake.y[0]=100;//蛇头位置
	snake.x[1]=110;
	snake.x[1]=100;
	snake.node=2;//蛇的节数
	initgraph(650,500);
	cleardevice();
	DrawK();
	return;
}

//Close();游戏关闭  的实现
void Close(void)
{
	closegraph();
	return;
}

//DrawK();绘制游戏围墙  的实现
void DrawK(void)
{
	//绘制画面，左上角坐标（50,40），右下角坐标（610,460） 的围墙
	
	setbkcolor(BLACK);//指定背景颜色为黑色 
	setcolor(LIGHTCYAN);//指定前景色淡青色
	setlinestyle(SOLID_LINE,0,4,NULL);//设置线形
	
	for(i=50;i<=600;i+=10)//画围墙
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

//GameOver();游戏结束 的实现
void GameOver(void)
{
	cleardevice();//清屏
	PrScoreF();
	setcolor(RED);
	setfont(-100,0,"黑体");
	outtextxy(100,200,"GAME OVER");
	getch();
	return; 
} 

//Update();游戏主体 的实现
void Update(void)
{
	randomize();//随机数发生器
	PrScore();//输出成绩 
	while(snake.life==0)//游戏死循环，蛇死或按ESC键结束 
	{
		DrawAll();
		if(kbhit())
		{
			key=getch();//接受按键
			if(key==27)
				break;
			else
			{
				//1,2,3,4表示右,左,上,下四个方向
				if((key==87||key==119)&&snake.direction!=4)//判断是否往相反方向移动
					snake.direction=3;
				else if((key==68||key==100)&&snake.direction!=2)
					snake.direction=1;
				else if((key==65||key==97)&&snake.direction!=1)
					snake.direction=2;
				else if((key==83||key==115)&&snake.direction!=3)
					snake.direction=4;
			}
		}
		if(food.yes==1)//需要出现新食物 
		{
			food.x=random(500)+60;
			food.y=random(370)+50;
			while(food.x%10!=0)//食物必须出现在整格中 
				food.x++;
			while(food.y%10!=0)
				food.y++;
			food.yes=0;//已有食物，不需要新食物 
		}
			
		for(i=snake.node-1;i>0;i--)//蛇的每一节前移
		{
			snake.x[i]=snake.x[i-1];
			snake.y[i]=snake.y[i-1];
		}
		switch(snake.direction)//1,2,3,4表示右,左,上,下四个方向,通过这个判断来移动蛇头
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
		for(i=3;i<snake.node;i++)//从蛇的第四节开始判断是否碰到自己，因为蛇头为两节，第三节不可能拐过来 
		{
			if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0]) 
			{
				snake.life=1;
				break;
			}
		}
		if(snake.x[0]<55||snake.x[0]>595||snake.y[0]<55||snake.y[0]>455)//判断蛇是否碰到墙壁 
		{
			snake.life=1; 
		}
		if(snake.x[0]==food.x&&snake.y[0]==food.y) //蛇吃到食物
		{
			setcolor(BLACK);
			rectangle(food.x,food.y,food.x+10,food.y-10);
			snake.x[snake.node]=-20;
			snake.y[snake.node]=-20;//新的一节先放在看不见的位置,下次循环就取前一节的位置
			snake.node++;//蛇的节数增加
			food.yes=1;//需要新食物
			score+=10;
			PrScore();//输出得分 
		}
		if((score/10)==(10*level+5))//游戏难度机制 
		{	
			gamespeed-=50;
			if(gamespeed<=50)
				gamespeed=50;
			level++;
		}
		DrawAll();
		delay_ms(gamespeed);//延时，控制游戏速度 
	}
	GameOver();
	Close();
	return;
} 

//绘制游戏对象 
void DrawAll()
{
	if(food.yes==0)//绘制已有食物
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

//PrScore();输出成绩 的实现
void PrScore(void)
{
	char str[20];
	setcolor(YELLOW);
	setfont(-20,0,"黑体");
	sprintf(str,"score:%d  speed:%d",score,gamespeed);
	outtextxy(50,15,str);
	return;
} 
void PrScoreF(void)
{
	char str[10];
	setcolor(YELLOW);
	setfont(-20,0,"黑体");
	sprintf(str,"score:%d",score);
	outtextxy(280,300,str);
	return;
} 
