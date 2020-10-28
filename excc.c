#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 255

#define DECL_VAR '#'
#define ACCS_ELM '/'
#define TEST_CTN '['
#define OPUT_CHR '>'
#define LINE_NEW 'N'
#define EQUALITY '='
#define NOTEQUAL '!'
#define PUSH_ALL '^'
#define PULL_ALL '_'
#define SUBT_NUM '-'
#define _ADD_NUM '+'
#define QUEUE_IT '*'
#define LOOP_FOR '{'
#define INPT_CHR '<'
#define CHTO_NUM '$'

struct Container {
	char Name;
	int  i_val;
	char c_val;
};

typedef char *String;
int state = 0;
int loopst= 0;
struct Container variables[100];
int used = 0;
int queue[4];
int imm;
int times;
char tempst = 'J';
int Qp = 0;

int pow_(int base,int exp){
	long long result = 1;
	while(exp != 0){
		result *= base;
		--exp;
	}
	return(result);
}

int cvrt(char cvrtd){
	int byt;
	byt = (int)cvrtd - 48 * (cvrtd <= '9' && cvrtd >= '0');
	return(byt);
}

void rmall(char what,String where){
	char *src, *dest; // source and destination
	for(src = dest = where; *src != '\0'; src++){ // src and dest = passed string, while not '\0' proceed
		*dest = *src; 		   	     // destination = source
		if(*dest != what) dest++; // if dest == character to be deleted then do not increase dest's memory address,
					 // ... this will result in the character being overwritten by the next one.
	}
	*dest = '\0';
}

void replace(char old,char new,String where){
	char *src, *dest;
	for(src = dest = where; *src != '\0'; src++){
		*dest = *src;
		if(*dest == old){
			*dest = new; // replace the old to the new one
		}
		dest++;
	}
	*dest = '\0';
}

char *substr(int start,int end,char *where){
	char *copy = (String)malloc(LINE);
	strncpy(copy,where,LINE);
	int counter = 0;
	char *src,*dest;
	for(src = dest = copy; *src != '\0'; src++){
		*dest = *src;
		if(counter >= start && counter <= end) dest++;
		counter++;
	}
	*dest = '\0';
	return(copy);
}

char subchar(int start,int end,char *where){
	char *copy = (String)malloc(LINE);
	strncpy(copy,where,LINE);
	int counter = 0;
	char *src,*dest;
	for(src = dest = copy; *src != '\0'; src++){
		*dest = *src;
		if(counter >= start && counter <= end) dest++;
		counter++;
	}
	*dest = '\0';
	return(copy[0]);
}

int number(char *what){
	char *src;
	int  len = 0;
	char *copy = (String)malloc(LINE);
	strncpy(copy,what,LINE);
	for(src = copy; *src != '\0'; src++){
		if(*src < '0' || *src > '9'){
			printf("\nDNDT ERROR: Do Not Do That! there are characters in the integer value\nYOUR VARIABLE: $x x xxxx\nVALID EXAMPLE: $x x 0000\n\n");
			exit(1);
		}
		len++;
	}
	int num[len];
	int counter = 0;
	int buf = 0;
	for(src = copy; *src != '\0'; src++){
		num[counter] = cvrt(*src);
		counter++;
	}
	for(int c = 0;c < counter;c++){
		if(counter - (c + 1) != 0){
			buf += num[c] * (pow_(10,counter - (c + 1)));
		}
		else{
			buf += num[c];
		}
	}
	return(buf);
}

int lookfor(char what, char *where){
	char *src, *dest;
	int counter = 0;
	for(src = dest = where; *src != '\0'; src++){
		*dest = *src;
		if(*dest == what){
			return(counter);
		}
		counter++;
		dest++;
	}
	return(-1);
}

int lookfor_var(char var){
	for(int o = 0;o < 100;o++){
		if(variables[o].Name == var){
			return(o);
		}
	}
	return(-1);
}

int eval(char operation, String context){
	struct Container ttmp;
	int operation_index;
	int var_index;
	int i_temp;
	char temp;
	switch(operation){
		case DECL_VAR:
			operation_index = lookfor(DECL_VAR,context);

			ttmp.Name = subchar(operation_index + 1,operation_index + 2,context);
			 ttmp.c_val = subchar(operation_index + 2,operation_index + 3,context); 
			  ttmp.i_val  = number(substr(operation_index + 3,LINE,context));

			variables[used] = ttmp;
			++used;
		break;
		case OPUT_CHR:
			operation_index = lookfor(OPUT_CHR,context);
			if(lookfor(DECL_VAR,context) != -1){
				rmall(DECL_VAR,context);
				if(lookfor(ACCS_ELM,context) != -1){
					var_index = lookfor_var(context[lookfor('/',context) + 3]);
					if(context[lookfor('/',context)+1] != 'd' && context[lookfor('/',context)+2] != 'x'){
						if(var_index != -1){
							printf("%c",variables[var_index].c_val);
						}
					}
					else if(context[lookfor('/',context)+2] == 'x'){
						if(var_index != -1){
							printf("%d %c",variables[var_index].i_val,variables[var_index].c_val);
						}
					}
					else{
						if(var_index != -1){
							printf("%d",variables[var_index].i_val);
						}
					}
				}
				else{
					printf("Warning: Missing '/D-'(CHAR),'/d-'(INT), defaulting to CHAR value\nuse --no-warnings to supress this warning\n");
					var_index = lookfor_var(context[lookfor('/',context) + 3]);
					if(var_index != -1){
						printf("%c",variables[var_index].c_val);
					}
				}
			}
			else{
				printf("%c",subchar(operation_index + 1,operation_index + 2,context));
			}
		break;
		case TEST_CTN:
			operation_index = context[lookfor(TEST_CTN,context)];
			switch(context[lookfor(operation_index,context) + 1]){
				case EQUALITY:
					if(lookfor(DECL_VAR,context) != -1){
						if(lookfor_var(context[lookfor(DECL_VAR,context) + 1]) != -1){
							var_index = lookfor_var(context[lookfor(DECL_VAR,context) + 1]);
							if(variables[var_index].c_val != context[lookfor(EQUALITY,context) + 3]){
								state = 1;
							}
						}
						else{
							printf("This variable(%c) doesnt exist or i couldnt find it\n",context[lookfor(DECL_VAR,context) + 1]);
							exit(1);
						}
					}
					else if(context[lookfor(EQUALITY,context) + 1] != context[lookfor(EQUALITY,context) + 2]){
						state = 1;
					}
				break;
				case NOTEQUAL:
					if(lookfor(DECL_VAR,context) != -1){
						if(lookfor_var(context[lookfor(DECL_VAR,context) + 1]) != -1){
							var_index = lookfor_var(context[lookfor(DECL_VAR,context) + 1]);
							if(variables[var_index].c_val == context[lookfor(NOTEQUAL,context) + 3]){
								state = 1;
							}
						}
						else{
							printf("This variable(%c) doesnt exist or i couldnt find it\n",context[lookfor(DECL_VAR,context) + 1]);
							exit(1);
						}
					}
					else if(context[lookfor(NOTEQUAL,context) + 1] == context[lookfor(NOTEQUAL,context) + 2]){
						state = 1;
					}
				break;
			}
		break;
		case LINE_NEW:
			printf("\n");
		break;
		case QUEUE_IT:
			var_index = lookfor_var(context[lookfor(QUEUE_IT,context)+1]);
			if(var_index != -1){
				queue[Qp] = variables[var_index].i_val;
			}
		break;
		case _ADD_NUM:
			queue[Qp] += number(substr(lookfor(_ADD_NUM,context)+1,LINE,context));
		break;
		case PULL_ALL:
			operation_index = lookfor(PULL_ALL,context);
			var_index = lookfor_var(context[operation_index + 1]);
			if(var_index != -1) variables[var_index].i_val = queue[Qp];
			else printf("No such variable\n");
		break;
		case LOOP_FOR:
			times = number(substr(lookfor(LOOP_FOR,context)+1,LINE,context));
			loopst = 2;
		break;
		case INPT_CHR:
			if(lookfor(DECL_VAR,context) != -1){
				var_index = lookfor_var(context[lookfor(DECL_VAR,context)+1]);
				if(var_index != -1){
					variables[var_index].c_val = getchar();
				}
			}
			else{
				tempst = getchar();
			}
		break;
		case CHTO_NUM:
			var_index = lookfor_var(context[lookfor(CHTO_NUM,context)+1]);
			if(var_index != -1){
				variables[var_index].i_val = cvrt(variables[var_index].c_val);
			}
			else{
				printf("No such variable\n");
			}
		break;
	}
}

int main()
{
	FILE *fh;
	for(int g = 0;g < 4;g++){
		queue[g] = 0;
	}
	char reserved[14] = {OPUT_CHR,TEST_CTN,INPT_CHR,CHTO_NUM,LOOP_FOR,PUSH_ALL,PULL_ALL,QUEUE_IT,_ADD_NUM,SUBT_NUM,DECL_VAR,LINE_NEW,ACCS_ELM};

	if((fh = fopen("main.exc","r")) == NULL){
		exit(1);
	}
	String buf = (String)malloc(LINE);
	while((fgets(buf,LINE,fh)) != NULL){
		replace('%',tempst,buf);
		rmall('\n',buf);       // rm all '\n' in buf
		rmall(' ',buf);
		rmall('\t',buf);
		if(state == 1  && buf[0] == ']'){
			state = 0;
		}
		if(loopst == 2 && buf[0] != '}'){
			for(int w = 0;w < times;w++){
				for(int cc = 0; cc < 14;cc++){
					if(lookfor(reserved[cc],buf) != -1){
						eval(reserved[cc],buf);
					}
				}
			}
		}
		else{
			loopst = 0;
		}
		for(int bc = 0; bc < 14; bc++){
			if(lookfor(reserved[bc],buf) != -1 && state == 0 && loopst == 0){
				eval(reserved[bc],buf);
			}
		}
	}
	free(buf);
}
