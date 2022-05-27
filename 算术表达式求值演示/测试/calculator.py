from tkinter import *
from functools import partial
from ctypes import *
cpy=CDLL('./function.dll')
cpy.EvaluateExpression.restype=c_double
cpy.check.restype=c_int
cpy.variable.restype=c_int
cpy.change.restype=c_void_p

#生成计算器主界面
def layout(root):
    label=Label(root,width=29,height=1,bd=5,bg='#FFFACD',anchor='se',textvariable=label_text)  #标签，可以显示文字或图片
    label.grid(row=0,columnspan=5)  #布局器，向窗口注册并显示控件； rowspan：设置单元格纵向跨越的列数
    entry=Entry(root,width=23,bd=5,bg='#FFFACD',justify="right",font=('微软雅黑', 12))  #文本框（单行）
    entry.grid(row=1,column=0,columnspan=5,sticky=N+W+S+E,padx=5,pady=5)  #设置控件周围x、y方向空白区域保留大小
    myButton=partial(Button,root,width=5,cursor='hand2',activebackground='#90EE90')  # 偏函数：带有固定参数的函数
    #command指定按钮消息的回调函数
    button_clear=myButton(text=' C ',command=lambda:clear(entry))
    button_left=myButton(text='(',command=lambda:entry.insert(INSERT,'('))
    button_right=myButton(text=')',command=lambda:entry.insert(INSERT,')'))
    button_backspace=myButton(text='←',command=lambda:entry.delete(len(entry.get())-1)) #删除文本框的最后一个输入值  
    button_x=myButton(text=' x ',command=lambda:entry.insert(INSERT,'x'))  
    button_clear.grid(row=3,column=0)
    button_left.grid(row=3,column=1)
    button_right.grid(row=3,column=2)
    button_backspace.grid(row=3,column=3)  
    button_x.grid(row=3,column=4)
    #第二行
    button_7=myButton(text=' 7 ',command=lambda:entry.insert(INSERT,'7'))
    button_8=myButton(text=' 8 ',command=lambda:entry.insert(INSERT,'8'))
    button_9=myButton(text=' 9 ',command=lambda:entry.insert(INSERT,'9'))
    button_divide=myButton(text=' / ',command=lambda:entry.insert(INSERT,'/'))
    button_fx=myButton(text='赋值',command=lambda:label_text.set('x='))
    button_7.grid(row=4,column=0)
    button_8.grid(row=4,column=1)
    button_9.grid(row=4,column=2)
    button_divide.grid(row=4,column=3)   
    button_fx.grid(row=4,column=4)
    #第三行
    button_4=myButton(text=' 4 ',command=lambda:entry.insert(INSERT,'4'))
    button_5=myButton(text=' 5 ',command=lambda:entry.insert(INSERT,'5'))
    button_6=myButton(text=' 6 ',command=lambda:entry.insert(INSERT,'6'))
    button_multi=myButton(text=' * ',command=lambda:entry.insert(INSERT,'*'))
    button_sure=myButton(text='确认',command=lambda:sure(entry))
    button_4.grid(row=5,column=0)
    button_5.grid(row=5,column=1)
    button_6.grid(row=5,column=2)
    button_multi.grid(row=5,column=3)
    button_sure.grid(row=5,column=4)
    
    #第四行
    button_1=myButton(text=' 1 ',command=lambda:entry.insert(INSERT,'1'))
    button_2=myButton(text=' 2 ',command=lambda:entry.insert(INSERT,'2'))
    button_3=myButton(text=' 3 ',command=lambda:entry.insert(INSERT,'3'))
    button_subtract=myButton(text=' - ',command=lambda:entry.insert(INSERT,'-'))
    button_equal=myButton(text=' \n = \n ',command=lambda:calculate(entry))
    button_1.grid(row=6,column=0)
    button_2.grid(row=6,column=1)
    button_3.grid(row=6,column=2)
    button_subtract.grid(row=6,column=3)
    button_equal.grid(row=6,column=4,rowspan=2)  
    #第五行
    button_power=myButton(text='^',command=lambda:entry.insert(INSERT,'^'))
    button_0=myButton(text=' 0 ',command=lambda:entry.insert(INSERT,'0'))
    button_point=myButton(text=' . ',command=lambda:entry.insert(INSERT,'.'))
    button_plus=myButton(text=' + ',command=lambda:entry.insert(INSERT,'+'))
    button_power.grid(row=7,column=0)
    button_0.grid(row=7,column=1)
    button_point.grid(row=7,column=2)
    button_plus.grid(row=7,column=3)

#删除所有输入内容和显示内容
def clear(entry):
    entry.delete(0,END)
    label_text.set('')

def sure(entry):   
    global m
    m=entry.get()
    if m=='':
        m=0
    m=float(m)
    clear(entry)
    return m

# 点击“=”后进行计算
def calculate(entry):
    try:
        formula=entry.get()
        x=formula
        x=x.encode('utf8')
        x=c_char_p(x) 
        if cpy.variable(x)==1: 
            cpy.change(x,c_double(m))
        clear(entry)
        if cpy.check(x)==1:
            entry.insert(END,'出错(T_T)')
        else:
            result=cpy.EvaluateExpression(x)
            if abs(result)==float('inf'):
                entry.insert(END,'发生除0错误(-_-)')
            else:
                entry.insert(END,result)
        label_text.set(''.join(formula+'='))
    except:
        clear(entry)
        entry.insert(END,'出错(T_T)')


if __name__ == '__main__':
    root=Tk()  #生成窗口
    root.title('计算器')  #窗口的名字
    root.resizable(0,0)  #窗口大小可调性，分别表示x，y方向的可变性
    global label_text  #定义全局变量
    label_text=StringVar()
    layout(root)
    root.mainloop()  #进入消息循环（必需组件），否则生成的窗口一闪而过