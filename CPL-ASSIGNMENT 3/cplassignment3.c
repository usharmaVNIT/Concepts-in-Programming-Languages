//
//  main.c
//  cplass3
//
//  Created by Official on 24/03/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node{
    int data;
    char par;
    bool marked;
    struct Node *left,*right;
} Node;


void init_Node(Node *node){
    node->data=0;
    node->par='\0';
    node->left=NULL;
    node->right=NULL;
    node->marked=false;
}



void Transverse(Node *root){
    Node *prev,*current,*tmp;
    prev=NULL;
    current=root;
    while(!root->marked){
        tmp=prev;
        if(current->left && !(current->left->marked)){
            prev = current;
            current=current->left;
            prev->left=tmp;
            prev->par='l';
        }
        else if(current->right && !(current->right->marked)){
            prev=current;
            current=current->right;
            prev->right=tmp;
            prev->par='r';
        }
        else{
            current->marked=true;
            printf("%d --> ",current->data);
            if(!root->marked){
                if(prev->par=='l'){
                    prev = prev->left;
                    tmp->left=current;
                    current=tmp;
                }
                else{
                    prev=prev->right;
                    tmp->right=current;
                    current=tmp;
                }
            }
        }
    }
}

void Postorder(Node *root){
    if(root!=NULL){
        Postorder(root->left);
        Postorder(root->right);
        printf("%d --> ",root->data);

    }
}

int main(void){

    Node root,n1,n2,n3,n4,n5,n6;
    init_Node(&root);
    init_Node(&n1);
    init_Node(&n2);
    init_Node(&n3);
    init_Node(&n4);
    init_Node(&n5);
    init_Node(&n6);
    root.data=4;
    n1.data=1;
    n2.data=2;
    n3.data=3;
    n4.data=5;
    n5.data=6;
    n6.data=7;
    root.left=&n3;
    n3.left=&n2;
    n2.left=&n1;
    root.right=&n4;
    n4.right=&n5;
    n5.left=&n6;

    Postorder(&root);

    printf("End Of Postorder \n\nStart of tran \n\n");
    Transverse(&root);
    printf("\n\n");

    return 0;
}
