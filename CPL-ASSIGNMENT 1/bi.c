#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    char bi[310];
}BigInt;

void Init(char *c,int len){
    for(int i=0;i<len;i++){
        c[i]='0';
    }
    c[len]='\0';
}
//**************************************************************************************    ADDITION    *****************************************************************************************
void add(char *a,char *b,BigInt *c){

    int la=strlen(a);
    int lb = strlen(b);
    int carry=0;
    int sum=0;
    int ctr=309;
    while((la)&&(lb)){
        sum = (a[la-1] - '0') + (b[lb-1] - '0') + carry;
        c->bi[ctr-1]=sum%10 + '0';
        carry = sum/10;
        la--;lb--;ctr--;
    }
    for(;la;la--){
        sum = (a[la-1]-'0') + carry;
        c->bi[ctr-1]=sum%10 +'0';
        ctr--;
        carry=sum/10;
    }
    for(;lb;lb--){
        sum= (b[lb-1] - '0') + carry;
        c->bi[ctr-1] = sum%10 + '0';
        ctr--;
        carry = sum/10;
    }
}
//**************************************************************************************    SUBTRACTION    *****************************************************************************************


void sub(char* a,char* b,BigInt *c){
    Init(c->bi,309);
    int ctr = 309;
    int la=strlen(a);
    int lb = strlen(b);
    int borrow=0;
    int diff=0;
    if(la>lb){
    while(lb){
        diff = (a[la-1] - b[lb-1]) -borrow;
        borrow =0;
        if(diff<0){
            diff = 10+diff;
            borrow=1;
        }
        c->bi[ctr-1]=diff +'0';
        la--;lb--;ctr--;
    }
    for(;la;la--){
        diff = (a[la-1]-'0') - borrow;
        borrow=0;
        if(diff<0){
            diff = 10+diff;
            borrow=1;
        }
        c->bi[ctr-1] = diff + '0';
        ctr--;
    }
    }//if la>lb
    else if(lb>la){
        while(la){
            diff = b[lb-1] - a[la-1] - borrow;
            borrow=0;
            if(diff<0){
                diff = 10+diff;
                borrow =1;
            }
            c->bi[ctr-1] = diff + '0';
            la--;
            lb--;
            ctr--;
        }
        for(;lb;lb--){
           diff = (b[lb-1]-'0')-borrow;
            borrow=0;
            if(diff<0){
                diff=10-diff;
                borrow=1;
            }
            c->bi[ctr-1] = diff + '0';
            ctr--;
        }
        c->bi[ctr-1]='-';
    }//else if lb>la
    else{
        int i=0;
        while(a[i]==b[i] && i<(la)){
            i++;
        }
        if(a[i]>=b[i]){
                 while(lb){
                diff = (a[la-1] - b[lb-1]) -borrow;
                borrow =0;
                if(diff<0){
                    diff = 10+diff;
                    borrow=1;
                }
                c->bi[ctr-1]=diff +'0';
                la--;lb--;ctr--;
            }
            for(;la;la--){
                diff = (a[la-1]-'0') - borrow;
                borrow=0;
                if(diff<0){
                    diff = 10+diff;
                    borrow=1;
                }
                c->bi[ctr-1] = diff + '0';
                ctr--;
            }
        }//a[i]>b[i]
        else{
                 while(la){
                diff = b[lb-1] - a[la-1] - borrow;
                borrow=0;
                if(diff<0){
                    diff = 10+diff;
                    borrow =1;
                }
                c->bi[ctr-1] = diff + '0';
                la--;
                lb--;
                ctr--;
            }
            for(;lb;lb--){
               diff = (b[lb-1]-'0')-borrow;
                borrow=0;
                if(diff<0){
                    diff=10-diff;
                    borrow=1;
                }
                c->bi[ctr-1] = diff + '0';
                ctr--;
            }
            c->bi[ctr-1]='-';
        }
    }//else la = lb
}

//**************************************************************************************    Multiplication    *******************************************************************************************

void mul(char* a,char* b,BigInt *c){
    Init(c->bi,309);
    int ctr = 309;
    int la=strlen(a);
    int lb = strlen(b);
    BigInt d;
    Init(d.bi,309);
    int carry=0;
    const int mea=lb;
    while(lb){
        int lla=la;
        int zz=mea-lb;
        char temp[la+zz+2];
        Init(temp,la+zz+1);
        int tempctr=la;
        while(lla){
            int a1=a[lla-1]-'0';
            int b1=b[lb-1]-'0';
            int mu= a1*b1;
            temp[tempctr]=mu%10 + carry +'0';
            tempctr--;
            carry = mu/10;
            lla--;
        }
        temp[tempctr]=carry+'0';
        int i;
        for(i=la+1;i<=la+zz;i++){
            temp[i]='0';
        }
        temp[i]='\0';
        add(d.bi,temp,&d);
        lb--;
    }
    *c=d;
}
//**************************************************************************************   MAIN   *******************************************************************************************

int main(void){
    char a[310],b[310];
    BigInt c;
    printf("Enter A and B \n");
    scanf("%s%s",a,b);
    printf("Sum : ");
    Init(c.bi,309);
    add(a,b,&c);
    int i=0;
    while(c.bi[i]=='0'){
        i++;
    }
    while(c.bi[i]!='\0'){
        printf("%c",c.bi[i]);
        i++;
    }
    printf("\nDifference : ");
    Init(c.bi,309);
    sub(a,b,&c);
    i=0;
    while(c.bi[i]=='0'){
        i++;
    }
    if(c.bi[i]=='\0'){
        printf("0");
    }
    while(c.bi[i]!='\0'){
        printf("%c",c.bi[i]);
        i++;
    }
    printf("\n");
    Init(c.bi,309);
    mul(a,b,&c);
    printf("Multiplication is : ");
    i=0;
    while(c.bi[i]=='0'){
        i++;
    }
    if(c.bi[i]=='\0'){
        printf("0");
    }
    while(c.bi[i]!='\0'){
        printf("%c",c.bi[i]);
        i++;
    }
    printf("\n");
    return 0;
}
