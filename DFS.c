#include <stdio.h>
#include <stdlib.h>
#define SIZE 100


int matrisBoyutBul(FILE *);
void matrisOku(char **,FILE *,int);
void DFS(char **,int **,int,int,int);

int isThereWay=0;//global degisken


int main(){
	FILE *fp=fopen("data.txt","r");
	char **Maze;//labirentimiz
	char B[100][100];	//ekrana bastirilacak olan labirent
	int i,j;
	int **visited;
	int n=matrisBoyutBul(fp);//matrisimizin boyutunu ogrendik
	Maze=(char**)malloc(sizeof(char*)*n);
	visited=(int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++){
		Maze[i]=(char*)malloc(sizeof(char)*n);
		visited[i]=(int*)malloc(sizeof(int)*n);
	}//maze ve visited matrislerine dinamik yer actik
	fseek(fp,0,SEEK_SET);	
	matrisOku(Maze,fp,n);//matris okundu
	printf("input matrisi:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%c\t",Maze[i][j]);
			visited[i][j]=0;
		}
		printf("\n");
	}	
	DFS(Maze,visited,1,1,n-2);//dfs ile yol olup olmadigi bulundu
	printf("\n");
	if(isThereWay==1){
		visited[n-2][n-2]=1;
		printf("Yol var...\n");
	}else{
		printf("yol yok...\n");
	}
	//Simdi cikis matrisimizi olusturalim...
	for(i=0;i<n;i+=2){
		for(j=0;j<n;j+=2){
			B[i][j]='+';
		}
	}
	for(i=0;i<n;i+=2){
		for(j=1;j<n;j+=2){
				B[i][j]='-';
				B[j][i]='|';							
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(Maze[i][j]=='1'){
				B[i][j]=' ';
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(Maze[i][j]=='B' && visited[i][j]==1){
				B[i][j]='I';
			}
		}
	}
	B[1][1]='*';
	B[n-2][n-2]='X';
	printf("\n");
	printf("labirentimiz ve sonuc:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%c",B[i][j]);
		}printf("\n");
	}		
	
	
	
	getch();
	return 0;

}
int matrisBoyutBul(FILE *fp){//dosyadan okunacak matrisin boyutunu bulur
	char buf[100];
	int k=0;
	int t=0;
	fscanf(fp,"%s",buf);
	while(buf[k]!='\0'){
		if(buf[k]==','){
			t=t+1;	
		}
		k=k+1;
	}
	t=t+1;//virgul sayisinin bir fazlasi kadardir matrisin satir ve sutun sayisi
	return t;
}
void matrisOku(char **Maze,FILE *fp,int n){//dosyadaki matris okunur
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(fp,"%c ,",&Maze[i][j]);
		}
	}
}

void DFS(char **Maze,int **visited,int x,int y,int n){//dfs ile rekörsif gezerek yol var mi diye bakilir
	if(x!=n || y!=n){
		if(Maze[x][y]!='0'){
			if(visited[x][y]==0 && isThereWay==0){
				visited[x][y]=1;
				DFS(Maze,visited,x,y+1,n);
				DFS(Maze,visited,x+1,y,n);
				DFS(Maze,visited,x,y-1,n);
				DFS(Maze,visited,x-1,y,n);
			}	
		}
	}else{
		isThereWay=1;//yolu bulduk
	}
}



