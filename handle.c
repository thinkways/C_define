#include "head.h"

static void skip_space(FILE *fp){
	int ch;
	while((ch=igetc(fp))==' '||ch=='\t')
		;
	ugetc(ch);
}
int makedef(FILE *fp){
	int ch,i=0;
	char name[WDSIZ];
	char rep[WDSIZ];

	skip_space(fp);
	getword(name,WDSIZ,fp);
	if(!strcmp(name,"define")){
		skip_space(fp);
		getword(name,WDSIZ,fp);
		if(isalpha(name[0])||name[0]=='_'){
			skip_space(fp);
			while((ch=igetc(fp))!='\n'&&ch!=' '&&ch!='\t')
				rep[i++]=ch;
			rep[i]='\0';
			if(ch==' '||ch=='\t'){
				skip_space(fp);
				ch=igetc(fp);
				if(ch!='\n'){
					fputs("rep wrong!",stderr);
					return -1;
				}
			}
			install(name,rep);
		}else{
			fputs("ID Error!\n",stderr);
			return -1;
		}
	}else if(!strcmp(name,"undef")){
		skip_space(fp);
		getword(name,WDSIZ,fp);
		if(isalpha(name[0])||name[0]=='_')
			delnode(name);
	}else{
		ugets(name,fp);
		return '#';
	}
	return 0;
}
