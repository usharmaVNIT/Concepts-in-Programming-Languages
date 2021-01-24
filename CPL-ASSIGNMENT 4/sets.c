//
//  main.c
//  CPLASSIGNMENT4
//
//  Created by Official on 23/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>


typedef enum{
    FAILURE,SUCCESS
} Status;

typedef struct{
    char **list;
    int numItems;
    int LENGTH_OF_MAP;
} SDS;

// Ans 6

SDS *create(){
    SDS *ptr = (SDS*)malloc(sizeof(SDS));
    printf("\n\n Set Created \n\n");
    return ptr;
}

void init_Set(SDS *s){
    s->numItems=0;
    s->list = (char**)malloc(sizeof(char*)*5);
    s->LENGTH_OF_MAP = 5;
    for(int i=0;i<s->LENGTH_OF_MAP;i++){
        s->list[i] = NULL;
    }
}

int hash(char *st,int len){
    unsigned long l = strlen(st);
    long int s = 0;
    for(int i =0;i<l;i++){
        s+=st[i];
    }
    return s%len;
}

Status ADD(char *word,char **list,int len){
    if(list !=NULL){
        int index = hash(word,len);
        int loc = -1;
        while(list[index]!=NULL){
            if(strcmp(word, list[index])==0){
                return FAILURE;
            }
            if(loc < 0 && strcmp("____FAKE VALUE___", list[index])==0){
                loc = index;
            }
            index = (index+1)%len;
        }
        if(loc < 0){
            loc = index;
        }
        list[loc] = word;
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
}

// We will make sure that the list will never be full and to do so we will
// add the existing list into a new list

char** __rehash(char **oldList,char **newList,int oldLen,int newLen){
    for(int i=0;i<oldLen;i++){
        if(oldList[i]!=NULL && strcmp("____FAKE VALUE___", oldList[i])!=0){
            ADD(oldList[i], newList,newLen);
        }
    }
    return newList;
}
// Ans 7

void add(char *word,SDS *s){
    int len = s->LENGTH_OF_MAP;
    if(ADD(word, s->list,len)==SUCCESS){
        s->numItems+=1;
        int loadfactor = (s->numItems/len);
        if(loadfactor >=.75){
            char** newList = (char**)malloc(2*len*sizeof(char*));
            for(int i=0;i<2*len;i++){
                newList[i]=NULL;
            }
            newList = __rehash(s->list, newList, len, 2*len);
            free(s->list);
            s->list = newList;
            s->LENGTH_OF_MAP = (s->LENGTH_OF_MAP)*2;
        }
        printf("Item Added Successfully\n");
    }
    else{
        printf("Item Already Present in The SDS\n");
    }
}

// Ans 5

void build(SDS *s,char **list, int len){
    for(int i=0;i<len;i++){
        add(list[i],s);
    }
    printf("\n\nSuccessfully Builded\n\n");
}

void printset(SDS *s){
    int le = s->LENGTH_OF_MAP;
    printf("\n");
    for(int i=0;i<le-1;i++){
        if(s->list[i] != NULL && strcmp(s->list[i], "____FAKE VALUE___") != 0){
            printf("%s ==> ",s->list[i]);
        }
    }
    if(s->list[le-1] != NULL && strcmp(s->list[le-1], "____FAKE VALUE___") != 0){
        printf("%s \n",s->list[le-1]);
    }
    printf("\n");
}

Status __remove(char *word, char **list,int len){
    int index = hash(word,len);
    
    while(list[index] != NULL){
        if(strcmp(word, list[index])==0){
            int next_i;
            next_i = (index+1)%len;
            
            if(list[next_i] == NULL){
                list[index] = NULL;
            }
            else{
                list[index] = "____FAKE VALUE___";
            }
            return SUCCESS;
        }
        index = (index+1)%len;
    }
    return FAILURE;
}

// Ans 8

void delete(char *word,SDS *s){
    int len = s->LENGTH_OF_MAP;
    if(__remove(word, s->list,len) == SUCCESS){
        s->numItems--;
        float loadfactor = (float)(s->numItems)/len;
        if(loadfactor<= 0.25){
            int max2;
// Here We will make Sure That The List Length never becomes 0 As our orignal length was 5
            int x = len/2;
            if(x>5){
                max2 = x;
            }
            else{
                max2 = 5;
            }
            char **newList = (char**)malloc(sizeof(char*)*max2);
            for(int i=0;i<max2;i++){
                newList[i]=NULL;
            }
            int ol = len;
            newList = __rehash(s->list, newList, ol, max2);
            free(s->list);
            s->list = newList;
            s->LENGTH_OF_MAP = max2;
        }
        printf("Item Removed Successfully\n");
    }
    else{
        printf("Item is not present in SDS\n");
    }
}

Status __contains(char *word,char **list,int len){
    int index = hash(word,len);
    while(list[index] != NULL){
        if(strcmp(list[index], word) == 0){
            return SUCCESS;
        }
        index = (index+1)%len;
    }
    return FAILURE;
}

// Ans 1

Status contains(char *word,SDS *s){
    return __contains(word, s->list,s->LENGTH_OF_MAP);
}

// Ans 2

Status isEmpty(SDS *s){
    if(s->numItems == 0){
        return SUCCESS;
    }
    return FAILURE;
}

// Ans 3

// Ans 4

char** ENUMERATE(SDS *s){
    char **list;
    list = (char**)malloc(sizeof(char*)*s->numItems);
    for(int i=0;i<s->numItems;i++){
        list[i]=NULL;
    }
    int j=0;
    for(int i=0;i<s->LENGTH_OF_MAP;i++){
        if(s->list[i] != NULL && strcmp("____FAKE VALUE___", s->list[i]) !=0){
            list[j] = s->list[i];
            j++;
        }
    }
    return list;
}

int sizeofSet(SDS *s){
    return s->numItems;
}

// Ans 9
//  Here We Start With Union

char** lUnion(char **list1,char **list2,int l1,int l2){
    int maxNum = l1+l2;
    char **unionList = (char**)malloc(sizeof(char*)*maxNum);
    for(int i=0;i<maxNum;i++){
        unionList[i]=NULL;
    }
    for(int i=0;i<l1;i++){
        if(list1[i] != NULL && strcmp("____FAKE VALUE___", list1[i])!= 0){
            if(__contains(list1[i], list2, l2) == FAILURE){
                ADD(list1[i], unionList, maxNum);
            }
        }
    }
    for(int i=0;i<l2;i++){
        if(list2[i] != NULL && strcmp("____FAKE VALUE___", list2[i])!= 0){
            ADD(list2[i], unionList, maxNum);
        }
    }
    return unionList;
}

char** Setunion(SDS *s1,SDS *s2,int *len){
    if(s1->numItems == 0){
        if(s2->numItems == 0){
            *len = 0;
            return NULL;
        }
        *len = s2->LENGTH_OF_MAP;
        return s2->list;
    }
    else if(s2->numItems == 0){
        *len = s1->LENGTH_OF_MAP;
        return s1->list;
    }
    else{
        *len = s1->LENGTH_OF_MAP+s2->LENGTH_OF_MAP;
        return lUnion(s1->list, s2->list, s1->LENGTH_OF_MAP, s2->LENGTH_OF_MAP);
    }
}

// Ans 10
// Here We Start with intersection

char** lInter(char **list1,char **list2,int l1,int l2){
    int minlen = l1>l2?l2:l1;
    char **intersectionList = (char**)malloc(sizeof(char*)*minlen);
    for(int i=0;i<minlen;i++){
        intersectionList[i]=NULL;
    }
    for(int i=0;i<l1;i++){
        if(list1[i] != NULL && strcmp("____FAKE VALUE___", list1[i])!= 0){
            if(__contains(list1[i], list2, l2) == SUCCESS){
                ADD(list1[i], intersectionList, minlen);
            }
        }
    }
    return intersectionList;
}

char** Setintersection(SDS *s1,SDS *s2, int *len){
    if(s1->numItems == 0 || s2->numItems == 0){
        *len=0;
        return NULL;
    }
    else{
        *len = s1->LENGTH_OF_MAP>s2->LENGTH_OF_MAP?s2->LENGTH_OF_MAP:s1->LENGTH_OF_MAP;
        return lInter(s1->list, s2->list, s1->LENGTH_OF_MAP, s2->LENGTH_OF_MAP);
    }
}

// Ans 11
// For Difference

char** lDiff(char **list1,char **list2,int l1,int l2){
    char **inter = lInter(list1, list2, l1, l2);
    int li = l1>l2?l2:l1;
    char **difflist = (char**)malloc(sizeof(char*)*l1);
    for(int i=0;i<l1;i++){
        difflist[i]=NULL;
    }
    for(int i=0;i<l1;i++){
        if(list1[i] != NULL && strcmp("____FAKE VALUE___", list1[i]) !=0){
            if(__contains(list1[i], inter, li) == FAILURE){
                ADD(list1[i], difflist, l1);
            }
        }
    }
    return difflist;
}

char **Setdifference(SDS *s1,SDS *s2,int *len){
    *len = s1->LENGTH_OF_MAP;
    return lDiff(s1->list, s2->list, s1->LENGTH_OF_MAP, s2->LENGTH_OF_MAP);
}

// Ans 12
// For Subset

Status lSubset(char **list1,char **list2,int l1,int l2){
    for(int i=0;i<l2;i++){
        if(list2[i] != NULL && strcmp("____FAKE VALUE___", list2[i]) !=0){
            if(__contains(list2[i], list1, l1) == FAILURE){
                return FAILURE;
            }
        }
    }
    return SUCCESS;
}

Status Setsubset(SDS *s1,SDS *s2){
    if(s2->numItems == 0){
        return SUCCESS;
    }
    else{
        return lSubset(s1->list, s2->list, s1->LENGTH_OF_MAP, s2->LENGTH_OF_MAP);
    }
}

int main(void){
    SDS *s;
    s = create();
    init_Set(s);
    char *l1[] = {"i1","i2","i3","i4","i5","i6","tes1","qweq","asdf","qwer","zxcv","wert","sdfg","xcvb"};
    build(s, l1, 14);
    printset(s);
    SDS *s2 = create();
    init_Set(s2);
    char *l2[] = {"tes1","asdf","qwer","afsafas"};
    build(s2, l2, 4);
    printset(s2);
    int ul,il;
    printf("Union\n");
    char **uni = Setunion(s, s2,&ul);
    for(int i=0;i<ul;i++){
        if(uni[i]!=NULL){
            printf("%s  ",uni[i]);
        }
    }
    printf("\n");
    
    printf("Intersection\n");
    char **inter = Setintersection(s, s2,&il);
    for(int i=0;i<il;i++){
        if(inter[i]!=NULL){
            printf("%s  ",inter[i]);
        }
    }
    printf("\n");
    printf("\n\n");
    int dl;
    char **diff = Setdifference(s, s2,&dl);
    printf("%d\n",dl);
    printf("\n\n************ Set Difference of Set S1 and Set S2 is ************ \n\n");
    for(int i=0;i<dl;i++){
        printf("%s - ",diff[i]);
    }
    printf("\n");
    
    printf("\n************Checking for subset************\n\n\n");
    if(Setsubset(s, s3)==SUCCESS){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    if(Setsubset(s, s2)==SUCCESS){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    
    printf("\n\n************Removing Elements From Set 1************\n\n\n");
    int initial_length = s->LENGTH_OF_MAP;
    char *rm[] = {"i1","i2","i3","i4","i5","i6","tes1","qweq","hello","qwer","zxcv","wert","asdf","sdfg"};
    for(int i=0;i<14;i++){
        delete(rm[i], s);
    }
    printset(s);
    printf("\nInitial Length Of Set was %d\n",initial_length);
    printf("\nFinal length of Set is %d\n",s->LENGTH_OF_MAP);
    printf("\n");
    
    
    
    
    
    printf("\n\n************************** END **************************\n\n");
    return 0;
}
