#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
	char type;                   // Node的型態 ( 'S' : Sensor, 'o' : 有訊號的Node, '.' : 無訊號的Node) 
	unsigned int signal;         // Node的訊號強度 
};

typedef struct node Node;

void init_Map(Node **map, int m, int n);
void show_Map(Node **map,int m, int n);
void set_Sensor(Node **map, int m, int n);
void show_Menu(Node **map, int m, int n); 
void compute_Coverage(Node **map, int m, int n, int x, int y);
int  distance(int x, int y, int i, int j);
void IsFullCover(void);
void random_Sensor(Node **map, int m, int n);
void set_Hole(Node **map, int m, int n);
void dibble(Node **map, int m, int n, int x1, int y1, int x2, int y2);
void exportToFile(Node **map, int m, int n);

int range = 5;
int counter;
int totalSensor;
int deadSensor;

int main(void){
	
	int m, n, i, j;
	
	printf("請輸入地圖的長 m : "); 
	scanf("%d", &m);
	printf("\n請輸入地圖的寬 n : "); 
	scanf("%d", &n);
	printf("\n請輸入Sensor的Range(default = 5) : ");
	scanf("%d", &range);
	
	
	/* 創造一個二維陣列(Create Map) */
	
	Node **map = calloc(m, sizeof(Node *));	
	Node *array = calloc(m * n, sizeof(Node));
	
	for(i = 0; i < m; i++)
	   map[i] = &array[n * i];
	
	/* 顯示初始地圖 */
	
	init_Map(map, m, n);
    show_Map(map, m, n);
    
    /* 功能表 */ 
    
    show_Menu(map, m, n);
    
	printf("\n\nBye Bye!\n\n");
	system("PAUSE");
	free(map);
	free(array);
	return 0;
}

/* Initalize the Map */

void init_Map(Node **map, int m, int n){
	
	int i, j;
	
	printf("\n\n******** 地 * 圖 * 初 * 始 * 化 ********\n\n");
	
    for(i = 0; i < m; i++){
    	for(j = 0; j < n; j++){    
    	    map[i][j].type = '.';
			map[i][j].signal = 0;  
    	} 	
    }
    
    /* 設定 Nodes Counter */
    
    counter = m * n;
    totalSensor = 0;
    deadSensor  = 0;
    
    system("PAUSE");
    
	return ;
}


/* Show Me the Map  */

void show_Map(Node **map, int m, int n){
	
	int i, j;
	
	system("cls");
	
    for(i = 0; i < m; i++){
    	for(j = 0; j < n; j++){
    		
    		printf("%c ", map[i][j].type);
    		
			if(!((j + 1) % n))
    		   printf("\n");
    	} 	
    }
    
    printf("\n\n");
	return ;
}

/* Sensor Allocation Function */

void set_Sensor(Node **map, int m, int n){
	
	int x, y;
	
	do{
		
		show_Map(map, m, n);
		
		printf("請輸入要佈下的Sensor座標, 結束請輸入 -1\n");
		
		/* 設定x座標 輸入-1則結束設定 */
		
		printf("x (1 < x <= %d) : ", n);	   
		scanf("%d", &x);
		
		if(x == -1)
		    break;
		else if(x <= 0 || x > n){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		/* 設定y座標, 輸入-1結束設定 */ 
		
		printf("y (1 < y <= %d) : ", m);	   
		scanf("%d", &y);
		
		if((y == -1))
		   break;
		else if(y <= 0 || y > m){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}   
		
		/* 設定的該點原本不是 Sensor */
		
		if(map[m - y][x - 1].type != 'S'){
			compute_Coverage(map, m, n, x - 1, m - y);
			totalSensor++;
		}  
		 
		/* 原本該點是 Sensor , 則要取消該點 Sensor 的設置 */ 
		  
		else{
			compute_Coverage(map, m, n, x - 1, m - y);
			totalSensor--;
		}
		    
		
		//system("cls");	
		
	} while(1);
	
	return ;
}

/* Function List */

void show_Menu(Node **map, int m, int n){
	
	int option = 0;
	
	do{
		printf("\n請選擇你要使用的Function : \n\n"
		       "[1] 顯示地圖\n"
			   "[2] 設定Sensor位置\n"
			   "[3] 隨機布置 Sensor 位置\n" 
			   "[4] 挖洞\n" 
			   "[5] 計算是否Full Coverage\n"
			   "[6] 輸出結果至檔案中\n" 
			   "[0] 結束程式\n\n > ");
		scanf("%d", &option);	   
			   
		switch(option){
			
			case 1 :
				show_Map(map, m, n);
				system("PAUSE");
				break;
			case 2 :
				set_Sensor(map, m, n);
				break;
			case 3 :
				random_Sensor(map, m, n);
				break;
			case 4 : 
			    set_Hole(map, m, n);
				break;	
			case 5 :
			    IsFullCover();
				break;
			case 6 :
			    exportToFile(map, m, n);
				break;	
			case 0 :
			    break;		
			default :
			    printf("\n\n請重新輸入正確的選項!\n\n");
			    system("PAUSE");
				break;	
		}
		
		system("cls");
		
	} while(option != 0);
	
	
	
	return ;
}

/* Compute Full Coverage Function */

void compute_Coverage(Node **map, int m, int n, int x, int y){
	
	int i, j;
	int up = y - range;
	int down = y + range;
	int left = x - range;
	int right = x + range;
	int squ_range = range * range; 
	
	/* 判斷 Sensor 的 range 是否超過邊界 */
		
	if(left < 0)
		left = 0;
		
	if(right >= n)
		right = n - 1;
		   
	if(up < 0)
		up = 0;
		   
	if(down >= m)
		down = m - 1;
	
	/* 設定的該點為原本無訊號的 Node */
	
	if(map[y][x].type == '.') 
		--counter;
		
	/* 設定的該點為原本為 Sensor 
		
	else if(map[y][x].type == 'S')
	    ++counter;	
	*/
	
	/* 開始設定該點為 Sensor 的步驟 */
	
	if(map[y][x].type != 'S'){
		
		map[y][x].type = 'S';	
		
	/* 將 range 內的 Node 設為 Covered */
		   
	    for(i = up; i <= down; i++){
	       	 for(j = left; j <= right; j++){
		        if((distance(x, y, i, j) <= squ_range) && (map[i][j].type == '.')){
			       	map[i][j].type = 'o';
			       	map[i][j].signal++;
				   --counter;
			    }
			    else if((distance(x, y, i, j) <= squ_range) && (map[i][j].type != '.')){
			    	map[i][j].signal++;	
			    }
		     }
	    }      
	}
	
	/* 將該點的Sensor取消 */
	
	else{
		
	/* 
	  將 range 內的 Node 減去該 Sensor 的訊號 
	  處理哪些 Node 是已經無訊號 Covered 的 Node 
	*/	
	    
	    map[y][x].type = 'o';  
	    
		for(i = up; i <= down; i++){
	       	 for(j = left; j <= right; j++){
		        if(distance(x, y, i, j) <= squ_range){
			       	map[i][j].signal--;
					
					/* 不在挖洞範圍內的Node，且訊號為0的時候 */
					
					if((map[i][j].signal == 0) && (map[i][j].type != ' ')){
					   map[i][j].type = '.';
				       ++counter;
				    }
			    }
		     }
	    }		  
	}
	       
	return ;
}

/* Calculate Distance */

int distance(int x, int y, int i, int j){
	
	return ((j - x) * (j - x) + (i - y) * (i - y));
	
}

/* 判斷是否 Full Cover */

void IsFullCover(void){
	
	if(counter > 0)
	   printf("\n\nNo Full Covered... (%d)\n\n", counter);
	else
	   printf("\n\n Full Covered !\n\n");
	   
	system("PAUSE");
	return ;      

}

/* 隨機布置 Sensor 的 Function */

void random_Sensor(Node **map, int m, int n){
	
	int number, x, y;
	
	do{
		
		printf("請輸入要亂數產生的Sensor數 : ");
		scanf("%d", &number);
		
		if((number > m * n) || (number < 0)){
			printf("\n\n 輸入的數值有誤, 請重新輸入...!\n\n");
			system("PAUSE");
		}
		else
		   break;
		
		system("cls");
	}while(1);
	
	/* 開始隨機撒 Sensor */
	
	for(srand(time(NULL)); number > 0; number--){
		
		x = rand() % n;
		y = rand() % m; 
		
		if(map[m - y - 1][x].type != 'S'){
			compute_Coverage(map, m, n, x, m - y - 1);
			totalSensor++;
		}
		else
		   number++;
	}
	
	show_Map(map, m, n);
	
	system("PAUSE");
	return ;
}

/* 挖洞設定 */

void set_Hole(Node **map, int m, int n){
	
	int x1, y1, x2, y2;
	
	do{
		
		show_Map(map, m, n);
		
		
		printf("請輸入洞的座標, 結束請輸入 -1\n");
		
		/* 設定挖洞的座標起始點 */
		
		printf("開始座標 x1 (1 < x1 <= %d) : ", n);	   
		scanf("%d", &x1);
		
		if(x1 == -1)
		    break;
		else if(x1 <= 0 || x1 > n){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		printf("開始座標 y1 (1 < y1 <= %d) : ", m);	   
		scanf("%d", &y1);
		
		if((y1 == -1))
		   break;
		else if(y1 <= 0 || y1 > m){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}   
		
		/* 設定挖洞的座標結束點 */
		
		printf("結束座標 x2 (1 < x2 <= %d) : ", n);	   
		scanf("%d", &x2);
		
		if(x2 == -1)
		    break;
		else if(x2 <= 0 || x2 > n){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		printf("結束座標 y2 (1 < y2 <= %d) : ", m);	   
		scanf("%d", &y2);
		
		if((y2 == -1))
		   break;
		else if(y2 <= 0 || y2 > m){
			printf("\n輸入範圍有誤! 請重新輸入!!\n\n");
			system("PAUSE");
			continue;	
		}    
		
		/* 開始挖洞 */
		
		dibble(map, m, n, x1 - 1, m - y1, x2 - 1, m - y2);
	
	} while(1);
	
	return ;
}

/* 挖洞機 */

void dibble(Node **map, int m, int n, int x1, int y1, int x2, int y2){

    int i, j;
    
    if(x1 - x2 > 0){
    	x1 = x1 ^ x2;
    	x2 = x1 ^ x2;
    	x1 = x1 ^ x2;
    }
       
    if(y1 - y2 > 0){
    	y1 = y1 ^ y2;
    	y2 = y1 ^ y2;
    	y1 = y1 ^ y2;
    }
	     
	
	for(j = x1; j <= x2; j++){
		for(i = y1; i <= y2; i ++){
			
			/* 若洞裡面有 Sensor */
			
			if(map[i][j].type == 'S'){
				compute_Coverage(map, m, n, j, i);
				//totalSensor++;
				deadSensor++;
			}
		}
	}
	
	for(j = x1; j <= x2; j++){
		for(i = y1; i <= y2; i++){
		    
		    /* 在挖洞內的無訊號Node不在判斷Full Coverage的範圍內 */
		    
			if(map[i][j].type == '.')
			   counter--;
			
			map[i][j].type = ' ';
		}
	}
    
	return ; 
} 

/* 輸出至檔案中 */

void exportToFile(Node **map, int m, int n){
	
	FILE *output;
	int i, j;
	int aliveNode = 0;
	
	if((output = fopen("WSN_FC.log", "wt")) == NULL)
	   printf("File can't not be created...\n\n");
	
	fprintf(output, "=======================================================\n"
	                "                          地圖\n"
					"=======================================================\n\n");
					
	for(i = 0; i < m; i++){
    	for(j = 0; j < n; j++){
    		
    		fprintf(output, "%c ", map[i][j].type);
    		
    		if(map[i][j].type == 'o')
			   aliveNode++;   
    		
			if(!((j + 1) % n))
    		   fprintf(output, "\n");
    	} 	
    }
	
	fprintf(output, "\n=======================================================\n"
	                "                        模擬資訊\n"
					"=======================================================\n");
	fprintf(output, "Map Node    總個數 : %d x %d = %d 個 Node\n", m, n, m * n);
	fprintf(output, "Sensor      總個數 : %d\n", totalSensor);
	fprintf(output, "Alive Sensor  個數 : %d\n",  totalSensor - deadSensor);
	fprintf(output, "Dead Sensor   個數 : %d\n", deadSensor);
	fprintf(output, "Covered Node  個數 : %d\n", aliveNode);
	fprintf(output, "UnCovered Node個數 : %d\n", counter);
	fprintf(output, "Sensor訊號的Range  : %d\n", range);
	fprintf(output, "是否 Full Coverage : %s\n", (counter > 0)? "No" : "Yes");		
	
	printf("\n\n*** 已輸出至 WSN_FC.log 檔案中!***\n\n");						

	fclose(output);
	system("PAUSE");
	return ;
}
