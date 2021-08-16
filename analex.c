#include "analex.h"

char listaSinais[100][100] ={ {"||"},{"&"},{"&&"},{"!"},{"*"},{"/"},{"+"},{"-"},{"<"},{"<="},{">"},{">="},{"=="},{"="},{"!="},{","},{";"},{"("},{")"},{"{"},{"}"},{"["},{"]"}};
char pReservada[100][10] ={ {},
                            {"if"},
                            {"else"},
                            {"while"},
                            {"void"},
                            {"for"},
                            {"return"},
                            {"char"},
                            {"int"},
                            {"extern"},
                            {"main"},
                            {"float"},
                            {"true"},
                            {"false"},
                            {"bool"}};

FILE * abrirArquivo(char nomeArquivo[]){
    FILE *fp;
    if ( (fp = fopen(nomeArquivo,"r")) != NULL ){
        return fp;
    }
    else{
       printf("Erro ao abrir o arquivo");
       exit(1);
    }
}

TOKEN montaToken(int cat,char token[],char ch,int pos){
     int convert_int;
     float convert_real;
     TOKEN estruturaToken;
     switch (cat){
            case ID:{
                printf ("<ID,%s>\n",token);
                estruturaToken.cat = ID;
                strcpy(estruturaToken.tipo.lexema,token);
                return estruturaToken;
            }
            case PR:{
                printf ("<PR,%s>\n",token);
                estruturaToken.cat = PR;
                estruturaToken.tipo.codigo = pos;
                return estruturaToken;
            }
            case SN:{
                printf ("<SN,%s>\n",token);
                estruturaToken.cat = SN;
                estruturaToken.tipo.codigo = pos;
                return estruturaToken;
            }
            case CTI:{
                convert_int = atoi(token);
                printf ("<CTI,%d>\n",convert_int);
                estruturaToken.cat = CTI;
                estruturaToken.tipo.valor_int = convert_int;
                return estruturaToken;
            }
            case CTR:{
                convert_real = atof(token);
                printf ("<CTR,%.1f>\n",convert_real);
                estruturaToken.cat = CTR;
                estruturaToken.tipo.valor_real = convert_real;
                return estruturaToken;
            }
            case CTC:{
                convert_int = ch;
                if((strcmp(token, "\\n") == 0) || (strcmp(token, "\\0") == 0)){
                    printf ("<CTC,%s>\n",token);
                }else{
                    printf ("<CTC,%c>\n",ch);
                }
                estruturaToken.cat = CTC;
                estruturaToken.tipo.codigo = convert_int;
                return estruturaToken;
            }
            case CTL:{
                printf ("<CTL,%s>\n",token);
                estruturaToken.cat = CTL;
                estruturaToken.tipo.codigo = pos;
                return estruturaToken;
            }
     }
}

int searchPR(char token[]){
     int existePR;
     int i;
     existePR = 0;
     i = 1;

     while ( (strcmp(pReservada[i],"") > 0) ){
         if ( (strcmp(token,pReservada[i]) == 0) ){
            existePR = 1;
            break;
         }
         i++;
     }
     if (existePR == 1){
        return i;
     }
     else{
        i = 0;
        return i;
     }
}

int adicionaLiteral(char literal[]){
    int i = 0;
    int cont = 0;

    i=0;
    while (1){
        if ( (strcmp(constLiteral[i],"") == 0) ){
            strcpy (constLiteral[i],literal);
            return i;
        }
        else{
            i++;
        }
    }
}

TOKEN analexico(){
        int estado = 0;
        char ch;
        char tokenAux;
        char token[TAM];
        char tokenNewLine[3];
        int cont = 0;
        int pos = 0;
        int linha = 1;
        TOKEN estruturaToken;

        while (1){
            switch (estado){
                    case 0:{
                        memset(token,0,TAM);
                        if (feof(fp)){
                            exit(1);
                        }
                        cont = 0;
                        /*if (feof(fp)){
                            exit(1);
                        }*/
                        ch = getc(fp);
                        if ( (ch == ' ') ){
                            estado = 0;
                        }
                        if ((ch == '\n')){
                            estado = 0;
                            linha++;
                        }
                        if ( isdigit(ch) ){
                            estado = 1;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( isalpha(ch) ){
                            estado = 6;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '\''){
                            estado = 8;
                        }
                        if ( ch == '\"'){
                            estado = 16;//14
                        }
                        if ( ch == '('){
                            estado = 18;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == ','){
                            estado = 19;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == ';'){
                            estado = 20;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '*'){
                            estado = 21;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '+'){
                            estado = 22;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '-'){
                            estado = 23;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '!'){
                            estado = 24;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '/'){
                            estado = 27;//25
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '<'){
                            estado = 31;//29
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '>'){
                            estado = 34;//32
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '='){
                            estado = 37;//35
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '&'){
                            estado = 40;//38
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '|'){
                            estado = 43;//41
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == ')'){
                            estado = 45;//50
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '{'){
                            estado = 46;//51
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '}'){
                            estado = 47;//52
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '['){
                            estado = 48;//53
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == ']'){
                            estado = 49;//54
                            token[cont] = ch;
                            cont++;
                        }

                        break;
                    }
                    case 1:{
                        ch = getc(fp);
                        if ( isdigit(ch) ){
                            estado = 1;
                            token[cont] = ch;
                            cont++;
                        }
                        if ( ch == '.'){
                            estado = 2;
                            token[cont] = ch;
                            cont++;
                        }
                        else if ( (ch != '.') && (!isdigit(ch)) ){
                            estado = 3;
                        }
                        break;
                    }
                    case 2:{
                        ch = getc(fp);
                        if ( isdigit(ch) ){
                            estado = 4;
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 3:{
                        estruturaToken = montaToken(CTI,token,'\0',0);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 4:{
                        ch = getc(fp);
                        if ( isdigit(ch) ){
                            estado = 4;
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 5;
                        }
                        break;
                    }
                    case 5:{
                        estruturaToken = montaToken(CTR,token,'\0',0);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 6:{
                        ch = getc(fp);
                        if ( isdigit(ch) || isalpha(ch) || ch == '_'){
                            estado = 6;
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 7;
                        }
                        break;
                    }
                    case 7:{
                        pos = searchPR(token);
                        if (pos != 0){
                            estruturaToken = montaToken(PR,pReservada[pos],'\0',pos);
                            estado = 0;
                        }
                        else{
                            estruturaToken = montaToken(ID,token,'\0',0);
                            estado = 0;
                        }
                        if(!isdigit(ch) || !isalpha(ch) || ch != '_'){
                            ungetc(ch,fp);
                        }
                        return estruturaToken;
                    }
                    case 8:{
                        ch = getc(fp);
                        if ( ch == '\\' ){
                            estado = 10;
                        }
                        else {
                            estado = 9;
                            tokenAux = ch;
                        }
                        break;
                    }
                    case 9:{
                        ch = getc(fp);
                        if ( (ch == '\'')  && (tokenAux != '\'') ){
                            estado = 11;
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 10:{
                        ch = getc(fp);
                        if ( ch == '\'' ){
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        else if( ch == 'n'){
                            estado = 12;
                        }
                        else if( ch == '0'){
                            estado = 13;
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 12:{
                        ch = getc(fp);
                        if ( ch == '\'' ){
                            estado = 14;//56
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 13:{
                        ch = getc(fp);
                        if ( ch == '\'' ){
                            estado = 15;//57
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 14:{//56
                        strcpy(tokenNewLine, "\\n");
                        estruturaToken = montaToken(CTC,tokenNewLine,'\n',0);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 15:{//57
                        strcpy(tokenNewLine, "\\0");
                        estruturaToken = montaToken(CTC,tokenNewLine,'\0',0);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 11:{
                        estruturaToken = montaToken(CTC,"",tokenAux,0);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 16:{//14
                        ch = getc(fp);
                        if ( ch == '\"' ){
                            if(strcmp(token, "\\0") == 0 || strcmp(token, "\\n") == 0){
                                printf("Erro na linha %d\n",linha);
                                exit(1);
                            }else {
                                ch = getc(fp);
                                if ( ch == '\"'){
                                    printf("Erro na linha %d\n",linha);
                                    exit(1);
                                }else if(strcmp(token, "") == 0){
                                    strcpy(token, "");
                                    estado = 17;//15
                                }else{
                                    estado = 17;//15
                                }
                                ungetc(ch,fp);
                            }
                        }
                        else {
                            estado = 16;//14
                            token[cont] = ch;
                            cont++;
                        }
                        break;
                    }
                    case 17:{//15
                        pos = adicionaLiteral(token);
                        estruturaToken = montaToken(CTL,token,'\0',pos);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 18:{
                        estruturaToken = montaToken(SN, listaSinais[ABRIRPARENTESE],'\0',ABRIRPARENTESE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 19:{
                        estruturaToken = montaToken(SN, listaSinais[VIRGULA],'\0',VIRGULA);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 20:{
                        estruturaToken = montaToken(SN, listaSinais[PONTO_VIRGULA],'\0',PONTO_VIRGULA);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 21:{
                        estruturaToken = montaToken(SN, listaSinais[MULTIPLICACAO],'\0',MULTIPLICACAO);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 22:{
                        estruturaToken = montaToken(SN, listaSinais[SOMA],'\0',SOMA);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 23:{
                        estruturaToken = montaToken(SN, listaSinais[SUBTRACAO],'\0',SUBTRACAO);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 24:{
                        ch = getc(fp);
                        if ( ch == '=' ){
                            estado = 25;//58
                        }
                        else{
                            estado = 26;//59
                        }
                        break;
                    }
                    case 25:{//58
                        estruturaToken = montaToken(SN, listaSinais[DIFERENTE],'\0',DIFERENTE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 26:{//59
                        estruturaToken = montaToken(SN, listaSinais[NOT],'\0',NOT);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 27:{//25
                        ch = getc(fp);
                        if ( ch == '*' ){
                            estado = 28;//26
                        }
                        else{
                            estado = 29;//27
                        }
                        break;
                    }
                    case 28:{//26
                        ch = getc(fp);
                        if ( ch == '*' ){
                            estado = 30;//55
                        }
                        else{
                            estado = 28;//26
                        }
                        break;
                    }
                    case 30:{//55
                        ch = getc(fp);
                        if( ch == '/' ){
                            estado = 0;
                        }else if( ch == '*' ){
                            estado = 30;//55
                        }else{
                            estado = 28;//26
                        }
                        break;
                    }
                    case 29:{//27
                        estruturaToken = montaToken(SN, listaSinais[DIVISAO],'\0',DIVISAO);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 31:{//29
                        ch = getc(fp);
                        if ( ch == '=' ){
                            estado = 32;//31
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 33;//30
                        }
                        break;
                    }
                    case 33:{//30
                        estruturaToken = montaToken(SN, listaSinais[MENOR],'\0',MENOR);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 32:{//31
                        estruturaToken = montaToken(SN, listaSinais[MENORIGUAL],'\0',MENORIGUAL);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 34:{//32
                        ch = getc(fp);
                        if ( ch == '=' ){
                            estado = 35;//34
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 36;//33
                        }
                        break;
                    }
                    case 36:{//33
                        estruturaToken = montaToken(SN, listaSinais[MAIOR],'\0',MAIOR);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 35:{//34
                        estruturaToken = montaToken(SN, listaSinais[MAIORIGUAL],'\0',MAIORIGUAL);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 37:{//35
                         ch = getc(fp);
                         if ( ch == '=' ){
                            estado = 38;//37
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 39;//36
                        }
                        break;
                    }
                    case 39:{//36
                        estruturaToken = montaToken(SN,listaSinais[ATRIBUICAO] ,'\0',ATRIBUICAO);
                        estado = 0;
                        ungetc(ch,fp);
                        return estruturaToken;
                    }
                    case 38:{//37
                        estruturaToken = montaToken(SN, listaSinais[IGUAL],'\0',IGUAL);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 40:{//38
                        ch = getc(fp);
                         if ( ch == '&' ){
                            estado = 41;//39
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            estado = 42;//40
                        }
                        break;
                    }
                    case 41:{//39
                        estruturaToken = montaToken(SN, listaSinais[AND],'\0',AND);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 42:{//40
                        estruturaToken = montaToken(SN, listaSinais[ENDERECO],'\0',ENDERECO);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 43:{//41
                        ch = getc(fp);
                         if ( ch == '|' ){
                            estado = 44;//42
                            token[cont] = ch;
                            cont++;
                        }
                        else{
                            printf("Erro na linha %d\n",linha);
                            exit(1);
                        }
                        break;
                    }
                    case 44:{//42
                        estruturaToken = montaToken(SN, listaSinais[OR],'\0',OR);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 45:{//50
                        estruturaToken = montaToken(SN, listaSinais[FECHARPARENTESE],'\0',FECHARPARENTESE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 46:{//51
                        estruturaToken = montaToken(SN, listaSinais[ABRIRCHAVE],'\0',ABRIRCHAVE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 47:{//52
                        estruturaToken = montaToken(SN, listaSinais[FECHARCHAVE],'\0',FECHARCHAVE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 48:{//53
                        estruturaToken = montaToken(SN, listaSinais[ABRIRCOCHETE],'\0',ABRIRCOCHETE);
                        estado = 0;
                        return estruturaToken;
                    }
                    case 49:{//54
                        estruturaToken = montaToken(SN, listaSinais[FECHARCOCHETE],'\0',FECHARCOCHETE);
                        estado = 0;
                        return estruturaToken;
                    }
            }
        }
}
