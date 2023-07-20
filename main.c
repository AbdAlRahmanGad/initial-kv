#include <stdio.h>
#include <string.h>

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
    char *s;
    char *k = argv[1];
    if(k[0] == 'p'){
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

    }else if(k[0] == 'd'){

    }else if(strcmp(k , "c") == 0){
//        fclose(fp);
        remove("database.txt");
    }else if(strcmp(k , "a") == 0){

    }else{
        printf("%s" , "bad command");
    }


//    fwrite();
//    fputs( argv[1],fp);
//    fputs( "\n",fp);
//    fgets(0,x);
//    fgets        Reads a line from a stream
//    fputs        Writes a string to a stream
//    if (argc == 1)  /* no args; copy standard input */
//        filecopy(stdin, stdout);
//    fgetc       Reads a character from a stream
//        printf("%s", argv[1]);
     fclose(fp);
    return 0;
}

/* filecopy:  copy file ifp to file ofp */
//void filecopy(FILE *ifp, FILE *ofp)
//{  int c;
//
//    while ((c = getc(ifp)) != EOF)
//        putc(c, ofp);
//}

