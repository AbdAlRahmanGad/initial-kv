#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void printAll(FILE *pFile);

void badCommand();

void getV(FILE *pFile, char *k);

/* cat:  concatenate files, version 1 */
int main(int argc, char *argv[])
{
    FILE *fp = fopen("database.txt", "a");


//    FILE *fp;
//    void filecopy(FILE *, FILE *);
//    FILE * x = fopen("f.txt","a");
//    int fputc(int c, FILE *stream);
//    int fputs(const char * restrict s, FILE * restrict stream);
//    char*s = argv[1];
//    s."fff";
//    char *s;
    char *k = argv[1];
//    bool validCommad =
    if(k[0] == 'p'){
        char *s;
        int x = 0;
        while ((s = strsep(&k, ",")) != NULL ){
            if(x!=0) {
                printf("%s\n", s);
                fputs(s,fp);
                if(x==1)
                    fputs(",",fp);
            }x++;
        }
        fputs( "\n",fp);

    }else if(k[0] == 'g'){
        getV(fp,k);
    }else if(k[0] == 'd'){
        char *s;

        char * line = NULL;
        size_t len = 0;
//        printf("%s","comp_____");

        fp = fopen("database.txt", "r");
        if (fp == NULL){
            exit(EXIT_FAILURE);
        }
        char* comp;
        int cnt = 0;
            while ((s = strsep(&k, ",")) != NULL ){
                if(cnt == 1) {
                    comp = s;
//                    printf("%s", comp);
//                    break;

                }else cnt++;
            }
            bool finished = false;
        while ((getline(&line, &len, fp)) != -1) {
//            printf("%s", line);
//            for (int i = 0; i < strlen(line); ++i) {
                int x = 0;
                while ((s = strsep(&line, ",")) != NULL ){
//                    if(x==1){
////                        printf("%s",s);
//                        finished = true;
//                        break;
//                    }
                   if(strcmp(s,comp)==0){
//                       printf("%s,",s);
                       finished = true;
                       break;
                   }else{
                       break;
                   }
                }
            if(finished){
                remove(line);
                break;
            }
//            }
        }
    }else if(strcmp(k , "c") == 0){
//        fclose(fp);
        remove("database.txt");
    }
    else if(strcmp(k , "a") == 0){
        printAll(fp);
    }else{
        badCommand();
    }
//    fwrite();
//    fputs( argv[1],fp);
//    fputs( "\n",fp);
//    fgets(0,x);
//    fgets        Reads a line from a stream
//    fputs        Writes a string to a stream
//        filecopy(stdin, stdout);
     fclose(fp);
    return 0;
}

void getV(FILE *fp, char *k) {
    char *s;
    int x =0;
    char* key;
    int exp = 1;
    int comma=0;
    for (int i = 0; i < strlen(k); ++i) {
//        printf("%c%s",k[i],"_");

        if(k[i]==','){
            comma++;
        }
    }
    if(comma!=1){
        exp = 0;
//            break;
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
    }else{
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
                    printf("%s",s);
                    finished = true;
                    break;
                }
                if(strcmp(s,key)==0){
                    printf("%s,",s);

                    x++;
                }else{
                    break;
                }
            }
            if(finished){
                break;
            }
        }
        if(!finished){
            printf("%s%s",key," not found");
        }

    }
}

void badCommand() { printf("%s" , "bad command"); }

void printAll(FILE *fp) {
    char * line = NULL;
    size_t len = 0;
    fp = fopen("database.txt", "r");
    if (fp == NULL){
//            printf("")
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
}
//void getV(FILE *fp , char*k)
//{
//
//}
/* filecopy:  copy file ifp to file ofp */
//void filecopy(FILE *ifp, FILE *ofp)
//{  int c;
//
//    while ((c = getc(ifp)) != EOF)
//        putc(c, ofp);
//}

