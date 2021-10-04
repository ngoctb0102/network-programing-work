#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct hCode{
    char code[10];
    int color;
    //0 is white, 1 is black
}hCode;

hCode getCode(){
    hCode code;
    char Code[10];
    do{
        printf("Enter HAZCHEM code: ");
        scanf("%s",Code); 
    }while(checkcode(Code) != 1);
    strcpy(code.code,Code);
    char sC = Code[1];
    if(sC == 'S' || sC == 'T' || sC =='Y' || sC == 'Z'){
        printf("Is the %c reserve coloured? ",sC);
        char check[5];
        scanf("%s",check);
        if(strcasecmp(check,"yes") == 0){
            code.color = 1;
        }else{
            code.color = 0;
        }
    }else{
        code.color = 1;
    }
    return code;
}

int checkcode(char code[]){
    if(strlen(code) > 3){
        printf("invalid length !!\n");
        return 0;
    }
    char fC = code[0];
    char sC = code[1];
    // char tC;
    // if(strlen(code) == 2){
    //     tC = 'a';
    // }
    char tC = code[2];
    // printf("%c%c%c",fC,sC,tC);
    if(fC == '1' || fC == '2' || fC == '3' || fC == '4'){
        if(sC == 'P' || sC == 'R' || sC == 'S' || sC == 'T' || sC == 'W' || sC == 'X' || sC == 'Y' || sC == 'Z'){
            if(tC == 'E' || tC == '\0'){
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else return 0;
}
void print1stCode(char c){
    if(c == '1'){
        printf("Material : jets\n");
    }else if(c == '2'){
        printf("Material : fog\n");
    }else if(c == '3'){
        printf("Material : foam\n");
    }else{
        printf("Material : dry agent\n");
    }
}
void print2ndCode(char c,int co){
    switch(c){
        case 'P':
            printf("Reactivity: can be violently reactive\n");
            printf("Protection: full protective clothing must be worn\n");
            printf("Containment: the dangerous goods may be washed down to a drain with a large quantity of water\n");
            break;
        case 'R':
            printf("Protection: full protective clothing must be worn\n");
            printf("Containment: the dangerous goods may be washed down to a drain with a large quantity of water\n");
            break;
        case 'S':
            printf("Reactivity: can be violently reactive\n");
            if(co == 0){
                printf("Protection : breathing apparatus\n");
            }else{
                printf("Protection : breathing apparatus, protective gloves for fire only\n");
            }
            printf("Containment: the dangerous goods may be washed down to a drain with a large quantity of water\n");
            break;
        case 'T':
            if(co == 0){
                printf("Protection : breathing apparatus\n");
            }else{
                printf("Protection : breathing apparatus, protective gloves for fire only\n");
            }
            printf("Containment: the dangerous goods may be washed down to a drain with a large quantity of water\n");
            break;
        case 'W':
            printf("Reactivity: can be violently reactive\n");
            printf("Protection: full protective clothing must be worn\n");
            printf("Containment: a need to avoid spillages from entering drains or water courses.\n");
            break;
        case 'X':
            printf("Protection: full protective clothing must be worn\n");
            printf("Containment: a need to avoid spillages from entering drains or water courses.\n");
            break;
        case 'Y':
            printf("Reactivity: can be violently reactive\n");
            if(co == 0){
                printf("Protection : breathing apparatus\n");
            }else{
                printf("Protection : breathing apparatus, protective gloves for fire only\n");
            }
            printf("Containment: a need to avoid spillages from entering drains or water courses.\n");
            break;
        case 'Z':
            printf("Reactivity: can be violently reactive\n");
            if(co == 0){
                printf("Protection : breathing apparatus\n");
            }else{
                printf("Protection : breathing apparatus, protective gloves for fire only\n");
            }
            printf("Containment: a need to avoid spillages from entering drains or water courses.\n");
            break;
        default:
            break;
    };
}
void print3rdCode(char c){
    if(c == 'E'){
        printf("Evacuation:  consider evacuation\n");
    }
}

void printInfor(hCode code){
    printf("***Emergency action advice***\n");
    print1stCode(code.code[0]);
    print2ndCode(code.code[1],code.color);
    print3rdCode(code.code[2]);
    printf("*****************************\n");
}
int main(){
    hCode code = getCode();
    printInfor(code);
    return 0;
}