// 미션3.c
// OS 환경 : WINDOWS (dos) 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <windows.h>

// 방향키값 선언  
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define MAZE_MAX_SIZE 16

// 입/출력 파일 선언  
FILE *file, *outfile;

// 캐릭터(★)의 현재 좌표값  
int x=1, y=1; 

// 파일에서 입력밭은 maze 크기 변수 
int hei=0, wid=0; 

// maze[][] 선언 및 초기화  
// 사방의 벽을 만들기 위해 배열의 최대크기보다 (가로/세로)각각 2씩 증가시킴
// 실제 값 저장은 maze[1][1] 부터 시작할 계획임   
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

// stack - 지나간 좌표를 저장, 최대 maze의 크기만큼 설정  
// xyStack[] : 자동 길찾기 좌표,  xyStackM : 수동 길찾기 좌표  
struct Stack {
	int sx;	  
	int sy;		
}xyStack[MAZE_MAX_SIZE*MAZE_MAX_SIZE], xyStackM[1000];

// stack 의 top값 설정 
int stackTop = 0;
char *filename = "";		// 미로파일 이름 저장할 포인터 
char filename1[30] = "";	// 미로파일 이름을 입력받을 변수  
 
int readMaze();		// "maze.txt" 파일을 읽어들임
int displayMaze(); 	// 미로를 출력(자동 조작) 
int displayMaze1();	// 미로를 출력(수동 조작) 
int statusMaze(); 	// 현재 캐릭터의 미로 상태를 return 함
void writeFile();	// 찾은 길 좌표를 파일로 출력(자동 찾기) 
void writeFileM(); // 찾은 길의 좌표를 출력한다 (수동 찾기) 
void setColor(int text, int background); // 글자 색 변경
int move(int key);  // 수동으로 캐릭터를 이동 시킴   

int main(){

	int status=0; 		// 현재 좌표에 대한 미로의 상태  
	int i=1, j=1;		// 임시 변수
	int menu1=0, menu2=0;		// 메뉴선택을 위한 변수
	int isFile = 1;		// 미로파일 (유/무) 체크 변수
	int key=0; 			// 수동으로 입력받기위한 키 값  

	// 미로 파일(.txt)명을 입력받음
	// 파일을 정상적으로 열때까지 반복 실행  
	do {
		printf(" 미로파일을 선택하세요. \n\n");
		printf(" 1. maze.txt \n");
		printf(" 2. maze1.txt \n");
		printf(" 3. 파일이름 직접 입력 \n\n");
	    printf(" 원하시는 번호를 선택하세요 : ");		
		scanf("%d", &menu1);
		if(menu1==1){
			filename = "maze.txt";
		}else if(menu1==2) {
			filename = "maze1.txt";
		}else if(menu1==3) {
			printf(" 파일명을 입력하세요 : ");
			scanf("%s", filename1);
			filename = filename1;
		}
		isFile = readMaze(); // 파일을 열음  
		if (isFile==1) {
			system("cls");		
			printf(" 파일이 존재하지 않습니다. 다시 선택하세요\n\n"); 
		}
	} while(isFile==1);
	 
	// 메뉴 선택 (1 ~ 2)  
	do {
		printf("\n\n [메뉴]\n\n");
		printf(" 1. 사용자 조종 \n");
		printf(" 2. 자동 미로찾기\n\n"); 
	    printf(" 원하시는 번호를 선택하세요 : ");
		scanf("%d", &menu2);
		if(menu2 < 1 || menu2 > 2) {
			system("cls");
			printf(" 번호입력이 잘못되었습니다. 다시 입력하세요 \n\n"); 
		}
	} while ( menu2 < 1 || menu2 > 2); 
	

	if( (isFile==0) && (menu2==1) ){ // 파일이 정상적이고, 메뉴가 1이면 (수동 실행) 
		maze[x][y] = 2;		// 최초 좌표(1,1)에 캐릭터(★) 값을 설정 
		xyStackM[stackTop].sx = 1;
		xyStackM[stackTop].sy = 1;
		 
		system("cls");
		displayMaze1();		// 미로출력 (수동조작 시) 
		
		// 캐릭터(★)가 미로의 끝에 닿으면 반복 종료시킴  
		while(1){
			key = getch();	// 키 입력을 기다림 	
			if (key == 224) {	// 키 입력중 방향키 입력을 받으면 캐릭터(★) 이동    
				key = getch();
				move(key);	
				
				stackTop++; 		// stack 에 이동 좌표 저장  
				if(stackTop==999) {	// stack overflow
					printf("STACK Overflow!!\n");
					break; 
				}
				xyStackM[stackTop].sx = x;
				xyStackM[stackTop].sy = y;				
				system("cls");
				displayMaze1(); // 미로출력 (수동조작 시)
			}else if( (key=='q') || (key =='Q') ){ // 'q' 키를 입력하면 끝냄  
				break;	
			}
			
			// 캐릭터(★)의 좌표가 hei, wid 값과 같으면 반복을 벗어남   
			if ( (x==hei)&&(y==wid) ) {
				printf("\n 목적지에 도착했습니다.\n");
				writeFileM();	// 찾은 길 좌표를 파일에 출력	
				break;
			}
		}
	} else if( (isFile==0) && (menu2==2) ){	// 파일이 정상적이고, 메뉴가 2이면 (자동실행)  
		maze[x][y] = 2;		// 최초 좌표(1,1)에 캐릭터(★) 값을 설정  

		xyStack[stackTop].sx = 1;	// 최초의 좌표를 stack에 저장  
		xyStack[stackTop].sy = 1;

		displayMaze();	// 화면에 미로를 표시  
		
		// 캐릭터(★)가 미로의 끝에 닿으면 반복 종료시킴  
		while(1){
			status = statusMaze();	// 미로 상태 값 확인 	  

			if ( status!= 0 ) {	  // 캐릭터가 갈 수 있는 방향이 있을 때   
				if ( status == 1 ) {
					maze[x][y] = 3; // 현재 좌표에 지나간 길값(3)을 표시 
					y = y + 1; // 오른쪽으로 이동함
					maze[x][y] = 2;	// 이동할 좌표에 캐릭터(★) 값(2)을 표시   
				}else if ( status == 2 ) {
					maze[x][y] = 3; // 현재 좌표에 지나간 길값(3)을 표시 
					x = x + 1;	// 아래쪽으로 이동함
					maze[x][y] = 2;	// 이동할 좌표에 캐릭터(★) 값(2)을 표시							
				}else if ( status == 4 ) {
					maze[x][y] = 3; // 현재 좌표에 지나간 길값(3)을 표시 
					y = y - 1; 	// 왼쪽으로 이동함							
					maze[x][y] = 2;	// 이동할 좌표에 캐릭터(★) 값(2)을 표시										
				}else if ( status == 8 ) {
					maze[x][y] = 3; // 현재 좌표에 지나간 길값(3)을 표시 					
					x = x - 1;	// 위쪽으로 이동함
					maze[x][y] = 2;	// 이동할 좌표에 캐릭터(★) 값(2)을 표시					
				}
				// 스택의 top값을 증가시키고 현 좌표를 저장  
				stackTop++; 	
				xyStack[stackTop].sx = x;
				xyStack[stackTop].sy = y;
			} else { 	// 캐릭터가 갈 수 있는 방향이 없음 
				// 목적지 값과 같지않을 때
				//     - 현 좌표가 최초의 좌표이면 갈 수 있는 길이 없음 
				//     - 현 좌표가 최조의 좌표가 아니면 stack에 저장된 바로 전 좌표로 이동  

				if ( (x==1)&&(y==1) ) {	// 최초 출발 좌표일 경우 
					printf("\n 갈 수 있는 길이 없습니다.\n");
					break; 
				}else{		// 최초 출발 좌표가 아닐 경우
					maze[x][y] = 4; // 현재 좌표에 지나간 길 막힌 값(4)을 표시
					stackTop--;							  
					x = xyStack[stackTop].sx;		
					y = xyStack[stackTop].sy;
					maze[x][y] = 2; // 전으로 이동한 좌표에 캐릭터(★) 값(2)을 표시   				
				}
			}
			
			// 화면을 지우고 다시 출력  
			system("cls");
			displayMaze();
			
			// 이동 후 캐릭터(★)의 좌표가 목적지 값과 같으면 반복을 벗어남  
			if ( (x==hei)&&(y==wid) ) {
				printf("\n 목적지에 도착했습니다.\n");
				writeFile();	// 찾은 길 좌표를 파일에 출력						
				break;
			}			
		}
	} 
	
	return 0;
} 

// "maze.txt" 파일을 읽어들임  
int readMaze(){
	char c=0;			// 값을 읽어들일 변수		
	int i=1, j=1;		// 임시 변수
	
	file = fopen(filename, "r");

	// 파일이 있으면 0, 파일이 없으면 1을 return 시킴  
	if(file == NULL) {
		printf("\n 파일이 존재하지 않습니다.");
		return 1;
	} else {
		fscanf(file, "%d %d", &wid, &hei);	// 세로, 가로 값을 읽어들임  
		
		while( (c=fgetc(file)) != EOF) {	// 반복(파일 끝을 만날 때까지)
			// c 값에 따라 maze[][] 값을 결정
			// c 값이 공백이면 무시 (0, 1 만 사용) 
			if (c=='0')
				maze[i][j++] = 0;
			else if (c=='1')
				maze[i][j++] = 1;
				
			// j값이 wid 값보다 클 경우
			// i값 증가, j값을 1으로 설정  
			if(j>wid) { 
				i++;	
				j = 1;	
			}
			
			// 만약 file의 데이터가 hei의 개수보다 많을 경우
			// 읽어들이는 실행을 빠져나간다
			// (지정된 개수 만큼만 읽어들이기 위함)
			if(i > hei) break; 
		}
	   
		// "maze.txt"파일을 닫는다  
		fclose(file);		
	
		return 0;
	}
}

// 미로를 출력  
int displayMaze(){
	int i=0, j=0;		// 임시 변수	 

	// 화면 출력 시작
	// 벽 포함 maze[0][0] ~ [hei+1][wid+1] 출력
	// 0: "□",  1: "■"  2: 캐릭터("★") 3: 지나간 길(◇) 출력  
	for(i=0; i<=(hei+1); i++){
		for(j=0; j<=(wid+1); j++){
			if( maze[i][j]==0 )			// 0: 빈공간(□)
				printf("□"); 
			else if( maze[i][j]==1 )	// 1: 벽(■)
				printf("■");
			else if( maze[i][j]==2 ) {	// 2: 캐릭터(★)
				setColor(12, 0); 		// 빨간색 글자(★) 변경 출력 
				printf("★");
				setColor(7, 0); 		// 원래 색으로 변경 				
			} else if( maze[i][j]==3 ){	// 3: 지나간 길(◇)	
				setColor(14, 0); 		// 노란색 글자(◇) 변경 출력 
				printf("◇");
				setColor(7, 0);			// 원래 색으로 변경  
			}else if( maze[i][j]==4 )	// 3: 지나간(막힌) 길(＃)	
				printf("＃");			
		}
		printf("\n");
	}

	return 0;
}

// 현재 캐릭터의 미로 상태를 return 함  
// 왼쪽:1, 아래쪽:2, 오른쪽:4, 위쪽: 8 
int statusMaze(){
	int status = 0;
	
	// 캐릭터가 갈 수 있는 방향을 체크함  
	if( maze[x][y+1] == 0) status = 1;
	else if( maze[x+1][y] == 0) status = 2;
	else if( maze[x][y-1] == 0) status = 4;
	else if( maze[x-1][y] == 0) status = 8;
		
	return status;
}

// 찾은 길의 좌표를 출력한다 (자동 찾기) 
void writeFile(){
	int i=0;

	outfile = fopen("result.txt", "w");
	 	
	for(i=0; i<stackTop; i++)
		fprintf(outfile, "(%d,%d)\n", xyStack[i].sx,  xyStack[i].sy);
	fprintf(outfile, "(%d,%d)", xyStack[i].sx,  xyStack[i].sy);	
	
	fclose(outfile);
}

// 찾은 길의 좌표를 출력한다 (수동 찾기) 
void writeFileM(){
	int i=0;

	outfile = fopen("resultM.txt", "w");
	 	
	for(i=0; i<stackTop; i++)
		fprintf(outfile, "(%d,%d)\n", xyStackM[i].sx,  xyStackM[i].sy);
	fprintf(outfile, "(%d,%d)", xyStackM[i].sx,  xyStackM[i].sy);	
	
	fclose(outfile);
}

// 글자 색 변경
void setColor(int text, int background){
	int color = (background << 4) | text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// 수동 조작 시 미로를 출력  
int displayMaze1(){
	int i=0, j=0;		// 임시 변수	 

	// 화면 출력 시작
	// 벽 포함 maze[0][0] ~ [hei+1][wid+1] 출력
	// 0: "□",  1: "■"  2: 캐릭터("★")  출력  
	for(i=0; i<=(hei+1); i++){
		for(j=0; j<=(wid+1); j++){
			if( maze[i][j]==0 )			// 0: 빈공간(□)
				printf("□"); 
			else if( maze[i][j]==1 )	// 1: 벽(■)
				printf("■");
			else if( maze[i][j]==2 )	// 2: 캐릭터(★)
				printf("★");
		}
		printf("\n");
	}
	printf("끝내기 : 'q' \n");	
	return 0;
}

// 캐릭터(★)를 움직임
int move(int key){
	
	// 뱡향키에 따른 maze[][] 배열의 값을 미리 확인하여
	// 변경될 좌표의 값이 0 일 경우에 좌표를 변경시킴
	// 캐릭터(★) 값 : 2    
	if (key == UP) {
		if (maze[x-1][y] == 0){
			maze[x][y] = 0;		// 현 좌표의 값을 0으로 설정 
			x--;				// 좌표 변경  
			maze[x][y] = 2;		// 변경된 좌표의 값을 2 값 설정
		}
	} else if (key == DOWN) {
		if (maze[x+1][y] == 0){
			maze[x][y] = 0;		// 현 좌표의 값을 0으로 설정
			x++;				// 좌표 변경  
			maze[x][y] = 2;		// 변경된 좌표의 값을 2 값 설정  			
		}
	} else if (key == LEFT) {
		if (maze[x][y-1] == 0){
			maze[x][y] = 0;		// 현 좌표의 값을 0으로 설정
			y--;				// 좌표 변경  		
			maze[x][y] = 2;		// 변경된 좌표의 값을 2 값 설정  			
		}
	} else if (key == RIGHT) {
		if (maze[x][y+1] == 0){
			maze[x][y] = 0;		// 현 좌표의 값을 0으로 설정
			y++;				// 좌표 변경  
			maze[x][y] = 2;		// 변경된 좌표의 값을 2 값 설정  			
		}
	}
	
	return 0;
}
