#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
# define LENGTH 4096

typedef char String[LENGTH];
char *inputString(FILE* fp, size_t size){
  //The size is extended by the input with the value of the provisional
  char *str;
  int ch;
  size_t len = 0;
  str = realloc(NULL, sizeof(char)*size);//size is start size
  if(!str)return str;
  while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
    str[len++]=ch;
    if(len==size){
      str = realloc(str, sizeof(char)*(size+=16));
      if(!str)return str;
    }
  }
  str[len++]='\0';

  return realloc(str, sizeof(char)*len);
}
int words(const char *sentence)
{
  int count,i,len;
  char lastC;
  len=strlen(sentence);
  if(len > 0)
    {
      lastC = sentence[0];
    }
  for(i=0; i<=len; i++)
    {
      if(sentence[i]==' ' && lastC != ' ')
        {
 
	  count++;
        }
      lastC = sentence[i];
    }
 
  return count+1;
}


int main(void){
  String sentance,regExpression;
  char* token;
  int i, tokenLen,newStringLength,reti,sizeTwo;
  char *strOne, *strTwo, *saveptrTwo;
  regex_t regex;                                                                        char msgbuf[100];  
  printf("please enter a string to analyze");
//sentance= inputString(stdin,1000);
  fgets(sentance,LENGTH,stdin);
  printf(" please enter reg exp:");
//regExpression= inputString(stdin,1000);
// fgets(regExpression,LENGTH,stdin);
  scanf("%s/n ",regExpression); 
  char  *saveptr=sentance;
  int size=strlen(sentance);
  token= strtok_r(sentance,".!?",&saveptr); 
  while(token!=NULL){
       printf("%s\n ", token);
       sizeTwo=words(token);
    
       reti = regcomp(&regex, regExpression, 0);
       if (reti) {
	 fprintf(stderr, "Could not compile regex\n");
	 exit(1);
  }

    /* Execute regular expression */
  reti = regexec(&regex, token, 0, NULL, 0);
  if (!reti) {  
    printf("Yes %d words \n",sizeTwo);
  }
  else if (reti == REG_NOMATCH) {
    printf(" No  %d  words  \n ",sizeTwo);
   
  }
  else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
  }
    regfree(&regex);   
    token= strtok_r(NULL,".!?",&saveptr);
  }
 
 return(EXIT_SUCCESS);
}
