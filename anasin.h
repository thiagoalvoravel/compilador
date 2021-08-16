#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED
#define EXCLUIR -10
#define PRIMEIRO -11
#define NADA -12
#define FUNC -13
#define PARAM -14
#define GLOBAL -15
#define LOCAL -16

typedef enum{IF,ELSE,WHILE,VOID,FOR,RETURN,CHAR,INT,EXTERN,FWD,MAIN,FLOAT,BOOL,FALSE,TRUE}PalavraReservada;

void funcOrDecl();
void decl();
void sintatico();
void prog();
void var(int classe);
void decl_var(int cod,int classe);
int tipo();
void tipos_param(int checaFWD);
void func();
int cmd();
int atrib();
void expr();
void error_sintatico();
void exprSimpRepete();
void expr_simp();
void termo();
void termoRepete();
void fator();
int op_rel();
void proxToken();
void fatorRepete();
void match_SN(int cod);
int match_SN_cond(int cod);
void match_PR(int cod);
int match_PR_cond (int cod);
void match_ID(int cod,int zombie,int classe);
int match_CTI();
int match_CTR();
int match_CTC();
int match_CTL();
int match_ID_cond(int cod);

#endif // SINTATICO_H_INCLUDED
