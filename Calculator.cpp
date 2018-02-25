#include <stdio.h>
#define MAX_STR 10000
#define MAX_LEVEL 2


int flagch(char ch)
{
    if('0'<=ch && ch<='9')return 9;
    if(ch=='.')return 9; 
    if(ch=='+' || ch=='-')return 1;
    if(ch=='*' || ch=='/')return 2;
    if(ch=='(' || ch==')')return 9;
    return -1;
}

char *highofstr(char *low)
{
    while(*low!='\0')
        low++;
    return low-1;
}

double trans(char *low, char *high)
{   
    double num=0;
    int cnt_point=-1;
    while(low<=high)
    {
        if( *low=='.' || cnt_point>-1 )
            cnt_point++;
        if( *low!='.' )
            num= 10*num+((*low)-'0');
        low++;
    }
    for( ; cnt_point>0; cnt_point--)
        num /=10;
    return num;
}

double deal(char *low, char *high, int level)
{
  if(level>MAX_LEVEL)
  {
    if( *low!='(' )
        return trans(low, high);
    else
        return deal(low+1, high-1, 1);
  }
  else
  {
    int cnt_kh=0;
    char *p=high;
     while( (flagch(*p)!=level && p>low) || (cnt_kh!=0) )
    {
        if(*p=='(')cnt_kh++;
        if(*p==')')cnt_kh--;
        p--;
    } 
    
    if(p<=low)
        return deal(low, high, 9);
    else if(*p=='+')
        return deal(low, p-1, level)+deal(p+1, high, level+1);
    else if(*p=='-')
        return deal(low, p-1, level)-deal(p+1, high, level+1);
    else if(*p=='*')
        return deal(low, p-1, level)*deal(p+1, high, level+1);
    else if(*p=='/')
        return deal(low, p-1, level)/deal(p+1, high, level+1);
  }
}

void Enterstr(char *str)
{
    for(int i=0; i<MAX_STR; i++)
    {
        scanf("%c", str);
        if(*str=='\n')break;
        if(*str!=' ')str++;
    } 
    *str='\0';
}

int main()
{
    char str[MAX_STR+1];
    while(1)
    {
        Enterstr(str);
        printf("%.8f\n", deal(str, highofstr(str), 1));
    }
    return 0;
}
