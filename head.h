#define WDSIZ 128
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"

struct node{
	const char *name;
	const char *rep;
	struct node *ptr;
};

struct node *lookup(const char *s);
struct node *install(const char *name,const char *rep);

int getword(char *word,int len,FILE *fp);
void ugets(char *s,FILE *fp);
int igetc(FILE *fp);
void ugetc(int ch);

int delnode(const char *s);
int makedef(FILE *fp);
