//
//  main.c
//  memory.c
//
//  Created by Official on 20/02/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include<stdio.h>
#include <limits.h>
#include <string.h>
#include<stdlib.h>

#define SIZEOFHEAP 10000


typedef struct Node {
    char name[10];
  int addr;
  int size;
    int *p;
  struct Node *nxt;
}Node;


typedef struct HEAP {
  int memory[SIZEOFHEAP];
}HEAP;
HEAP H;

void init_AL(Node **al){
  *al=NULL;
}

void init_FL(Node **fl){
  Node *ptr = (Node*)malloc(sizeof(Node));
  ptr->addr = 0;
    ptr->p=&(H.memory[ptr->addr]);
  ptr->size=SIZEOFHEAP;
  ptr->nxt = NULL;
  *fl = ptr;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  LISTS  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Node *FL;
Node *AL;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void printfl(Node *fl){
    Node *ptr=fl;
    printf("\n\n\n");
    printf("---------------->   FREE LIST   <-------------------\n");
    while(ptr){
        printf("Address =  %d,size = %d ",ptr->addr,ptr->size);
        if(ptr->nxt!=NULL){
            printf(" --> ");}
        ptr = ptr->nxt;
    }
}

void printal(Node *al){
    Node *ptr=al;
    printf("\n\n\n");
        printf("---------------->   ALLOCATE LIST   <-------------------\n");
        while(ptr){
            printf("Address =  %d,size = %d,Name = %s ",ptr->addr,ptr->size,ptr->name);
            if(ptr->nxt!=NULL){
                printf(" --> ");
            }
            ptr = ptr->nxt;
        }
    
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void AddAL(Node *node,Node **al){
  if(*al==NULL){
    *al = node;
  }
  else{
    Node *ptr=*al;
    while(ptr->nxt){
      ptr = ptr->nxt;
    }
    ptr->nxt=node;
  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MEMORY ALLOC>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Node *memAlloc(int sizeofnode,Node **fl){
  Node *ptr,*prev,*loc,*locprev;
  Node *ret_val;
  ptr = *fl;
  prev = NULL;
  loc = NULL;
  locprev=NULL;
  int diff = INT_MAX;
  while(ptr){
    int sz = ptr->size;
    int dif = sz-sizeofnode;
    if(dif<diff && dif>=0){
      diff = dif;
      locprev = prev;
      loc = ptr;
    }
    prev = ptr;
    ptr=ptr->nxt;

  }
    //IMPROVE FROM HERE
  ret_val = (Node*)malloc(sizeof(Node));
    if(loc!=NULL){

        if(prev == *fl){
          if(prev->size>=sizeofnode){
          Node *nptr = *fl;
          ret_val->addr = nptr->addr;
              ret_val->p=&(H.memory[ret_val->addr]);
          ret_val->size=sizeofnode;
          ret_val->nxt=NULL;
          
          nptr->addr = nptr->addr+sizeofnode;
              nptr->p=&(H.memory[nptr->addr]);
          nptr->size=nptr->size-sizeofnode;
              if(nptr->size==0){
                  *fl=nptr->nxt;
              }
          }
        }
        else{
          if(loc==NULL){
              printf("Not Enough Size To Allocate\n");
              return NULL;
          }
        ret_val->addr=loc->addr;
          ret_val->p=&(H.memory[ret_val->addr]);
          ret_val->size = sizeofnode;
          if(locprev==NULL){
              printf("locprev null ");
               Node *nptr = *fl;
              nptr->addr+=sizeofnode;
              nptr->p=&(H.memory[nptr->addr]);
              nptr->size-=sizeofnode;
              if(nptr->size==0){
                  nptr=nptr->nxt;
              }
              *fl = nptr;
          }
          else{
               printf("locprev  not null ");
              loc->addr+=sizeofnode;
              loc->p=&(H.memory[loc->addr]);
              loc->size-=sizeofnode;
              if(loc->size==0){
                  locprev->nxt=loc->nxt;
                  free(loc);
              }
          }

          ret_val->nxt=NULL;
        }
    }
    else{
        printf("Not Enough Size To Allocate\n");
                     return NULL;
    }
  return ret_val;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Freemem(Node *fr,Node **fl,Node **al){
  Node *ptr,*prev;
  int p=0,n=0;
  ptr = *fl;
  prev = NULL;
    if(*al==NULL){
        return;
    }
    //...............................................
    
    Node *aptr = *al;
    Node *aprev = NULL;
    while(aptr->addr != fr->addr){
        aprev = aptr;
        aptr = aptr->nxt;
    }
    if(aprev==NULL){
        *al = fr->nxt;
    }
    else{
        aprev->nxt=aptr->nxt;
    }
    
    //........................................
  while((ptr!=NULL)&&(ptr->addr<fr->addr)){
    prev = ptr;
    ptr = ptr->nxt;
  }
    if(prev == NULL && ptr!=NULL){
      if(fr->addr+fr->size == ptr->addr){
          ptr->addr = fr->addr;
          ptr->p=&(H.memory[ptr->addr]);
          ptr->size+=fr->size;
          free(fr);
      }
      else{
      fr->nxt = *fl;
      *fl = fr;
      }
  }
  else if(ptr==NULL){
      if(prev!=NULL){
          if(prev->addr+prev->size==fr->addr){
              prev->size+=fr->size;
              free(fr);
          }
          else{
              prev->nxt = fr;
          }
      }
      else{
          fr->nxt=NULL;
          *fl=fr;
      }
  }
  else{
    if(prev->addr+prev->size == fr->addr){
      prev->size+=fr->size;
      p=1;
    }
    if(fr->addr+fr->size==ptr->addr){
        ptr->addr = fr->addr;
        ptr->p=&(H.memory[ptr->addr]);
        ptr->size+=fr->size;
      n=1;
      }
      if(p==1 && n==1){
          prev->size+=ptr->size;
          prev->size-=fr->size;
          prev->nxt=ptr->nxt;
          free(ptr);
          free(fr);
      }
      else if(p==1 || n ==1){
          free(fr);
      }
      else{
          fr->nxt=ptr;
          prev->nxt=fr;
      }
    }
  }


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Node* newmalloc(int sizeofnode){
    Node *retval;
    retval = memAlloc(sizeofnode, &FL);
    AddAL(retval, &AL);
    return retval;
    
}

void newfree(Node *ptr){
    Freemem(ptr, &FL,&AL);
}





//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(void){
  printf("HI\n");
    init_FL(&FL);
    init_AL(&AL);
    printal(AL);
    printfl(FL);
    printf("\n");
    char pname[10];
    int choice,f=1,sz,nf=0;
    int ch2;
    do
    {
        printf("***************************\n");
        printf("1.Malloc\n");
        printf("2.Free\n");
        printf("3.Print allocated list\n");
        printf("4.Print free list\n");
        printf("5.Print Both The Lists\n");
        printf("6.Access\n");
        printf("7.Quit\n");
        printf("***************************\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                //search for name
                do{
                    nf=0;
                printf("Enter Name and Size Of The Pointer : \n");
                scanf("%s%d",pname,&sz);
                    while(sz<=0){
                        printf("Enter Correct Size >0\n");
                        scanf("%d",&sz);
                    }
                Node *fnd=AL;
                while((!nf) && fnd){
                    if(strcmp(fnd->name, pname)==0){
                        nf=1;
                        printf("Name Already Exists \n");
                    }
                    fnd=fnd->nxt;
                }
                }while(nf==1);
                
                Node *new=newmalloc(sz);
                if(new!=NULL){
                strcpy(new->name, pname);
                }
                break;
            case 2:
                if(AL!=NULL){
                    printf("Enter name of pointer\n");
                    scanf("%s",pname);
                    Node *fr = NULL;
                    do{
                        nf=0;
                        Node *fnd=AL;

                        while((!nf) && fnd){
                            if(strcmp(pname, fnd->name)==0){
                                nf=1;
                                fr=fnd;
                            }
                            fnd=fnd->nxt;
                        }
                       if(nf==0){
                            printf("No Name Found \nEnter The Name\n");
                            scanf("%s",pname);
                        }
                    }while(nf==0);
                    if(fr!=NULL){
                        newfree(fr);
                    }
                }
                else{
                    printf("The Allocated List is Empty Try To Insert First\n");
                }
                break;
            case 3:
                printf("\n\n");
                printal(AL);
                printf("\n\n");
                break;
            case 4:
                printf("\n\n");
                printfl(FL);
                printf("\n\n");
                break;
            case 5:
                printf("Both The Lists Are : \n\n" );
                printal(AL);
                printf("\n\n");
                printfl(FL);
                printf("\n\n\n");
                break;
            case 6:
                if(AL!=NULL){
                    nf=0;
                    do{
                    printf("Enter Name of The Pointer\n");
                    scanf("%s",pname);
                        Node *ptr=AL;
                        while(ptr){
                            if(strcmp(ptr->name, pname)==0){
                                nf=1;
                                break;
                            }
                            ptr=ptr->nxt;
                        }
                        if(nf==1){
                            printf("1.To Print Data\n");
                            printf("2.To Insert Data");
                            scanf("%d",&ch2);
                            switch(ch2){
                                case 1:
                                    printf("Name is : %s\n",ptr->name);
                                    printf("Address is : %d\n",ptr->addr);
                                    printf("Data are :\n");
                                    for(int i=0;i<ptr->size;i++){
                                        printf("At Address %d : %d\n",ptr->addr+i,ptr->p[i]);
                                    }
                                    break;
                                case 2:
                                    printf("Enter the Number of Elements you want to enter (but <= %d)\n",ptr->size);
                                    scanf("%d",&ch2);
                                    while(ch2>ptr->size){
                                        printf("Enter the Number of Elements you want to enter (but <= %d)\n",ptr->size);
                                        scanf("%d",&ch2);
                                    }
                                    printf("Enter The Elements You Want :\n");
                                    for(int i=0;i<ch2;i++){
                                        scanf("%d",&(ptr->p[i]));
                                    }
                            }
                        }
                        
                    }while(nf==0);
                }
                else{
                    printf("The Allocated List is Empty Try To Insert First\n");
                }
                break;
                
            case 7:
                f=0;
                break;
        }
    }while(f==1);
    return 0;
}

