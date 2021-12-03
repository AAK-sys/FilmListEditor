#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _movienode
{   
  char title[35];
  char genre[35];
  double duration;
  struct _movienode *next;
} movieNode;

movieNode *createmovieNode(char *title, char *genre, double duration){
  
  movieNode *newNode = (movieNode*) malloc(sizeof(movieNode));
  
  strcpy(newNode->title, title);
  strcpy(newNode->genre, genre);
  newNode->duration=duration;
  
  if(title==NULL||genre==NULL){return NULL;}
  
  return newNode;
}

int insertmovie(movieNode* *head, movieNode *newNode, int position){
  
  int Cpos=1;
  movieNode *current=*head;
  movieNode *pre;
  
  if (*head==NULL){
  
    *head=newNode;
    return 1;
  
  }else{
    
    while(Cpos!=position && current!=NULL){
      pre=current;
      current=current->next;
      Cpos++;
    }
    if(current==NULL){pre->next=newNode;}
    else{
      newNode=current->next;
      current->next=newNode;
    }
    return 1;
  }
  
  return 1;
}

double computeDuration(movieNode *head){
  
  double total=0;

  if(head==NULL){return -1;}
  
  
  
  movieNode *current=head;

  while(current!=NULL){
    total+=current->duration;
    current=current->next;
  }
  
  return total;
}

void printList(movieNode *head){
  
  movieNode *current=head;
  int count=1;

  if(current==NULL){printf("the list is empty\n");return;}

  printf("\nyour movie list:\n\n");

  while(current!=NULL){
    printf("movie #%d\n",count++);
    printf("movie name: %s\n",current->title);
    printf("movie genre: %s\n",current->genre);
    printf("movie duration: %0.2lf\n",current->duration);
    current=current->next;
    printf("\n");
  }
}
movieNode *loadwatchlist(){
  
  movieNode *head;
  
  movieNode *current;
  
  FILE *fp;
 
 char check[100];
 char duration[100];
 char filename[35];
 char name[35];
 char type[35];
 double time;
 int Cpos=1;
 do{
 printf("enter the name of file to save your movies in:\t");
 
 fgets(check, 35, stdin);
 sscanf(check, "%s", filename);
  
 fp=fopen(filename,"r");
 }while(fp==NULL);
  while(!feof(fp)){
    fgets(name,35,fp);
    strtok(name, "\n");
    fgets(type, 35, fp);
    strtok(type, "\n");
    fgets(duration,sizeof(duration), fp);
    sscanf(duration, "%lf", &time);
    insertmovie(&head, createmovieNode(name, type, time),Cpos);
    Cpos++;
  }
 return head;

}

movieNode *removemovie(movieNode *head, movieNode *remNode){

  movieNode *current=head;
  movieNode *removed;

  while(current->next!=remNode){
    current=current->next;
    if(current==NULL){return NULL;}
  }
  
  removed=current->next;
  current->next=current->next->next;
  removed->next=NULL;
  
  return removed;

}

int deletemovie(movieNode *head, movieNode *delNode){
  
  movieNode *removed=removemovie(head, delNode);
  
  if(removed==NULL){printf(delNode->title,"%s, movie not found");return 0;}
  
  else{
    free(removed);
  }
  
  return 1;

}

movieNode *getNode(movieNode *head, char *search){

  int Cpos=1;
  int i;
  char *temp;
  char dispo[35];
  

  movieNode *current=head;

  strtok(search," ");

  while(current!=NULL){
    strcpy(dispo, current->title);
    strtok(dispo, " ");
    if (strcmp(search, dispo)==0){break;}
    Cpos++;
    current=current->next;
  }
  return current;
}

int getNodePosition(movieNode *head, char *search){

  int Cpos=1;
  int i;
  char *temp;
  char dispo[35];
  
  if(head==NULL){return -1;}

  movieNode *current=head;

  strtok(search," ");

  while(current!=NULL){
    strcpy(dispo, current->title);
    strtok(dispo, " ");
    if (strcmp(search, dispo)==0){break;}
    Cpos++;
    current=current->next;
    if(current==NULL){printf("make sure you entered a valid movie title(Captialized), ");return -1;}
  }

  printf("%s\n",current->title);
  printf("%s\n",current->genre);
  printf("%0.2lf\n",current->duration);

  return Cpos;
}

int options(){

  char check[100];
  int option;

  printf("1)Print watchlist\n2)Show duration\n3)Search by title\n4)Move a movie up\n5)Move a movie down\n6)Remove a movie\n7)Save watchlist\n8)Load watchlist\n9)Go to movie Library\n10)Quit\n");
  
  fgets(check, 100, stdin);

  if(sscanf(check, "%d", &option)==0){options();}
  
  return option;

}

int savewatchlist(movieNode *head){

  if (head==NULL){return -1;}
 
 FILE *fp;
 
 char check[100];
 char filename[35];
 char buffer[100];

 movieNode *current=head;

 printf("enter the name of file to save your movies in:");
 
 fgets(check, 35, stdin);
 sscanf(check, "%s", filename);

 fp=fopen(filename,"w+");

 while(current!=NULL){
  fputs(current->title, fp);
  fputc('\n', fp);
  fputs(current->genre, fp);
  fputc('\n', fp);
  snprintf(buffer, sizeof buffer, "%0.2lf", current->duration);
  fputs(buffer, fp);
  if(current->next!=NULL){fputc('\n', fp);}
  current=current->next;
 }
 fclose(fp);
  return 1;
}

void insertatStart(movieNode **head,movieNode *newNode){
  
  if(head==NULL){
    *head=newNode;
  }else{
    newNode->next=*head;
    *head=newNode;
  }
}

void insertatEnd(movieNode **head,movieNode *newNode){

  movieNode *current=*head;

  if(head==NULL){
    *head=newNode;
  }
  else{
    while(current->next!=NULL){
      current=current->next;
    }
    current->next=newNode;
  }
}


void insertAT(movieNode **head,movieNode *newNode,int pos){
  
  int Cpos=-1;

  movieNode *current=*head;

  if(head==NULL){insertatStart(head, newNode);}
  
  while(Cpos!=pos && current!=NULL){
      Cpos++;
      current=current->next;
  }
  if(current==NULL){current=newNode;}
  newNode->next=current->next;
  current->next=newNode;
}

void userInsert(movieNode **head){
  
  char name[35];
  char genre[35];
  double time;
  int option;
  int position;
  char check[100];
  char check1[100];
  char check2[100];
  char check3[100];
  char check4[100];

  movieNode *newNode;

    printf("enter the name of movie:\n");
    fgets(check1, 35, stdin);
    sscanf(check1, "%s", name);
  
    printf("enter the name of the movie's genre\n");
    fgets(check2, 35, stdin);
    sscanf(check2, "%s", genre);

  while(sscanf(check3, "%lf",&time)==0){
    printf("enter the duration of the movie in hours\n");
    fgets(check3, 8, stdin);
  }
  newNode=createmovieNode(name, genre, time);
  printf("1}Add movie to the end\n2)Add movie at the beginning\n3)Insert movie at a specific position\n");

  fgets(check, 100, stdin);
  sscanf(check, "%d", &option);

  switch(option){
    case 1:
      insertatEnd(head,newNode);
      break;    
    case 2:
      insertatStart(head, newNode);
      break;
    case 3:
      do{
        printf("please enter a position\n");
        fgets(check4, 100, stdin);
        sscanf(check4,"%d", &position);
      }while(position<=0);
      insertAT(head,newNode,position);
      break;
    default:
      userInsert(head);
      break;
  }
}

void movielib(movieNode **head){

  int option;
  char name[35];
  char check[100];

  printf("1)View all movies\n2)Search by title\n3)Add a movie to watchlist\n4)Back to watchlist\n");

  fgets(check, 100, stdin);
  sscanf(check, "%d", &option);

  if (option==4){return;}

  switch(option){
    case 1:
      printList(*head);
      break;
    case 2:
      printf("enter the movie name\n");
      fgets(check, 35, stdin);
      sscanf(check, "%s", name);
      if(getNodePosition(*head, name)==-1){printf("movie not found\n");}
      break;
    case 3:
      userInsert(head);
      break;
    default:
      movielib(head);
      break;
  }
}

void moveup(movieNode *head){
  char check[100];
  char name [35];

  movieNode*current=head;
  movieNode *temp;
  movieNode *prev;
  
  

  printf("enter the name of the movie you want to move up the list(Captialized)\n");
  
  fgets(check, 35, stdin);
  sscanf(check, "%s", name);
  
  temp=getNode(head, name);
  if(temp==head){printf("the movie is already at the top of the list\n");return;}
  if(temp==NULL){printf("such movie doesn't exist\n");return;}

  while(current!=temp && current!=NULL){
    if(current->next->next==temp){prev=current;}
    current=current->next;
  }
  prev->next->next=current->next;
  current->next=prev->next;
  prev->next=current;
}

void movedown(movieNode *head){

  char check[100];
  char name [35];

  movieNode*current=head;
  movieNode *temp;
  movieNode *prev;
  movieNode *prevprev;

  printf("enter the name of the movie you want to move down the list(Captialized)\n");
  
  fgets(check, 35, stdin);
  sscanf(check, "%s", name);
  temp=getNode(head, name);
  
  if(temp->next==NULL){printf("the movie is already at the bottom of the list\n");return;}
  if(temp==NULL){printf("such movie doesn't exist\n");return;}

  while(current!=NULL && current!=temp){
    if(current->next->next==temp){prev=current;}
    current=current->next;
  }
  
  while(current!=temp->next && current!=NULL){
    if(current->next==temp){prev=current;}
    current=current->next;
  }
  temp->next=current->next;
  current->next=temp;
  prev->next=current;
}

void close(movieNode *head){

  movieNode *temp;
  movieNode *current;

  if(head==NULL){return;}

  while(current!=NULL){

  temp=current;

  current=current->next;

  free(temp);

  }
}


int main(void) {
    
  movieNode *Hnode=NULL;
  movieNode *temp;
  do{
  char check[100];
  char name[35];
  
  int option=options();
  
  switch(option){
    case 1:
      printList(Hnode);
      break;
    case 2:
      if(computeDuration(Hnode)==-1){printf("the list is empty\n");}
      else{printf("\nthe total duration of the movie list is %0.2lf hours\n\n",computeDuration(Hnode));}
      break;
    case 3:
      printf("enter the movie name\n");
      fgets(check, 35, stdin);
      sscanf(check, "%s", name);
      if(getNodePosition(Hnode, name)==-1){printf("movie not found\n");}
      break;
    case 4:
      moveup(Hnode);
      break;
    case 5:
      movedown(Hnode);
      break;
    case 6:
      printf("enter the name of the movie you want to remove(Captialized)\n");
      fgets(check, 35, stdin);
      sscanf(check, "%s", name);
      temp=getNode(Hnode, name);
      if(temp==NULL){printf("such movie doesn't exist\n");break;}
      deletemovie(Hnode,temp);
      break;
    case 7:
      savewatchlist(Hnode);
      break;
    case 8:
      Hnode=loadwatchlist();
      break;
    case 9:
      movielib(&Hnode);
      break;
    case 10:
    close(Hnode);
    exit(0);
    default:
      break;
  }
  }while(true);
  return 0;
}