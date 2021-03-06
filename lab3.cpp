#include<GL/glut.h>
#include<iostream>

#define max 100

struct color {
	int r,g,b;
};
color x[] = {{0,1,1},
	     {0,1,1},
	     {0,1,1},
	     {0,1,1},
	     {0,1,1},
	     {0,1,1},
	     {0,1,1}};

struct line {
	int len;
	color c;
};
line ln[max],sortln[max],temp[max]; 

int min=0,count=0,finished=0;
int sorttype=0,inptype=0;
void drawlines();
void input(int);

void delay(){
	int i =999999;
	while(i--);
}

int partition(int l,int r){
	line temp;
	int i,j,pivot;
	pivot=sortln[l].len;
	i=l+1;
	j=r;
	while(i<=j){
		while(pivot>=sortln[i].len && i<=r)
			i++;
		while(pivot<=sortln[j].len && j>l)
			j--;
		if(i<j){
			temp=sortln[i];
			sortln[i]=sortln[j];
			sortln[j]=temp;
			glClear(GL_COLOR_BUFFER_BIT);
			drawlines();
			glutSwapBuffers();
		}
	}
	temp=sortln[l];
	sortln[l]=sortln[j];
	sortln[j]=temp;
	glClear(GL_COLOR_BUFFER_BIT);
	drawlines();
	glutSwapBuffers();
	return j;
}
void quicksort(int l,int r){
	int pos;
	if(l<r){
		pos=partition(l,r);
		quicksort(l,pos-1);
		quicksort(pos+1,r);
	}
}


void sort(){
	line temp;
	int a=0;
	switch(sorttype){
	
	
	case 0:quicksort(0,max-1);
		   break;
        case 1:return;
                   break;
	}
}

void drawlines(){
	int start=50;
	for(int i=0;i<max;i++){
		glColor3f(sortln[i].c.r,sortln[i].c.g,sortln[i].c.b);
		glBegin(GL_LINES);
		glVertex2f(start,10);
		glVertex2f(start,10+sortln[i].len);
		glEnd();
		start+=10;
	}
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,1,0);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);
	glLineWidth(5);
	drawlines();
	glutSwapBuffers();
	sort();
}

void randomize(){
int a;
	for(int i=0;i<max;i++){
		ln[i].len=(rand()%500);
		a=rand()%7;
		ln[i].c=x[a];
	}
}
void choice(int ch){
	sorttype=ch;
	count=0;min=0;
	for(int i=0;i<max;i++)
	sortln[i]=ln[i];
	display();
	
}

int main(int argc,char** argv){
	randomize();
	for(int i=0;i<max;i++)
		sortln[i]=ln[i];
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(900,600);
	glutCreateWindow("sort");
	glutCreateMenu(choice);
	glutAddMenuEntry("quick sort",0);
        glutAddMenuEntry("exit",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutMainLoop();
}
