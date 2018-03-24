#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 1010 
struct variable{
	char name[MAX];
	int num_i;  //整型值 
	double num_d;  //浮点型值 
	int type;  //0为整型，1为浮点型 
	struct variable * next;
};  //链表中存储变量的结构体 
void del_space(char str1[]);//声明除空格的函数 
double CalResult(char ch[], struct variable *head, struct variable *current);//声明计算的函数 
struct variable *find(struct variable *head, char name[]);//声明遍历链表的函数 

int main(int argc, char * argv[])
{ 
	FILE * fp;
	if((fp = fopen(argv[1], "r")) == NULL)
		{printf("Can't open !\nPlease try again!");
		 exit(1);}//检测文件是否可以打开
	int ch, i;
	char line[MAX];
	const char *delim= ", ;()";
    char *pword;
	struct variable * prev, * current;
	struct variable * head = NULL;
	while((ch = getc(fp)) != EOF)//以字符为单位读取文件 
    {
	   i=0;
	   memset(line,0,sizeof(line)); //清空数组 
	   while(!isprint(ch)||ch==' ') {ch = getc(fp);
	                        if(ch == EOF) exit(1);}
	   while(ch != ';')
	   {
		  line[i++] = ch;
		  ch = getc(fp);
	   }
	   line[i]='\0';
       if(strncmp(line, "int ", 4) == 0) //定义整型变量 
	   {
	    	pword = strtok(line, delim);//将"int "除去 
	    	while(pword = strtok(NULL, delim))//除去标点、空格 
            {
		    current = (struct variable *)malloc(sizeof(struct variable));
		    if(head == NULL)
		    head = current;
		    else
		    prev->next = current;
		    current->next = NULL;
		    strcpy(current->name, pword);
		    current->type = 0;
		    current->num_i = 0;
		     prev = current;
	    	}
	    }
	    else if(strncmp(line, "double ", 7) == 0) //定义浮点型变量 
	    {
		    pword = strtok(line, delim);//将“double"除去 
		    while(pword = strtok(NULL, delim))
            {
		      current = (struct variable *)malloc(sizeof(struct variable));
		      if(head == NULL)
		      head = current;
		      else
		      prev->next = current;
		      current->next = NULL;
		      strcpy(current->name, pword);
		      current->type = 1;
		      current->num_d = 0;
		      prev = current;
	   	    }
	      }
	    else 
		{  del_space(line);//除掉空格 
		   if(strncmp(line, "print(", 6)== 0)		//判断是否为输出部分 
	       { 
	    	  pword = strtok(line, delim);
		      pword = strtok(NULL, delim);
		      if(isalpha(pword[0]))  //判断是否输出变量 
		      {
		   	    current = find(head, pword);//遍历链表 
                if(current->type == 0) printf("%d\n", current->num_i);//判断输出变量的类型 
		        else printf("%f\n", current->num_d);
	          }
		      else printf("%s\n", pword); 
	       }
	       else//进入运算部分 
		   CalResult(line, head, current);
     	}
    }
		while(current != NULL)//释放内存 
	    {
		  free(current);
		  current = current->next;
	    }
	return 0;
}
struct variable *find(struct variable *head, char name[])//遍历链表的函数，传入一个头指针和一个要搜索的变量名 
{
	struct variable *current = head;
	while(current != NULL)
	{
	  if(strcmp(name, current->name) != 0) 
	  current = current->next;
	  else break;
	}
	return current;  
}
void del_space(char str1[])  //除去字符串中空格的函数 
{
	int i, j;
	char *str2 = (char *)calloc(MAX, sizeof(char));
	for(i=0, j=0; i<strlen(str1); i++)
	{
		if(str1[i] == ' ') continue;
		else str2[j++] = str1[i];
	}
	strcpy(str1, str2);
	free(str2);
}
typedef struct   //创建存放操作符的结构体 
{
	int type;
	char ch;               //定义ch 存放操作符 
	int level;				//定义level 存放操作符的优先级 
}OpNode;
typedef struct//创建字符栈 
{
	OpNode opNode[MAX];
	int top;				//存放栈顶的数 
	int size;				//存放当前栈的大小 
}OpStack; 
void Op_init(OpStack *ops)//对字符栈的初始化
{
	ops->top = 0;
	ops->size = 0;
}
void Op_push(OpStack *ops,OpNode op)
{
	ops->size++;
	ops->opNode[(ops->top)++] = op;
}
OpNode Op_pop(OpStack *ops)//字符出栈 
{
	if(ops->size == 0)		//判断栈是否为空，如果为空，则退出程序，否则出栈 
	{
		printf("The op stack is empty!");
		exit(1);
	}
	ops->size--;
	return ops->opNode[--(ops->top)];
}
typedef struct//创建存放数的结构体 
{
	char name[50];//存取变量名 
    double d;		//定义浮点型存放操作数 
	int type;//定义存放数类型 ,整型为0，浮点型为1 
}TdNode;
typedef struct//创建数栈 
{
	TdNode tdNode[MAX];
	int size;
	int top;
}TdStack;
void Td_init(TdStack *tds)//数栈的初始化 
{
	tds->size = 0;
 	tds->top = 0;
}
void Td_push(TdStack *tds,TdNode td)//数栈的入栈 
{
	tds->size++;
	tds->tdNode[(tds->top)++] = td;
}
TdNode Td_pop(TdStack *tds)//数栈的出栈 
{
	if(tds->size == 0)		//判断栈是否为空，如果为空，则退出程序，否则出栈 
	{
		printf("The num stack is empty!");
		exit(-1);
	}
	tds->size--;
	return tds->tdNode[--(tds->top)];
}
double CalResult(char ch[], struct variable *head, struct variable *current)//返回整个表达式的计算结果 
{
	struct variable *find(struct variable *head, char name[]);
	int index = 0;  //定义字符串的索引 
	OpStack ops;	//定义 操作符栈 
	TdStack tds;	//定义 操作数栈 
	OpNode op;		//定义 字符节点 
	TdNode td;		//定义 数节点 
	Op_init(&ops);	//初始化字符栈 
	Td_init(&tds);	//初始化操作数栈 
	while(ch[index] != '\0')
	{
		char chr = ch[index]; 		 //取出字符串的而一个字符 
		if(chr == '+' && ch[index-1] != ')' && !isalnum(ch[index-1])) //判断是否为正号，如果是，直接读取下一个字符 
		{index++;
		continue;
		}
		if(isalnum(chr) || chr == '.')  //判断是否为操作数或变量 
		{
			int tempIndex = index;    //定义辅助索引 
			int i = 0;
			char tempCh[MAX] ={0};	  //定义数组存放一个操作数，并进行初始化
            while(isalnum(chr) || chr == '.')   //将一个操作数从字符数组中取出，并存放在tempCh数组中 
			    {
				  tempCh[i++] = ch[tempIndex];
				  tempIndex++;
				  chr = ch[tempIndex];
			    }
			if(isdigit(tempCh[0]))//判断是否为数字 
			{
				char *p;
		        if((p=strchr(tempCh, '.' ))== NULL) td.type = 0;//没有小数点即为整型 
                else td.type = 1;
	            td.d = atof(tempCh); 
		        Td_push(&tds,td);		//把取出的操作数压入到操作数栈 
		        index = tempIndex;		
			}
			else{current = find(head, tempCh);//在链表中搜索该变量 
				 td.type = current->type;
				 if(td.type == 0) td.d = current->num_i;
				 else td.d = current->num_d;
				 strcpy(td.name, tempCh);
				 Td_push(&tds,td);		//把取出的操作数压入到操作数栈 
		         index = tempIndex;
			    } 
		}
		if(chr == '=') //判断是否为赋值 
		{
			op.ch = chr;
			op.level = 1;
			while(ops.size != 0)
			{
				int level_1 =(&ops)->opNode[(&ops)->size - 1].level;//两个运算符判断优先级 
				if(level_1>op.level)
				{
				   char op1 = Op_pop(&ops).ch;
				   double num = 0; // 定义一个变量用于接收计算的结果
				   if(op1 == '#')
				        {double num_2 = Td_pop(&tds).d;
				         num = 0 - num_2;}
				    else{int type2 = (&tds)->tdNode[(&tds)->size - 1].type;
						 double num_2 = Td_pop(&tds).d;
					     char tempname[50];
						 strcpy(tempname, (&tds)->tdNode[(&tds)->size - 1].name);
					     int type1 = (&tds)->tdNode[(&tds)->size - 1].type;
					     double num_1 = Td_pop(&tds).d;
	                     switch(op1)
	                        {
		                      case '+':num = num_1 + num_2;break;
		                      case '-':num = num_1 - num_2;break;
		                      case '*':num = num_1 * num_2;break;
		                      case '/':if(num_2 == 0)            // 如果除数为零，则推出程序并打印错误信息        
					              {
						            printf("divided by ZERO\n");
						             exit(-1);
					               }
		                             else
									    {
									    	if(type1 == 0 && type2 == 0) num = (int)num_1/(int)num_2;
									    	else num = num_1 / num_2;
									    } break; 
							  case '=':num = num_2;
							         current = find(head, tempname);
									 if(current->type == 0) current->num_i = (int)num_2;
				                     else current->num_d = num_2;break; 		    
	                         }
	                     }
					td.d = num;
					Td_push(&tds,td);
				}
				else{
				    Op_push(&ops,op);
					break;
				     }
		        } 
		        if(ops.size == 0)   //若字符栈是空栈，则直接进行入栈的操作 
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		    }
		if(chr == '+' || chr == '-')		//判断是否为加法、减法运算或者负号 
		{
			if(ch[index-1]==')' || isalnum(ch[index-1]))
			{op.ch = chr;	//存放操作符到操作符节点 
		    op.level = 2;}
			else{op.ch = '#'; 
			     op.level = 4;}	  //给操作符赋值优先级 
			while(ops.size != 0)   //若字符栈不为空，则进行字符的优先级比较 
			{
				int level_1 = (&ops)->opNode[(&ops)->size - 1].level;
			//两个字符比较优先级，若新的字符优先级比栈中的字符优先级高，则
			//从字符栈中字符出栈，同时从数栈中出栈两个数，进行计算，计算结
				//果存入数栈,否则将新的字符入栈     
				if(level_1>op.level)
				{
				    char op1 = Op_pop(&ops).ch;
				    double num = 0; // 定义一个变量用于接收计算的结果
				    if(op1 == '#')
				        {double num_2 = Td_pop(&tds).d;
				         num = 0 - num_2;}
				    else{int type2 = (&tds)->tdNode[(&tds)->size - 1].type;
						 double num_2 = Td_pop(&tds).d;
					     char tempname[50];
						 strcpy(tempname, (&tds)->tdNode[(&tds)->size - 1].name);
					     int type1 = (&tds)->tdNode[(&tds)->size - 1].type;
					     double num_1 = Td_pop(&tds).d;
	                     switch(op1)
	                        {
		                      case '*':num = num_1 * num_2;break;
		                      case '/':if(num_2 == 0)            // 如果除数为零，则推出程序并打印错误信息        
					              {
						            printf("divided by ZERO\n");
						             exit(-1);
					               }
		                             else
									    {
									    	if(type1 == 0 && type2 == 0) num = (int)num_1/(int)num_2;
									    	else num = num_1 / num_2;
									    } break; 
							  case '=':num = num_2;
							         current = find(head, tempname);
									 if(current->type == 0) current->num_i = (int)num_2;
				                     else current->num_d = num_2;break; 		    
	                         }
	                     }
					td.d = num;
					Td_push(&tds,td);
				}
				else
				{
					Op_push(&ops,op);
					break;
				}
			}
			if(ops.size == 0)   //若字符栈是空栈，则直接进行入栈的操作 
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		}
		if(chr == '*' || chr == '/')		//判断是否为乘法或者除法的运算符 
		{
			op.ch = chr;    //存放操作符到操作符节点 
			op.level = 3;     //给操作符赋值优先级 
			while(ops.size != 0)
			{
				int level_1 = (&ops)->opNode[(&ops)->size - 1].level;//两个字符比较优先级，若新的字符优先级比栈中的字符优先级高，则
			                                                         //从字符栈中字符出栈，同时从数栈中出栈两个数，进行计算，计算结
				                                                      //果存入数栈,否则将新的字符入栈  
				if(level_1>=op.level)
				{				    char op1 = Op_pop(&ops).ch;
				    double num = 0; // 定义一个变量用于接收计算的结果
				    if(op1 == '#')
				        {double num_2 = Td_pop(&tds).d;
				         num = 0 - num_2;}
				    else{int type2 = (&tds)->tdNode[(&tds)->size - 1].type;
						 double num_2 = Td_pop(&tds).d;
					     char tempname[50];
						 strcpy(tempname, (&tds)->tdNode[(&tds)->size - 1].name);
					     int type1 = (&tds)->tdNode[(&tds)->size - 1].type;
					     double num_1 = Td_pop(&tds).d;
	                     switch(op1)
	                        {
		                    case '+':num = num_1 + num_2;break;
		                    case '-':num = num_1 - num_2;break;
		                      case '*':num = num_1 * num_2;break;
		                      case '/':if(num_2 == 0)            // 如果除数为零，则推出程序并打印错误信息        
					              {
						            printf("divided by ZERO\n");
						             exit(-1);
					               }
		                             else
									    {
									    	if(type1 == 0 && type2 == 0) num = (int)num_1/(int)num_2;
									    	else num = num_1 / num_2;
									    } break; 
							  case '=':num = num_2;
							         current = find(head, tempname);
							         //printf("tempname:%s", tempname);
									 if(current->type == 0) current->num_i = (int)num_2;
				                     else current->num_d = num_2;break; 		    
	                         }
	                     }
					td.d = num;
					Td_push(&tds,td);}
				else
		         	{
					Op_push(&ops,op);	
					break;
                    }
	            }
			if(ops.size == 0)   //若字符栈是空栈，则直接进行入栈的操作
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		}
		if(chr == '(')		//判断是否为左括号，直接进行入栈操作 
		{
			op.ch = chr;
			op.level = 0;
			Op_push(&ops,op);
			index++;
			continue;
		}
		if(chr == ')')		//判断是否为右括号 
		{
			char ch1 = (&ops)->opNode[(&ops)->size - 1].ch; 
			while(ch1 != '(')			//进行出栈的操作，知道遇到左括号为止。
			{
					   char op1 = Op_pop(&ops).ch;
				       double num = 0; // 定义一个变量用于接收计算的结果
				       if(op1 == '#')
				        {double num_2 = Td_pop(&tds).d;
				         num = 0 - num_2;}
				    else{int type2 = (&tds)->tdNode[(&tds)->size - 1].type;
						 double num_2 = Td_pop(&tds).d;
					     char tempname[50];
						 strcpy(tempname, (&tds)->tdNode[(&tds)->size - 1].name);
						//printf("tempname:%s\n", tempname);
					     int type1 = (&tds)->tdNode[(&tds)->size - 1].type;
					     double num_1 = Td_pop(&tds).d;
	                     switch(op1)
	                        {
		                      case '+':num = num_1 + num_2;break;
		                      case '-':num = num_1 - num_2;break;
		                      case '*':num = num_1 * num_2;break;
		                      case '/':if(num_2 == 0)            // 如果除数为零，则推出程序并打印错误信息        
					              {
						            printf("divided by ZERO\n");
						             exit(-1);
					               }
		                             else
									    {
									    	if(type1 == 0 && type2 == 0) num = (int)num_1/(int)num_2;
									    	else num = num_1 / num_2;
									    } break; 
							  case '=':num = num_2;
							         current = find(head, tempname);
									 if(current->type == 0) current->num_i = (int)num_2;
				                     else current->num_d = num_2;break; 		    
	                         }
	                     }
					td.d = num;
					Td_push(&tds,td);
				ch1 = (&ops)->opNode[(&ops)->size - 1].ch;	
			}
			Op_pop(&ops);
			index++;
			continue;
		}
		}
	while(ops.size != 0)	//如果字符栈不为空，则一直出栈直到字符栈为空。 
	{
		char op1 = Op_pop(&ops).ch;
		double num = 0; // 定义一个变量用于接收计算的结果
		if(op1 == '#')
			{double num_2 = Td_pop(&tds).d;
			 num = 0 - num_2;}
		else{int type2 = (&tds)->tdNode[(&tds)->size - 1].type;
			 double num_2 = Td_pop(&tds).d;
			 char tempname[50];
			 strcpy(tempname, (&tds)->tdNode[(&tds)->size - 1].name);
			 current = find(head, tempname);
			 int type1 = (&tds)->tdNode[(&tds)->size - 1].type;
			 double num_1 = Td_pop(&tds).d;
	         switch(op1)
	            {
		        case '+':num = num_1 + num_2;break;
		        case '-':num = num_1 - num_2;break;
		        case '*':num = num_1 * num_2;break;
		        case '/':if(num_2 == 0)            // 如果除数为零，则推出程序并打印错误信息        
					        {
						        printf("divided by ZERO\n");
						        exit(-1);
					        }
		                else
						{
							if(type1 == 0 && type2 == 0) num = (int)num_1/(int)num_2;
							else num = num_1 / num_2;
						} break; 
				case '=':num = num_2;
						if(current->type == 0) current->num_i = (int)num_2;
				        else current->num_d = num_2;break; 		    
	            }
	        }
					td.d = num;
					Td_push(&tds,td);
	}
	return Td_pop(&tds).d;	//将结果出栈返回 
}
