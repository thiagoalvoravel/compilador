#include "analex.h"
#include "anasin.h"

int main(){

     //FILE *fp;
     int posPR;
     char ch;
     TOKEN token;
     fp = abrirArquivo("codigo_teste_1.txt");
     /*while (!feof(fp)){
        token = analexico();
     }*/
     //analexico();
     sintatico();
     fclose(fp);
     system("PAUSE");
     return 0;
}
