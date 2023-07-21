#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void printAll(FILE *pFile);

void badCommand();

void getV(FILE *pFile, char *k);

void addKV(FILE *pFile, char *k);

char * checkIfExist(FILE *pFile, char *key, char *value);

void removeLine(int number);

void dCommand(FILE *pFile, char *k);

int main(int argc, char *argv[])
{
    FILE *fp = fopen("database.txt", "a");
    for (int i = 1; i < argc; ++i) {
        char *k = argv[i];
        if (k[0] == 'p') {
            addKV(fp, k);
        } else if (k[0] == 'g') {
            getV(fp, k);
        } else if (k[0] == 'd') {
            dCommand(fp, k);
        } else if (strcmp(k, "c") == 0) {
//        fclose(fp);
            remove("database.txt");
        } else if (strcmp(k, "a") == 0) {
            printAll(fp);
        } else {
            badCommand();
        }
    }
     fclose(fp);
    return 0;
}

void dCommand(FILE *fp, char *k) {
    char *s;
    char *st = strdup(k);
    char * line = NULL;
    size_t len = 0;
    fp = fopen("database.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    int comma=0;
    int exp =1;
    for (int i = 0; i < strlen(k); ++i) {
        if(k[i]==','){
            comma++;
        }
    }
    if(comma!=1){
        exp = 0;
    }
    int x = 0;
    while ((s = strsep(&st, ",")) != NULL ){
        if(x>1){
            exp = 0;
            break;
        }
        if(x == 0 ){
            if(strcmp("d",s)!=0){
                exp = 0;
                break;
            }
        }
        if(x==1) {
            for (int i = 0; i < strlen(s); ++i) {
                if( isdigit(s[i]) == 0){
                    ///// exception
                    exp = 0;
                    break;
                }
            }
        }x++;
    }
    if(exp==0){
        badCommand();
    }else {
        char *comp;
        int cnt = 0;

        while ((s = strsep(&k, ",")) != NULL) {
            if (cnt == 1) {
                comp = s;
            } else
                cnt++;
        }
        bool finished = false;
        int lineNumber = 0;
        while ((getline(&line, &len, fp)) != -1) {
            lineNumber++;
            while ((s = strsep(&line, ",")) != NULL) {

                if (strcmp(s, comp) == 0) {
                    finished = true;
                    break;
                } else {
                    break;
                }
            }
            if (finished) {
                removeLine(lineNumber);
                break;
            }
        }

    }
}
void removeLine(int number) {
    FILE *fileptr1, *fileptr2;
    char filename[40] = "database.txt";
    char ch;
    int delete_line, temp = 1;
    //open file in read mode
    fileptr1 = fopen("database.txt", "r");
//    ch = getc(fileptr1);
//    while (ch != EOF)
//    {
//        printf("%c", ch);
//        ch = getc(fileptr1);
//    }
    //rewind
//    rewind(fileptr1);
//    printf(" \n Enter line number of the line to be deleted:");
//    scanf("%d", &delete_line);
    delete_line = number;
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = getc(fileptr1);

    while (ch != EOF)
    {
        //except the line to be deleted
        if (temp != delete_line)
        {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
        ch = getc(fileptr1);
    }
//    fclose(fileptr1);
//    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
//    printf("\n The contents of file after being modified are as follows:\n");
//    fileptr1 = fopen(filename, "r");
//    ch = getc(fileptr1);
//    while (ch != EOF)
//    {
//        printf("%c", ch);
//        ch = getc(fileptr1);
//    }
//    fclose(fileptr1);
}

void addKV(FILE *fp, char *k) {
    fp = fopen("database.txt", "a");
    char *s;
    char *st= k;
    st = strdup(k);
    int x =0;
    int exp = 1;
    int comma=0;
    for (int i = 0; i < strlen(k); ++i) {
        if(k[i]==','){
            comma++;
        }
    }
    if(comma!=2){
        exp = 0;
    }
//    printf("%s\n", st);
    while ((s = strsep(&k, ",")) != NULL ){
        if(x>2){
            exp = 0;
            break;
        }
        if(x == 0 ){
            if(strcmp("p",s)!=0){
                exp = 0;
                break;
            }
        }
        if(x==1) {
            for (int i = 0; i < strlen(s); ++i) {
                if( isdigit(s[i]) == 0){
                    ///// exception
                    exp = 0;
                    break;
                }
            }
        }
        //// check is alpha ?
//            if(x == 2){
//                for (int i = 0; i < strlen(s); ++i) {
//                    if( isalpha(s[i]) == 0){
//                        ///// exception
//                        exp = 0;
//                        break;
//                    }
//                }
//            }
        x++;
    }
//    printf("%s\n", s);

    if(exp==0){
        badCommand();
    }else {
        x =0;
//        printf("%s\n", st);
        char* v = "-1";
        bool exist = false;
        while ((s = strsep(&st, ",")) != NULL) {
            if(x==1){
               if(checkIfExist(fp,s,v) != "-1"){
                   exist = true;
                   break;
               }
            }
            if (x != 0) {
//                printf("%s\n", s);
                fputs(s, fp);
                if (x == 1)
                    fputs(",", fp);
            }
            x++;
        }
        if(exist==false)
        fputs("\n", fp);
    }
}

void getV(FILE *fp, char *k) {
    char *s;
    int x =0;
    char* key;
    int exp = 1;
    int comma=0;
    for (int i = 0; i < strlen(k); ++i) {
        if(k[i]==','){
            comma++;
        }
    }
    if(comma!=1){
        exp = 0;
    }
    while ((s = strsep(&k, ",")) != NULL ){
        if(x>1){
            exp = 0;
            break;
        }
        if(x == 0 ){
            if(strcmp("g",s)!=0){
                exp = 0;
                break;
            }
        }
        if(x==1) {
            key = s;
            for (int i = 0; i < strlen(s); ++i) {
                if( isdigit(s[i]) == 0){
                    ///// exception
                    exp = 0;
                    break;
                }
            }
        }x++;
    }
    if(exp==0){
        badCommand();
    }
    else{
        char * value="-1";
       char* found =  checkIfExist(fp,key,value);
        if(found != "-1"){
            printf("%s,%s",key,found);
        }else{
            printf("%s%s",key," not found");
        }

    }
}

char * checkIfExist(FILE *fp, char *key, char *(value)) {
    char *s;
    char * line = NULL;
    size_t len = 0;
    fp = fopen("database.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    bool finished = false;
    while ((getline(&line, &len, fp)) != -1) {
        int x = 0;
        while ((s = strsep(&line, ",")) != NULL ){
            if(x==1){
                value = s;
                finished = true;
                break;
            }
            if(strcmp(s,key)==0){
                x++;
            }else{
                break;
            }
        }
        if(finished){
            break;
        }
    }
    if(finished)return value;
    else return "-1";

}
void badCommand() { printf("%s" , "bad command"); }
void printAll(FILE *fp) {
    char * line = NULL;
    size_t len = 0;
    fp = fopen("database.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
}


