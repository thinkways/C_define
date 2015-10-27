#include "head.h"
int main(void){
	char word[WDSIZ+1];
	struct node *p;
	FILE *fpr,*fpw;

	fpr=fopen("d://1.txt","r");
	fpw=fopen("d://2.txt","w");
	if(!fpr||!fpw)
		return -1;

	while(EOF!=getword(word,WDSIZ,fpr)){
		if(!strcmp(word,"#")){
			if(makedef(fpr)=='#')
				fputc('#',fpw);
		}
		else if(isalpha(word[0])||word[0]=='_'){
			if((p=lookup(word))!=0)
				ugets(p->rep,fpr);
			else
				fputs(word,fpw);
		}
		else
			fputs(word,fpw);
	}

	fclose(fpr);
	fclose(fpw);
	return 0;
}
