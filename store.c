#include "head.h"
#define MAX 256
static struct node *table[MAX];

unsigned makehash(const char *s)
{
	unsigned n=0;
	while(*s!='\0'){
		n=31*n+*s-'0';
		s++;
	}
	return n%MAX;
}


struct node *lookup(const char *s){
	struct node *p;
	for(p=table[makehash(s)];p!=0;p=p->ptr){
		if(strcmp(s,p->name)==0)
			return p;
	}
	return p;
}

static const char *strtmp(const char *s){
	const char *t;
	t=(const char*)malloc(strlen(s)+1);
	if(t==0)
		return 0;
	strcpy(t,s);
	return t;
}

struct node *install(const char *name,const char *rep){
	struct node *p;
	unsigned hashnum;
	if((p=lookup(name))==0){
		p=(struct node *)malloc(sizeof(*p));
		if(!p||!(p->name=strtmp(name)))
			return 0;
		hashnum=makehash(name);
		p->ptr=table[hashnum];
		table[hashnum]=p;
	}
	else
		free((void *)p->rep);
	if(!(p->rep=strtmp(rep)))
		return 0;
	return p;
}

int delnode(const char *s){
	struct node *p,*prevp=0;
	for(p=table[makehash(s)];p!=0;prevp=p,p=p->ptr){
		if(!strcmp(s,p->name))
			break;
	}
	if(p==0)
		return -1;
	if(prevp==0&&(p=table[makehash(s)]))
		table[makehash(s)]=p->ptr;
	else
		prevp=p->ptr;
	free((void *)p->name);
	free((void *)p->rep);
	return 1;
}
