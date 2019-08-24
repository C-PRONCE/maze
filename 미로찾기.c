// �̼�3.c
// OS ȯ�� : WINDOWS (dos) 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <windows.h>

// ����Ű�� ����  
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define MAZE_MAX_SIZE 16

// ��/��� ���� ����  
FILE *file, *outfile;

// ĳ����(��)�� ���� ��ǥ��  
int x=1, y=1; 

// ���Ͽ��� �Է¹��� maze ũ�� ���� 
int hei=0, wid=0; 

// maze[][] ���� �� �ʱ�ȭ  
// ����� ���� ����� ���� �迭�� �ִ�ũ�⺸�� (����/����)���� 2�� ������Ŵ
// ���� �� ������ maze[1][1] ���� ������ ��ȹ��   
int maze[MAZE_MAX_SIZE+2][MAZE_MAX_SIZE+2] 
	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// stack - ������ ��ǥ�� ����, �ִ� maze�� ũ�⸸ŭ ����  
// xyStack[] : �ڵ� ��ã�� ��ǥ,  xyStackM : ���� ��ã�� ��ǥ  
struct Stack {
	int sx;	  
	int sy;		
}xyStack[MAZE_MAX_SIZE*MAZE_MAX_SIZE], xyStackM[1000];

// stack �� top�� ���� 
int stackTop = 0;
char *filename = "";		// �̷����� �̸� ������ ������ 
char filename1[30] = "";	// �̷����� �̸��� �Է¹��� ����  
 
int readMaze();		// "maze.txt" ������ �о����
int displayMaze(); 	// �̷θ� ���(�ڵ� ����) 
int displayMaze1();	// �̷θ� ���(���� ����) 
int statusMaze(); 	// ���� ĳ������ �̷� ���¸� return ��
void writeFile();	// ã�� �� ��ǥ�� ���Ϸ� ���(�ڵ� ã��) 
void writeFileM(); // ã�� ���� ��ǥ�� ����Ѵ� (���� ã��) 
void setColor(int text, int background); // ���� �� ����
int move(int key);  // �������� ĳ���͸� �̵� ��Ŵ   

int main(){

	int status=0; 		// ���� ��ǥ�� ���� �̷��� ����  
	int i=1, j=1;		// �ӽ� ����
	int menu1=0, menu2=0;		// �޴������� ���� ����
	int isFile = 1;		// �̷����� (��/��) üũ ����
	int key=0; 			// �������� �Է¹ޱ����� Ű ��  

	// �̷� ����(.txt)���� �Է¹���
	// ������ ���������� �������� �ݺ� ����  
	do {
		printf(" �̷������� �����ϼ���. \n\n");
		printf(" 1. maze.txt \n");
		printf(" 2. maze1.txt \n");
		printf(" 3. �����̸� ���� �Է� \n\n");
	    printf(" ���Ͻô� ��ȣ�� �����ϼ��� : ");		
		scanf("%d", &menu1);
		if(menu1==1){
			filename = "maze.txt";
		}else if(menu1==2) {
			filename = "maze1.txt";
		}else if(menu1==3) {
			printf(" ���ϸ��� �Է��ϼ��� : ");
			scanf("%s", filename1);
			filename = filename1;
		}
		isFile = readMaze(); // ������ ����  
		if (isFile==1) {
			system("cls");		
			printf(" ������ �������� �ʽ��ϴ�. �ٽ� �����ϼ���\n\n"); 
		}
	} while(isFile==1);
	 
	// �޴� ���� (1 ~ 2)  
	do {
		printf("\n\n [�޴�]\n\n");
		printf(" 1. ����� ���� \n");
		printf(" 2. �ڵ� �̷�ã��\n\n"); 
	    printf(" ���Ͻô� ��ȣ�� �����ϼ��� : ");
		scanf("%d", &menu2);
		if(menu2 < 1 || menu2 > 2) {
			system("cls");
			printf(" ��ȣ�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ��� \n\n"); 
		}
	} while ( menu2 < 1 || menu2 > 2); 
	

	if( (isFile==0) && (menu2==1) ){ // ������ �������̰�, �޴��� 1�̸� (���� ����) 
		maze[x][y] = 2;		// ���� ��ǥ(1,1)�� ĳ����(��) ���� ���� 
		xyStackM[stackTop].sx = 1;
		xyStackM[stackTop].sy = 1;
		 
		system("cls");
		displayMaze1();		// �̷���� (�������� ��) 
		
		// ĳ����(��)�� �̷��� ���� ������ �ݺ� �����Ŵ  
		while(1){
			key = getch();	// Ű �Է��� ��ٸ� 	
			if (key == 224) {	// Ű �Է��� ����Ű �Է��� ������ ĳ����(��) �̵�    
				key = getch();
				move(key);	
				
				stackTop++; 		// stack �� �̵� ��ǥ ����  
				if(stackTop==999) {	// stack overflow
					printf("STACK Overflow!!\n");
					break; 
				}
				xyStackM[stackTop].sx = x;
				xyStackM[stackTop].sy = y;				
				system("cls");
				displayMaze1(); // �̷���� (�������� ��)
			}else if( (key=='q') || (key =='Q') ){ // 'q' Ű�� �Է��ϸ� ����  
				break;	
			}
			
			// ĳ����(��)�� ��ǥ�� hei, wid ���� ������ �ݺ��� ���   
			if ( (x==hei)&&(y==wid) ) {
				printf("\n �������� �����߽��ϴ�.\n");
				writeFileM();	// ã�� �� ��ǥ�� ���Ͽ� ���	
				break;
			}
		}
	} else if( (isFile==0) && (menu2==2) ){	// ������ �������̰�, �޴��� 2�̸� (�ڵ�����)  
		maze[x][y] = 2;		// ���� ��ǥ(1,1)�� ĳ����(��) ���� ����  

		xyStack[stackTop].sx = 1;	// ������ ��ǥ�� stack�� ����  
		xyStack[stackTop].sy = 1;

		displayMaze();	// ȭ�鿡 �̷θ� ǥ��  
		
		// ĳ����(��)�� �̷��� ���� ������ �ݺ� �����Ŵ  
		while(1){
			status = statusMaze();	// �̷� ���� �� Ȯ�� 	  

			if ( status!= 0 ) {	  // ĳ���Ͱ� �� �� �ִ� ������ ���� ��   
				if ( status == 1 ) {
					maze[x][y] = 3; // ���� ��ǥ�� ������ �氪(3)�� ǥ�� 
					y = y + 1; // ���������� �̵���
					maze[x][y] = 2;	// �̵��� ��ǥ�� ĳ����(��) ��(2)�� ǥ��   
				}else if ( status == 2 ) {
					maze[x][y] = 3; // ���� ��ǥ�� ������ �氪(3)�� ǥ�� 
					x = x + 1;	// �Ʒ������� �̵���
					maze[x][y] = 2;	// �̵��� ��ǥ�� ĳ����(��) ��(2)�� ǥ��							
				}else if ( status == 4 ) {
					maze[x][y] = 3; // ���� ��ǥ�� ������ �氪(3)�� ǥ�� 
					y = y - 1; 	// �������� �̵���							
					maze[x][y] = 2;	// �̵��� ��ǥ�� ĳ����(��) ��(2)�� ǥ��										
				}else if ( status == 8 ) {
					maze[x][y] = 3; // ���� ��ǥ�� ������ �氪(3)�� ǥ�� 					
					x = x - 1;	// �������� �̵���
					maze[x][y] = 2;	// �̵��� ��ǥ�� ĳ����(��) ��(2)�� ǥ��					
				}
				// ������ top���� ������Ű�� �� ��ǥ�� ����  
				stackTop++; 	
				xyStack[stackTop].sx = x;
				xyStack[stackTop].sy = y;
			} else { 	// ĳ���Ͱ� �� �� �ִ� ������ ���� 
				// ������ ���� �������� ��
				//     - �� ��ǥ�� ������ ��ǥ�̸� �� �� �ִ� ���� ���� 
				//     - �� ��ǥ�� ������ ��ǥ�� �ƴϸ� stack�� ����� �ٷ� �� ��ǥ�� �̵�  

				if ( (x==1)&&(y==1) ) {	// ���� ��� ��ǥ�� ��� 
					printf("\n �� �� �ִ� ���� �����ϴ�.\n");
					break; 
				}else{		// ���� ��� ��ǥ�� �ƴ� ���
					maze[x][y] = 4; // ���� ��ǥ�� ������ �� ���� ��(4)�� ǥ��
					stackTop--;							  
					x = xyStack[stackTop].sx;		
					y = xyStack[stackTop].sy;
					maze[x][y] = 2; // ������ �̵��� ��ǥ�� ĳ����(��) ��(2)�� ǥ��   				
				}
			}
			
			// ȭ���� ����� �ٽ� ���  
			system("cls");
			displayMaze();
			
			// �̵� �� ĳ����(��)�� ��ǥ�� ������ ���� ������ �ݺ��� ���  
			if ( (x==hei)&&(y==wid) ) {
				printf("\n �������� �����߽��ϴ�.\n");
				writeFile();	// ã�� �� ��ǥ�� ���Ͽ� ���						
				break;
			}			
		}
	} 
	
	return 0;
} 

// "maze.txt" ������ �о����  
int readMaze(){
	char c=0;			// ���� �о���� ����		
	int i=1, j=1;		// �ӽ� ����
	
	file = fopen(filename, "r");

	// ������ ������ 0, ������ ������ 1�� return ��Ŵ  
	if(file == NULL) {
		printf("\n ������ �������� �ʽ��ϴ�.");
		return 1;
	} else {
		fscanf(file, "%d %d", &wid, &hei);	// ����, ���� ���� �о����  
		
		while( (c=fgetc(file)) != EOF) {	// �ݺ�(���� ���� ���� ������)
			// c ���� ���� maze[][] ���� ����
			// c ���� �����̸� ���� (0, 1 �� ���) 
			if (c=='0')
				maze[i][j++] = 0;
			else if (c=='1')
				maze[i][j++] = 1;
				
			// j���� wid ������ Ŭ ���
			// i�� ����, j���� 1���� ����  
			if(j>wid) { 
				i++;	
				j = 1;	
			}
			
			// ���� file�� �����Ͱ� hei�� �������� ���� ���
			// �о���̴� ������ ����������
			// (������ ���� ��ŭ�� �о���̱� ����)
			if(i > hei) break; 
		}
	   
		// "maze.txt"������ �ݴ´�  
		fclose(file);		
	
		return 0;
	}
}

// �̷θ� ���  
int displayMaze(){
	int i=0, j=0;		// �ӽ� ����	 

	// ȭ�� ��� ����
	// �� ���� maze[0][0] ~ [hei+1][wid+1] ���
	// 0: "��",  1: "��"  2: ĳ����("��") 3: ������ ��(��) ���  
	for(i=0; i<=(hei+1); i++){
		for(j=0; j<=(wid+1); j++){
			if( maze[i][j]==0 )			// 0: �����(��)
				printf("��"); 
			else if( maze[i][j]==1 )	// 1: ��(��)
				printf("��");
			else if( maze[i][j]==2 ) {	// 2: ĳ����(��)
				setColor(12, 0); 		// ������ ����(��) ���� ��� 
				printf("��");
				setColor(7, 0); 		// ���� ������ ���� 				
			} else if( maze[i][j]==3 ){	// 3: ������ ��(��)	
				setColor(14, 0); 		// ����� ����(��) ���� ��� 
				printf("��");
				setColor(7, 0);			// ���� ������ ����  
			}else if( maze[i][j]==4 )	// 3: ������(����) ��(��)	
				printf("��");			
		}
		printf("\n");
	}

	return 0;
}

// ���� ĳ������ �̷� ���¸� return ��  
// ����:1, �Ʒ���:2, ������:4, ����: 8 
int statusMaze(){
	int status = 0;
	
	// ĳ���Ͱ� �� �� �ִ� ������ üũ��  
	if( maze[x][y+1] == 0) status = 1;
	else if( maze[x+1][y] == 0) status = 2;
	else if( maze[x][y-1] == 0) status = 4;
	else if( maze[x-1][y] == 0) status = 8;
		
	return status;
}

// ã�� ���� ��ǥ�� ����Ѵ� (�ڵ� ã��) 
void writeFile(){
	int i=0;

	outfile = fopen("result.txt", "w");
	 	
	for(i=0; i<stackTop; i++)
		fprintf(outfile, "(%d,%d)\n", xyStack[i].sx,  xyStack[i].sy);
	fprintf(outfile, "(%d,%d)", xyStack[i].sx,  xyStack[i].sy);	
	
	fclose(outfile);
}

// ã�� ���� ��ǥ�� ����Ѵ� (���� ã��) 
void writeFileM(){
	int i=0;

	outfile = fopen("resultM.txt", "w");
	 	
	for(i=0; i<stackTop; i++)
		fprintf(outfile, "(%d,%d)\n", xyStackM[i].sx,  xyStackM[i].sy);
	fprintf(outfile, "(%d,%d)", xyStackM[i].sx,  xyStackM[i].sy);	
	
	fclose(outfile);
}

// ���� �� ����
void setColor(int text, int background){
	int color = (background << 4) | text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// ���� ���� �� �̷θ� ���  
int displayMaze1(){
	int i=0, j=0;		// �ӽ� ����	 

	// ȭ�� ��� ����
	// �� ���� maze[0][0] ~ [hei+1][wid+1] ���
	// 0: "��",  1: "��"  2: ĳ����("��")  ���  
	for(i=0; i<=(hei+1); i++){
		for(j=0; j<=(wid+1); j++){
			if( maze[i][j]==0 )			// 0: �����(��)
				printf("��"); 
			else if( maze[i][j]==1 )	// 1: ��(��)
				printf("��");
			else if( maze[i][j]==2 )	// 2: ĳ����(��)
				printf("��");
		}
		printf("\n");
	}
	printf("������ : 'q' \n");	
	return 0;
}

// ĳ����(��)�� ������
int move(int key){
	
	// ����Ű�� ���� maze[][] �迭�� ���� �̸� Ȯ���Ͽ�
	// ����� ��ǥ�� ���� 0 �� ��쿡 ��ǥ�� �����Ŵ
	// ĳ����(��) �� : 2    
	if (key == UP) {
		if (maze[x-1][y] == 0){
			maze[x][y] = 0;		// �� ��ǥ�� ���� 0���� ���� 
			x--;				// ��ǥ ����  
			maze[x][y] = 2;		// ����� ��ǥ�� ���� 2 �� ����
		}
	} else if (key == DOWN) {
		if (maze[x+1][y] == 0){
			maze[x][y] = 0;		// �� ��ǥ�� ���� 0���� ����
			x++;				// ��ǥ ����  
			maze[x][y] = 2;		// ����� ��ǥ�� ���� 2 �� ����  			
		}
	} else if (key == LEFT) {
		if (maze[x][y-1] == 0){
			maze[x][y] = 0;		// �� ��ǥ�� ���� 0���� ����
			y--;				// ��ǥ ����  		
			maze[x][y] = 2;		// ����� ��ǥ�� ���� 2 �� ����  			
		}
	} else if (key == RIGHT) {
		if (maze[x][y+1] == 0){
			maze[x][y] = 0;		// �� ��ǥ�� ���� 0���� ����
			y++;				// ��ǥ ����  
			maze[x][y] = 2;		// ����� ��ǥ�� ���� 2 �� ����  			
		}
	}
	
	return 0;
}
