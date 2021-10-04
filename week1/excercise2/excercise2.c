#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct sinhvien{
    int maSV;
    char hodem[20];
    char ten[10];
    float gk;
    float ck;
    char point;
    struct sinhvien *next;
}sinhvien;

typedef struct sinhvien *sv;

typedef struct objScore{
    char mon [20];
    char hocky[20];
    char tenmon[50];
    int heso;
    int soSV;
    sv svList;
}objScore;

typedef struct objScore *oj;

sv createSV(int maSv, char hodem[], char ten[], float gk, float ck, char point){
    sv temp;
    temp = (sv)malloc(sizeof(struct sinhvien));
    temp->next = NULL;
    temp->maSV = maSv;
    strcpy(temp->hodem,hodem);
    strcpy(temp->ten,ten);
    temp->gk = gk;
    temp->ck = ck;
    temp->point = point;
    return temp;
}

sv addSV(sv head, sv sV){
    if(head == NULL){
        head = sV;
    }else{
        sV->next = head;
        head = sV;
    }
    return head;
}

sv delSV(sv head, int maSv){
    if(head == NULL || head->maSV == maSv){
        if(head == NULL){
            return head;
        }else{
            head = head->next;
            return head;
        }
    }else{
        sv p = head;
        while(p->next->next != NULL && p->next->maSV != maSv){
            p = p->next;
        }
        if(p->next->maSV == maSv){
            p->next = p->next->next;
        }else{
            printf("Sinh vien khong ton tai !!\n");
        }
    }
    return head;
}

sv searchSV(sv head, int maSv){
    if(head == NULL){
        printf("danh sach sinh vien rong !!\n");
        return NULL;
    }else if(head->maSV == maSv){
        return head;
    }else{
        sv p = head;
        while(p->next->next != NULL && p->next->maSV != maSv){
            p = p->next;
        }
        if(p->next->maSV != maSv){
            printf("sinh vien khong co trong danh sach!\n");
            return NULL;
        }else{
            return p->next;
        }
    }
}

sv addPoint(sv head, int maSv, float gk, float ck){
    if(head == NULL){
        printf("danh sach sinh vien rong !!\n");
        return NULL;
    }else if(head->maSV == maSv){
        head->gk = gk;
        head->ck = ck;
        return head;
    }else{
        sv p = head;
        while(p->next->next != NULL && p->maSV != maSv){
            p = p->next;
        }
        if(p->maSV != maSv){
            printf("sinh vien khong co trong danh sach!\n");
            return NULL;
        }else{
            p->gk = gk;
            p->ck = ck;
            return head;
        }
    }
}

void printSV(sv head){
    for(sv p = head;p!=NULL;p=p->next){
        printf("%d|%s|%s\n",p->maSV,p->hodem,p->ten);
    }
}

oj getSvList(char mon[], char hocky[]){
    FILE *f;
    oj o;
    o = (oj)malloc(sizeof(struct objScore));
    char split[2] = "|" ;
    strcpy(o->mon,mon);
    strcpy(o->hocky,hocky);
    char filepath[100] = "";
    strcat(filepath,mon);
    strcat(filepath,"_");
    strcat(filepath,hocky); 
    strcat(filepath,".txt");
    f = fopen(filepath,"r");
    if(f == NULL){
        // printf("1\n");
        printf("khong co mon %s tai hoc ky %s\n",mon,hocky);
        return NULL;
    }else{
        char f1[100];
        fgets(f1,200,f);
        // printf("1\n");
        // printf("%s",f1);
        char f2[100];
        fgets(f2,200,f);
        char *token1;
        token1 = strtok(f2,split);
        token1 = strtok(NULL,split);
        strcpy(o->tenmon,token1);
        char f3[20];
        fgets(f3,200,f);
        char *token2;
        token2 = strtok(f3,split);
        token2 = strtok(NULL,split);
        //printf("%s",token2);
        int heso = atoi(token2);
        o->heso = heso;
        char f4[100];
        fgets(f4,200,f);
        char f5[100];
        fgets(f5,200,f);
        char *token3;
        token3 = strtok(f5,split);
        token3 = strtok(NULL,split);
        int sosv = atoi(token3);
        o->soSV = sosv;
        for(int i = 0;i<sosv;i++){
            char s[100];
            char *t;
            fgets(s,100,f);
            t = strtok(s,split);
            t = strtok(NULL,split);
            int maSv = atoi(t);
            t = strtok(NULL,split);
            char hodem[20];
            strcpy(hodem,t);
            t = strtok(NULL,split);
            char ten[10];
            strcpy(ten,t);
            t = strtok(NULL,split);
            float gk = atof(t);
            t = strtok(NULL,split);
            float ck = atof(t);
            t = strtok(NULL,split);
            char point = t[0];
            if(i == 0){
                o->svList = createSV(maSv,hodem,ten,gk,ck,point);
            }else{
                sv siv = createSV(maSv,hodem,ten,gk,ck,point);
                o->svList = addSV(o->svList,siv);
            }
        }
    }
    fclose(f);
    return o;
}

void printMenu(){
    printf("Learning Management System\n-------------------------------------\n");
    printf("\t1.	Add a new score board\n\t2.	Add score\n\t3.	Remove score\n");
    printf("\t4.	Search score\n\t5.	Display score board and score report\n");
    printf("Your choice (1-6, other to quit): ");
}

char Point(float gk, float ck, int heso){
    float h = heso/100.0;
    float tk = gk*h + ck*(1-h);
    if(tk < 4){
        return 'F';
    }else if(tk < 5.5){
        return 'D';
    }else if(tk < 7){
        return 'C';
    }else if(tk < 8.5){
        return 'B';
    }else{
        return 'A';
    }
}
float po(sv head,int heso){
    float h = heso/100.0;
    float p = head->gk*h + head->ck*(1-h);
    return p;
}
sv maxSV(sv head,int heso){
    if(head == NULL){
        return NULL;
    }else{
        sv temp = head;
        for(sv p = head;p!=NULL;p=p->next){
            if(po(p,heso) > po(temp,heso)){
                temp = p;
            }
        }
        return temp;
    }  
}
sv minSV(sv head, int heso){
    if(head == NULL){
        return NULL;
    }else{
        sv temp = head;
        for(sv p = head;p!=NULL;p=p->next){
            if(po(p,heso) < po(temp,heso)){
                temp = p;
            }
        }
        return temp;
    }  
}
float avg(sv head,int heso){
    float avg = 0;
    float count = 0;
    for(sv p = head;p!=NULL;p=p->next){
        avg+=po(p,heso);
        count+=1;
    }
    avg = avg/count;
    return avg;
}
int countP(sv head, char poi){
    int count = 0;
    for(sv p = head;p!=NULL;p=p->next){
        if(p->point == poi){
            count++;
        }
    }
    return count;
}
void WriteToFile(oj o){
    FILE *f;
    char filepath[100] = "";
    strcat(filepath,o->mon);
    strcat(filepath,"_");
    strcat(filepath,o->hocky); 
    strcat(filepath,".txt");
    f = fopen(filepath,"w");
    fprintf(f,"SubjectID|%s\n",o->mon);
    fprintf(f,"Subject|%s",o->tenmon);
    fprintf(f,"F|%d|%d\n",o->heso,100 - o->heso);
    fprintf(f,"Semester|%s\n",o->hocky);
    fprintf(f,"StudentCount|%d\n",o->soSV);
    for(sv p = o->svList;p!=NULL;p=p->next){
        fprintf(f,"S|%d|%s|%s|%.1f|%.1f|%c\n",p->maSV,p->hodem,p->ten,p->gk,p->ck,p->point);
    }
    fclose(f);
    FILE *fr;
    char filepathrp[100] = "";
    strcat(filepathrp,o->mon);
    strcat(filepathrp,"_");
    strcat(filepathrp,o->hocky); 
    strcat(filepathrp,"_rp.txt");
    fr = fopen(filepathrp,"w");
    sv max = maxSV(o->svList,o->heso);
    sv min = minSV(o->svList,o->heso);
    float av = avg(o->svList,o->heso);
    int a = countP(o->svList,'A');
    int b = countP(o->svList,'B');
    int c = countP(o->svList,'C');
    int d = countP(o->svList,'D');
    int F = countP(o->svList,'F');
    fprintf(fr,"The student with the highest mark is: %s %s\n",max->hodem,max->ten);
    fprintf(fr,"The student with the lowest mark is: %s %s\n",min->hodem,min->ten);
    fprintf(fr,"The average mark is: %.2f\n\n",av);
    fprintf(fr,"A histogram of the subject %s is: ",o->mon);
    fprintf(fr,"\nA:");
    if(a > 0){
        for(int x = 0;x<a;x++){
            fprintf(fr,"*");
        }  
    }
    fprintf(fr,"\nB:");
    if(b > 0){
        for(int x = 0;x<b;x++){
            fprintf(fr,"*");
        }  
    }
    fprintf(fr,"\nC:");
    if(c > 0){
        for(int x = 0;x<c;x++){
            fprintf(fr,"*");
        }  
    }
    fprintf(fr,"\nD:");
    if(d > 0){
        for(int x = 0;x<d;x++){
            fprintf(fr,"*");
        }  
    }
    fprintf(fr,"\nF:");
    if(F > 0){
        for(int x = 0;x<F;x++){
            fprintf(fr,"*");
        }  
    }
    fclose(fr);
}

void function1(){
    char mon[20];
    printf("ID mon hoc la: ");
    scanf("%s",mon);
    getchar();
    printf("Ten mon hoc la: ");
    char tenmon[50];
    scanf("%[^\n]%*c",tenmon);
    printf("He so mon hoc la(nhap he so giua ky): ");
    int hsgk,hsck;
    scanf("%d",&hsgk);
    getchar();
    hsck = 100-hsgk;
    printf("Nhap hoc ky: ");
    char hocky[20];
    scanf("%s",hocky);
    // getchar();
    printf("Nhap so luong sinh vien: ");
    int soSV;
    scanf("%d",&soSV);
    getchar();
    oj temp;
    temp = getSvList(mon,hocky);
    if(temp != NULL){
        printf("mon hoc nay da ton tai !! khong the tao moi !!\n");
    }else{
        oj o;
        strcpy(o->mon,mon);
        strcpy(o->hocky,hocky);
        strcpy(o->tenmon,tenmon);
        o->heso = hsgk;
        o->soSV = soSV;
        for(int i = 0;i<soSV;i++){
            int maSv; 
            char hodem[20]; 
            char ten[10]; 
            float gk; 
            float ck; 
            char point;
            printf("Nhap maSv thu %d: ",i);
            scanf("%d",&maSv);
            getchar();
            printf("Nhap ho va ten dem: ");
            scanf("%[^\n]%*c",hodem);
            // getchar();
            printf("Nhap ten: ");
            scanf("%[^\n]%*c",ten);
            // getchar();
            printf("Nhap diem gk: ");
            scanf("%f",&gk);
            // getchar();
            printf("Nhap diem ck: ");
            scanf("%f",&ck);
            // getchar();
            point = Point(gk,ck,hsgk);
            if(i == 0){
            o->svList = createSV(maSv,hodem,ten,gk,ck,point);
            }else{
                sv siv = createSV(maSv,hodem,ten,gk,ck,point);
                o->svList = addSV(o->svList,siv);
            }
        WriteToFile(o);
        }
    }
}

void function2(){
    char mon[20];
    printf("ID mon hoc la: ");
    scanf("%s",mon);
    getchar();
    printf("Nhap hoc ky: ");
    char hocky[20];
    scanf("%s",hocky);
    getchar();
    oj temp;
    temp = getSvList(mon,hocky);
    // printf("%s-%s\n",mon,hocky);
    if(temp == NULL){
        printf("mon hoc nay khong ton tai !! khong the them !!\n");
    }else{
        int maSv; 
        char hodem[20]; 
        char ten[10]; 
        float gk; 
        float ck; 
        char point;
        printf("Nhap maSv: ");
        scanf("%d",&maSv);
        getchar();
        printf("Nhap ho va ten dem: ");
        scanf("%[^\n]%*c",hodem);
            // getchar();
        printf("Nhap ten: ");
        scanf("%[^\n]%*c",ten);
            // getchar();
        printf("Nhap diem gk: ");
        scanf("%f",&gk);
            // getchar();
        printf("Nhap diem ck: ");
        scanf("%f",&ck);
            // getchar();
        point = Point(gk,ck,temp->heso);
        sv siv = createSV(maSv,hodem,ten,gk,ck,point);
        temp->svList = addSV(temp->svList,siv);
        temp->soSV+=1;
        WriteToFile(temp);
    }
    
}

void function3(){
    char mon[20];
    printf("ID mon hoc la: ");
    scanf("%s",mon);
    getchar();
    printf("Nhap hoc ky: ");
    char hocky[20];
    scanf("%s",hocky);
    getchar();
    oj temp;
    temp = getSvList(mon,hocky);
    if(temp == NULL){
        printf("mon hoc nay khong ton tai !! khong the xoa !!\n");
    }else{
        int maSv; 
        printf("Nhap maSv: ");
        scanf("%d",&maSv);
        getchar();
        temp->svList = delSV(temp->svList,maSv);
        temp->soSV-=1;
    }
    WriteToFile(temp);
}

void function4(){
    char mon[20];
    printf("ID mon hoc la: ");
    scanf("%s",mon);
    getchar();
    printf("Nhap hoc ky: ");
    char hocky[20];
    scanf("%s",hocky);
    getchar();
    oj temp;
    temp = getSvList(mon,hocky);
    if(temp == NULL){
        printf("mon hoc nay khong ton tai !! khong the tim !!\n");
    }else{
        int maSv; 
        printf("Nhap maSv: ");
        scanf("%d",&maSv);
        getchar();
        sv s = searchSV(temp->svList,maSv);
        if(s == NULL){
            printf("sinh vien khong ton tai \n");
        }else{
            printf("S|%d|%s\t\t\t|%s\t\t|%.1f|%.1f|%c\n",s->maSV,s->hodem,s->ten,s->gk,s->ck,s->point);
        }
    }
}

void function5(){
    char mon[20];
    printf("\nID mon hoc la: ");
    scanf("%s",mon);
    getchar();
    printf("Nhap hoc ky: ");
    char hocky[20];
    scanf("%s",hocky);
    FILE *f;
    char filepath[100]="";
    
    strcat(filepath,mon);
    strcat(filepath,"_");
    strcat(filepath,hocky); 
    strcat(filepath,".txt");
    // printf("-----------%s",filepath);
    f = fopen(filepath,"r");
    if(f == NULL){
        printf("mon nay ko co !!\n");
    }else{
        char a;
        do{
            a = fgetc(f);
            if(a == EOF){
                break;
            }
            printf("%c",a);
        }while(a!=EOF);
        printf("\n");
        fclose(f);
        FILE *fr;
        char filepathrp[100];
        strcat(filepathrp,mon);
        strcat(filepathrp,"_");
        strcat(filepathrp,hocky); 
        strcat(filepathrp,"_rp.txt");
        fr = fopen(filepathrp,"r");
        if(fr == NULL){
            printf("\n");
        }else{
            char b;
            do{
                b = fgetc(fr);
                if(b == EOF){break;}
                printf("%c",b);
            }while(b!=EOF);
            fclose(fr);
            printf("\n");
        } 
    }   
}

int main(){
    int choice;
    do{
        printMenu();
        scanf("%d",&choice);
        getchar();
        if(choice == 1){
            char c;
            do{
                function1();
                printf("Su dung tiep chuc nang ? ");
                getchar();
                scanf("%c",&c);
            }while(c == 'y' || c=='Y');
        }else if(choice == 2){
            char c;
            do{
                function2();
                printf("Su dung tiep chuc nang ? ");
                getchar();
                scanf("%c",&c);
            }while(c == 'y' || c=='Y');
        }else if(choice==3){
            char c;
            do{
                function3();
                printf("Su dung tiep chuc nang ? ");
                getchar();
                scanf("%c",&c);
            }while(c == 'y' || c=='Y');
        }else if(choice ==4){
            char c;
            do{
                function4();
                printf("Su dung tiep chuc nang ? ");
                getchar();
                scanf("%c",&c);
            }while(c == 'y' || c=='Y');
        }else if(choice ==5){
            //function5();
            char c;
            do{
                function5();
                printf("Su dung tiep chuc nang ? ");
                getchar();
                scanf("%c",&c);
            }while(c == 'y' || c=='Y');
        }else{
            printf("Bye !!\n");
        }
    }while(choice > 0 && choice < 6);
    // function5();
    return 0;
}