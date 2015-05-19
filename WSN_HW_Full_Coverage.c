#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
	char type;                   // Node�����A ( 'S' : Sensor, 'o' : ���T����Node, '.' : �L�T����Node) 
	unsigned int signal;         // Node���T���j�� 
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
	
	printf("�п�J�a�Ϫ��� m : "); 
	scanf("%d", &m);
	printf("\n�п�J�a�Ϫ��e n : "); 
	scanf("%d", &n);
	printf("\n�п�JSensor��Range(default = 5) : ");
	scanf("%d", &range);
	
	
	/* �гy�@�ӤG���}�C(Create Map) */
	
	Node **map = calloc(m, sizeof(Node *));	
	Node *array = calloc(m * n, sizeof(Node));
	
	for(i = 0; i < m; i++)
	   map[i] = &array[n * i];
	
	/* ��ܪ�l�a�� */
	
	init_Map(map, m, n);
    show_Map(map, m, n);
    
    /* �\��� */ 
    
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
	
	printf("\n\n******** �a * �� * �� * �l * �� ********\n\n");
	
    for(i = 0; i < m; i++){
    	for(j = 0; j < n; j++){    
    	    map[i][j].type = '.';
			map[i][j].signal = 0;  
    	} 	
    }
    
    /* �]�w Nodes Counter */
    
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
		
		printf("�п�J�n�G�U��Sensor�y��, �����п�J -1\n");
		
		/* �]�wx�y�� ��J-1�h�����]�w */
		
		printf("x (1 < x <= %d) : ", n);	   
		scanf("%d", &x);
		
		if(x == -1)
		    break;
		else if(x <= 0 || x > n){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		/* �]�wy�y��, ��J-1�����]�w */ 
		
		printf("y (1 < y <= %d) : ", m);	   
		scanf("%d", &y);
		
		if((y == -1))
		   break;
		else if(y <= 0 || y > m){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}   
		
		/* �]�w�����I�쥻���O Sensor */
		
		if(map[m - y][x - 1].type != 'S'){
			compute_Coverage(map, m, n, x - 1, m - y);
			totalSensor++;
		}  
		 
		/* �쥻���I�O Sensor , �h�n�������I Sensor ���]�m */ 
		  
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
		printf("\n�п�ܧA�n�ϥΪ�Function : \n\n"
		       "[1] ��ܦa��\n"
			   "[2] �]�wSensor��m\n"
			   "[3] �H�����m Sensor ��m\n" 
			   "[4] ���}\n" 
			   "[5] �p��O�_Full Coverage\n"
			   "[6] ��X���G���ɮפ�\n" 
			   "[0] �����{��\n\n > ");
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
			    printf("\n\n�Э��s��J���T���ﶵ!\n\n");
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
	
	/* �P�_ Sensor �� range �O�_�W�L��� */
		
	if(left < 0)
		left = 0;
		
	if(right >= n)
		right = n - 1;
		   
	if(up < 0)
		up = 0;
		   
	if(down >= m)
		down = m - 1;
	
	/* �]�w�����I���쥻�L�T���� Node */
	
	if(map[y][x].type == '.') 
		--counter;
		
	/* �]�w�����I���쥻�� Sensor 
		
	else if(map[y][x].type == 'S')
	    ++counter;	
	*/
	
	/* �}�l�]�w���I�� Sensor ���B�J */
	
	if(map[y][x].type != 'S'){
		
		map[y][x].type = 'S';	
		
	/* �N range ���� Node �]�� Covered */
		   
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
	
	/* �N���I��Sensor���� */
	
	else{
		
	/* 
	  �N range ���� Node ��h�� Sensor ���T�� 
	  �B�z���� Node �O�w�g�L�T�� Covered �� Node 
	*/	
	    
	    map[y][x].type = 'o';  
	    
		for(i = up; i <= down; i++){
	       	 for(j = left; j <= right; j++){
		        if(distance(x, y, i, j) <= squ_range){
			       	map[i][j].signal--;
					
					/* ���b���}�d�򤺪�Node�A�B�T����0���ɭ� */
					
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

/* �P�_�O�_ Full Cover */

void IsFullCover(void){
	
	if(counter > 0)
	   printf("\n\nNo Full Covered... (%d)\n\n", counter);
	else
	   printf("\n\n Full Covered !\n\n");
	   
	system("PAUSE");
	return ;      

}

/* �H�����m Sensor �� Function */

void random_Sensor(Node **map, int m, int n){
	
	int number, x, y;
	
	do{
		
		printf("�п�J�n�üƲ��ͪ�Sensor�� : ");
		scanf("%d", &number);
		
		if((number > m * n) || (number < 0)){
			printf("\n\n ��J���ƭȦ��~, �Э��s��J...!\n\n");
			system("PAUSE");
		}
		else
		   break;
		
		system("cls");
	}while(1);
	
	/* �}�l�H���� Sensor */
	
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

/* ���}�]�w */

void set_Hole(Node **map, int m, int n){
	
	int x1, y1, x2, y2;
	
	do{
		
		show_Map(map, m, n);
		
		
		printf("�п�J�}���y��, �����п�J -1\n");
		
		/* �]�w���}���y�а_�l�I */
		
		printf("�}�l�y�� x1 (1 < x1 <= %d) : ", n);	   
		scanf("%d", &x1);
		
		if(x1 == -1)
		    break;
		else if(x1 <= 0 || x1 > n){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		printf("�}�l�y�� y1 (1 < y1 <= %d) : ", m);	   
		scanf("%d", &y1);
		
		if((y1 == -1))
		   break;
		else if(y1 <= 0 || y1 > m){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}   
		
		/* �]�w���}���y�е����I */
		
		printf("�����y�� x2 (1 < x2 <= %d) : ", n);	   
		scanf("%d", &x2);
		
		if(x2 == -1)
		    break;
		else if(x2 <= 0 || x2 > n){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}
		
		printf("�����y�� y2 (1 < y2 <= %d) : ", m);	   
		scanf("%d", &y2);
		
		if((y2 == -1))
		   break;
		else if(y2 <= 0 || y2 > m){
			printf("\n��J�d�򦳻~! �Э��s��J!!\n\n");
			system("PAUSE");
			continue;	
		}    
		
		/* �}�l���} */
		
		dibble(map, m, n, x1 - 1, m - y1, x2 - 1, m - y2);
	
	} while(1);
	
	return ;
}

/* ���}�� */

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
			
			/* �Y�}�̭��� Sensor */
			
			if(map[i][j].type == 'S'){
				compute_Coverage(map, m, n, j, i);
				//totalSensor++;
				deadSensor++;
			}
		}
	}
	
	for(j = x1; j <= x2; j++){
		for(i = y1; i <= y2; i++){
		    
		    /* �b���}�����L�T��Node���b�P�_Full Coverage���d�� */
		    
			if(map[i][j].type == '.')
			   counter--;
			
			map[i][j].type = ' ';
		}
	}
    
	return ; 
} 

/* ��X���ɮפ� */

void exportToFile(Node **map, int m, int n){
	
	FILE *output;
	int i, j;
	int aliveNode = 0;
	
	if((output = fopen("WSN_FC.log", "wt")) == NULL)
	   printf("File can't not be created...\n\n");
	
	fprintf(output, "=======================================================\n"
	                "                          �a��\n"
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
	                "                        ������T\n"
					"=======================================================\n");
	fprintf(output, "Map Node    �`�Ӽ� : %d x %d = %d �� Node\n", m, n, m * n);
	fprintf(output, "Sensor      �`�Ӽ� : %d\n", totalSensor);
	fprintf(output, "Alive Sensor  �Ӽ� : %d\n",  totalSensor - deadSensor);
	fprintf(output, "Dead Sensor   �Ӽ� : %d\n", deadSensor);
	fprintf(output, "Covered Node  �Ӽ� : %d\n", aliveNode);
	fprintf(output, "UnCovered Node�Ӽ� : %d\n", counter);
	fprintf(output, "Sensor�T����Range  : %d\n", range);
	fprintf(output, "�O�_ Full Coverage : %s\n", (counter > 0)? "No" : "Yes");		
	
	printf("\n\n*** �w��X�� WSN_FC.log �ɮפ�!***\n\n");						

	fclose(output);
	system("PAUSE");
	return ;
}
