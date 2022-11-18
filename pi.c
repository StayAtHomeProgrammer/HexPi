/** 
HexPi

By Sullivan Devries 
Original Algorithm by Simon Plouffe in collaboration with David H. Bailey and Peter Borwein   
**/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define P 10 // Accuracy for Bn()

double Bn(int a, int n);
double An(int a, int n);
unsigned long long pow16(int n, int a, int k);
double ABn(int a, int n);
char getPi(unsigned int num);
double shave(double s);

int main(int argc, char* argv[]){
    int uin1;
    printf("Enter an option:\n");
    printf("1.) Print digits of pi starting from the beginning\n");
    printf("2.) Print nth digit of pi\n");
    printf("\nYour selection: ");
    scanf("%d", &uin1);
    if(uin1==1){
        //printf("\n3.");
        int n = 1;
        while(true){
            printf("%X",getPi(n));
            n++;
            if((n-1)%64==0) printf("\n");
        }
    }
    else if (uin1==2){
        int uin2;
        printf("What number would you like to calculate: ");
        scanf("%d",&uin2);
        printf("\nCalculating...");
        printf("\nHex digit number %d of pi is %x\n",uin2,getPi(uin2));
    }
    else{
        return 1;
    }
    return 0;
}

double Bn(int a, int n){
    double s = 0;
    for(int k=n;k<n+10+P;k++){
        double n16 = pow(16,(n-k));
        double f = n16/((8*k)+a);
        s += f;   
    }
    return s;
}

double An(int a, int n){
    double s = 0;
    for(int k=0;k<=n-1;k++){
        double y = pow16(n-k,a,k)/(double)((8*k)+a);
        s += y;
        s = shave(s); 
    }
    return s;
}

unsigned long long pow16(int e, int a, int k){ // e is n-k
    if(e == 0) return 1;
    if(e == 1) return 16;

    unsigned long long R = pow16(e/2, a, k);
    if(e%2==0) return (R*R)%((8*k)+a);
    else return (R*R*16)%((8*k)+a);
}

double ABn(int a, int n){
    return An(a,n) + Bn(a,n);
}

char getPi(unsigned int num){
    int n = num - 1;
    double sum = 4*ABn(1,n) - 2*ABn(4,n) - ABn(5,n) - ABn(6,n);
    char f = 0xF & lrintf(floorf(16*sum)); // voodoo magic
    return f;
}

double shave(double s){ // Helper to make sure the sum doesnt grow too big
    int d = (int)lrintf(s);
    if(s >= 1 || s <= -1){
        s-=d;
    }
    return s;
}