#include "head.h"
int getword(char *word,int len,FILE *fp){
	char *s=word;
	int ch;
	int comment(int ch,FILE *fp);

	ch=igetc(fp);

	*s=ch;
	if(ch==EOF)
		return ch;
	if(isalpha(ch)||ch=='_'){
		while(--len&&(isalnum(ch=igetc(fp))||ch=='_'))
			*++s=ch;
		ugetc(ch);
		*++s='\0';
		return word[0];
	}
	if(isdigit(ch)){
		while(--len&&isdigit(ch=igetc(fp)))
			*++s=ch;
		ugetc(ch);
		*++s='\0';
		return word[0];
	}
	if(ch=='"'){
		while(--len&&(ch=igetc(fp))!='"'&&ch!=EOF){
			*++s=ch;
			if(ch=='\\')
				*++s=igetc(fp);
		}
		if(ch=='"')
			*++s=ch;
		*++s='\0';
		return word[0];
	}
	if(ch=='/'){
		int tmp=comment(igetc(fp),fp);
		if(!tmp)
			*s='\0';
		else
			ugetc(tmp);
	}
	*++s='\0';
	return word[0];
}

int comment(int ch,FILE *fp){
	int a,b;

	if(ch=='/'){
		while((ch=igetc(fp))!='\n'&&ch!=EOF)
			;
		return 0;
	}else if(ch=='*'){
		a=igetc(fp);
		b=igetc(fp);
		while(a!='*'||b!='/'){
			a=b;
			b=igetc(fp);	
		}
		return 0;
	}
	return ch;
}

#define BSIZE 16
static int buff[BSIZE];
static int bptr=0;

int igetc(FILE *fp){
	return (bptr>0)?buff[--bptr]:fgetc(fp);
}

void ugetc(int ch){
	if(bptr>BSIZE-1)
		return;
	buff[bptr++]=ch;
}

void ugets(char *s,FILE *fp){
	int ch;
	ch=*s;
	if(ch==0)
		return;
	ugets(++s,fp);
	ugetc(ch,fp);
}
