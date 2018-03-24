#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 1010 
struct variable{
	char name[MAX];
	int num_i;  //����ֵ 
	double num_d;  //������ֵ 
	int type;  //0Ϊ���ͣ�1Ϊ������ 
	struct variable * next;
};  //�����д洢�����Ľṹ�� 
void del_space(char str1[]);//�������ո�ĺ��� 
double CalResult(char ch[], struct variable *head, struct variable *current);//��������ĺ��� 
struct variable *find(struct variable *head, char name[]);//������������ĺ��� 

int main(int argc, char * argv[])
{ 
	FILE * fp;
	if((fp = fopen(argv[1], "r")) == NULL)
		{printf("Can't open !\nPlease try again!");
		 exit(1);}//����ļ��Ƿ���Դ�
	int ch, i;
	char line[MAX];
	const char *delim= ", ;()";
    char *pword;
	struct variable * prev, * current;
	struct variable * head = NULL;
	while((ch = getc(fp)) != EOF)//���ַ�Ϊ��λ��ȡ�ļ� 
    {
	   i=0;
	   memset(line,0,sizeof(line)); //������� 
	   while(!isprint(ch)||ch==' ') {ch = getc(fp);
	                        if(ch == EOF) exit(1);}
	   while(ch != ';')
	   {
		  line[i++] = ch;
		  ch = getc(fp);
	   }
	   line[i]='\0';
       if(strncmp(line, "int ", 4) == 0) //�������ͱ��� 
	   {
	    	pword = strtok(line, delim);//��"int "��ȥ 
	    	while(pword = strtok(NULL, delim))//��ȥ��㡢�ո� 
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
	    else if(strncmp(line, "double ", 7) == 0) //���帡���ͱ��� 
	    {
		    pword = strtok(line, delim);//����double"��ȥ 
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
		{  del_space(line);//�����ո� 
		   if(strncmp(line, "print(", 6)== 0)		//�ж��Ƿ�Ϊ������� 
	       { 
	    	  pword = strtok(line, delim);
		      pword = strtok(NULL, delim);
		      if(isalpha(pword[0]))  //�ж��Ƿ�������� 
		      {
		   	    current = find(head, pword);//�������� 
                if(current->type == 0) printf("%d\n", current->num_i);//�ж�������������� 
		        else printf("%f\n", current->num_d);
	          }
		      else printf("%s\n", pword); 
	       }
	       else//�������㲿�� 
		   CalResult(line, head, current);
     	}
    }
		while(current != NULL)//�ͷ��ڴ� 
	    {
		  free(current);
		  current = current->next;
	    }
	return 0;
}
struct variable *find(struct variable *head, char name[])//��������ĺ���������һ��ͷָ���һ��Ҫ�����ı����� 
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
void del_space(char str1[])  //��ȥ�ַ����пո�ĺ��� 
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
typedef struct   //������Ų������Ľṹ�� 
{
	int type;
	char ch;               //����ch ��Ų����� 
	int level;				//����level ��Ų����������ȼ� 
}OpNode;
typedef struct//�����ַ�ջ 
{
	OpNode opNode[MAX];
	int top;				//���ջ������ 
	int size;				//��ŵ�ǰջ�Ĵ�С 
}OpStack; 
void Op_init(OpStack *ops)//���ַ�ջ�ĳ�ʼ��
{
	ops->top = 0;
	ops->size = 0;
}
void Op_push(OpStack *ops,OpNode op)
{
	ops->size++;
	ops->opNode[(ops->top)++] = op;
}
OpNode Op_pop(OpStack *ops)//�ַ���ջ 
{
	if(ops->size == 0)		//�ж�ջ�Ƿ�Ϊ�գ����Ϊ�գ����˳����򣬷����ջ 
	{
		printf("The op stack is empty!");
		exit(1);
	}
	ops->size--;
	return ops->opNode[--(ops->top)];
}
typedef struct//����������Ľṹ�� 
{
	char name[50];//��ȡ������ 
    double d;		//���帡���ʹ�Ų����� 
	int type;//������������ ,����Ϊ0��������Ϊ1 
}TdNode;
typedef struct//������ջ 
{
	TdNode tdNode[MAX];
	int size;
	int top;
}TdStack;
void Td_init(TdStack *tds)//��ջ�ĳ�ʼ�� 
{
	tds->size = 0;
 	tds->top = 0;
}
void Td_push(TdStack *tds,TdNode td)//��ջ����ջ 
{
	tds->size++;
	tds->tdNode[(tds->top)++] = td;
}
TdNode Td_pop(TdStack *tds)//��ջ�ĳ�ջ 
{
	if(tds->size == 0)		//�ж�ջ�Ƿ�Ϊ�գ����Ϊ�գ����˳����򣬷����ջ 
	{
		printf("The num stack is empty!");
		exit(-1);
	}
	tds->size--;
	return tds->tdNode[--(tds->top)];
}
double CalResult(char ch[], struct variable *head, struct variable *current)//�����������ʽ�ļ����� 
{
	struct variable *find(struct variable *head, char name[]);
	int index = 0;  //�����ַ��������� 
	OpStack ops;	//���� ������ջ 
	TdStack tds;	//���� ������ջ 
	OpNode op;		//���� �ַ��ڵ� 
	TdNode td;		//���� ���ڵ� 
	Op_init(&ops);	//��ʼ���ַ�ջ 
	Td_init(&tds);	//��ʼ��������ջ 
	while(ch[index] != '\0')
	{
		char chr = ch[index]; 		 //ȡ���ַ����Ķ�һ���ַ� 
		if(chr == '+' && ch[index-1] != ')' && !isalnum(ch[index-1])) //�ж��Ƿ�Ϊ���ţ�����ǣ�ֱ�Ӷ�ȡ��һ���ַ� 
		{index++;
		continue;
		}
		if(isalnum(chr) || chr == '.')  //�ж��Ƿ�Ϊ����������� 
		{
			int tempIndex = index;    //���帨������ 
			int i = 0;
			char tempCh[MAX] ={0};	  //����������һ���������������г�ʼ��
            while(isalnum(chr) || chr == '.')   //��һ�����������ַ�������ȡ�����������tempCh������ 
			    {
				  tempCh[i++] = ch[tempIndex];
				  tempIndex++;
				  chr = ch[tempIndex];
			    }
			if(isdigit(tempCh[0]))//�ж��Ƿ�Ϊ���� 
			{
				char *p;
		        if((p=strchr(tempCh, '.' ))== NULL) td.type = 0;//û��С���㼴Ϊ���� 
                else td.type = 1;
	            td.d = atof(tempCh); 
		        Td_push(&tds,td);		//��ȡ���Ĳ�����ѹ�뵽������ջ 
		        index = tempIndex;		
			}
			else{current = find(head, tempCh);//�������������ñ��� 
				 td.type = current->type;
				 if(td.type == 0) td.d = current->num_i;
				 else td.d = current->num_d;
				 strcpy(td.name, tempCh);
				 Td_push(&tds,td);		//��ȡ���Ĳ�����ѹ�뵽������ջ 
		         index = tempIndex;
			    } 
		}
		if(chr == '=') //�ж��Ƿ�Ϊ��ֵ 
		{
			op.ch = chr;
			op.level = 1;
			while(ops.size != 0)
			{
				int level_1 =(&ops)->opNode[(&ops)->size - 1].level;//����������ж����ȼ� 
				if(level_1>op.level)
				{
				   char op1 = Op_pop(&ops).ch;
				   double num = 0; // ����һ���������ڽ��ռ���Ľ��
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
		                      case '/':if(num_2 == 0)            // �������Ϊ�㣬���Ƴ����򲢴�ӡ������Ϣ        
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
		        if(ops.size == 0)   //���ַ�ջ�ǿ�ջ����ֱ�ӽ�����ջ�Ĳ��� 
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		    }
		if(chr == '+' || chr == '-')		//�ж��Ƿ�Ϊ�ӷ�������������߸��� 
		{
			if(ch[index-1]==')' || isalnum(ch[index-1]))
			{op.ch = chr;	//��Ų��������������ڵ� 
		    op.level = 2;}
			else{op.ch = '#'; 
			     op.level = 4;}	  //����������ֵ���ȼ� 
			while(ops.size != 0)   //���ַ�ջ��Ϊ�գ�������ַ������ȼ��Ƚ� 
			{
				int level_1 = (&ops)->opNode[(&ops)->size - 1].level;
			//�����ַ��Ƚ����ȼ������µ��ַ����ȼ���ջ�е��ַ����ȼ��ߣ���
			//���ַ�ջ���ַ���ջ��ͬʱ����ջ�г�ջ�����������м��㣬�����
				//��������ջ,�����µ��ַ���ջ     
				if(level_1>op.level)
				{
				    char op1 = Op_pop(&ops).ch;
				    double num = 0; // ����һ���������ڽ��ռ���Ľ��
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
		                      case '/':if(num_2 == 0)            // �������Ϊ�㣬���Ƴ����򲢴�ӡ������Ϣ        
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
			if(ops.size == 0)   //���ַ�ջ�ǿ�ջ����ֱ�ӽ�����ջ�Ĳ��� 
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		}
		if(chr == '*' || chr == '/')		//�ж��Ƿ�Ϊ�˷����߳���������� 
		{
			op.ch = chr;    //��Ų��������������ڵ� 
			op.level = 3;     //����������ֵ���ȼ� 
			while(ops.size != 0)
			{
				int level_1 = (&ops)->opNode[(&ops)->size - 1].level;//�����ַ��Ƚ����ȼ������µ��ַ����ȼ���ջ�е��ַ����ȼ��ߣ���
			                                                         //���ַ�ջ���ַ���ջ��ͬʱ����ջ�г�ջ�����������м��㣬�����
				                                                      //��������ջ,�����µ��ַ���ջ  
				if(level_1>=op.level)
				{				    char op1 = Op_pop(&ops).ch;
				    double num = 0; // ����һ���������ڽ��ռ���Ľ��
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
		                      case '/':if(num_2 == 0)            // �������Ϊ�㣬���Ƴ����򲢴�ӡ������Ϣ        
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
			if(ops.size == 0)   //���ַ�ջ�ǿ�ջ����ֱ�ӽ�����ջ�Ĳ���
			{
				Op_push(&ops,op);
			}
			index++;
			continue;
		}
		if(chr == '(')		//�ж��Ƿ�Ϊ�����ţ�ֱ�ӽ�����ջ���� 
		{
			op.ch = chr;
			op.level = 0;
			Op_push(&ops,op);
			index++;
			continue;
		}
		if(chr == ')')		//�ж��Ƿ�Ϊ������ 
		{
			char ch1 = (&ops)->opNode[(&ops)->size - 1].ch; 
			while(ch1 != '(')			//���г�ջ�Ĳ�����֪������������Ϊֹ��
			{
					   char op1 = Op_pop(&ops).ch;
				       double num = 0; // ����һ���������ڽ��ռ���Ľ��
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
		                      case '/':if(num_2 == 0)            // �������Ϊ�㣬���Ƴ����򲢴�ӡ������Ϣ        
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
	while(ops.size != 0)	//����ַ�ջ��Ϊ�գ���һֱ��ջֱ���ַ�ջΪ�ա� 
	{
		char op1 = Op_pop(&ops).ch;
		double num = 0; // ����һ���������ڽ��ռ���Ľ��
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
		        case '/':if(num_2 == 0)            // �������Ϊ�㣬���Ƴ����򲢴�ӡ������Ϣ        
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
	return Td_pop(&tds).d;	//�������ջ���� 
}
