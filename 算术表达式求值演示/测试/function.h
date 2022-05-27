double Opreate(double a,double b,char optr); //对操作数和对应的运算符进行计算并返回结果
int In(char c,char *tr); //判断字符是否为运算符
char Precede(char m, char n, char *OP); //判断运算符的优先级
double EvaluateExpression(char *expr); //算术表达式求值的算符优先算法
void clear(char *c);//删除输入的空格
int check(char *c);//检查是否有非法字符输入
void negative(char *c);//处理负数问题
void change(char *c,double x);//将变量x赋值
int variable(char *c);//判断输入是否为变量