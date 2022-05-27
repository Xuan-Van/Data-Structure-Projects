
%声明cls版本
\NeedsTeXFormat{LaTeX2e}[1995/12/01]

%提供新的class类型
\ProvidesClass{DateStructure}

% 加载已有Class
\LoadClass[a4paper,12pt,twoside]{article}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 加载宏包
% 支持中文的 ctex 宏包
\RequirePackage{ctex}
\RequirePackage{ifxetex}
\RequirePackage{geometry}

%中文字体
\RequirePackage{fontspec, xunicode, xltxtra}
\RequirePackage{xeCJK}

% 数学宏包
\RequirePackage{amsmath}
\RequirePackage{amsfonts}
\RequirePackage{amssymb}
\RequirePackage{bm}
\RequirePackage{titlesec}
\RequirePackage{titletoc}

% 设置颜色
\RequirePackage[x11names,svgnames,dvipsnames]{xcolor}

% 图片、表格宏包
\RequirePackage{graphicx}
\RequirePackage{array,lastpage}
\RequirePackage{longtable}
\RequirePackage{booktabs}
\RequirePackage{multirow}
\RequirePackage{bigstrut}
\RequirePackage{cprotect}

%绘图工具
\RequirePackage{tikz}
%自动生成pdf书签
\RequirePackage{hyperref}

%代码宏包
\RequirePackage{listings}
\RequirePackage{url}
%其他宏包
\RequirePackage{float}
\RequirePackage{caption}
\RequirePackage{enumitem}
\RequirePackage{ulem}
\RequirePackage{calc}
\RequirePackage[titletoc,title]{appendix}
\RequirePackage{fancyhdr}




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%% Document Layout
% 页面布局
\geometry{top=25.4mm,bottom=25.4mm,left=31.8mm,right=31.8mm}
\renewcommand*{\baselinestretch}{1.38}

%设置字体
\ifxetex
\RequirePackage{ctex}
\setmainfont{Times New Roman}
\setCJKmainfont[AutoFakeBold = {2.15}]{SimSun}
\setCJKfamilyfont{song}[AutoFakeBold]{SimSun}
\newcommand*{\song}{\CJKfamily{song}}
\else
\RequirePackage[UTF8]{ctex}
\usepackage{newtxtext}
\usepackage{newtxmath}
\fi

% 更好的代码颜色
\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{mauve}{rgb}{0.58,0,0.82}


%代码样式
\lstset{
  frame=tb,
  aboveskip=3mm,
  belowskip=3mm,
  showstringspaces=false,
  columns=flexible,
  framerule=1pt,
  rulecolor=\color{gray!35},
  backgroundcolor=\color{gray!5},
  basicstyle={\small\ttfamily},
  numbers=left,
  numberstyle=\small\color{black},
  keywordstyle=\color{blue},
  commentstyle=\color{dkgreen},
  stringstyle=\color{mauve},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=3,
}
%超链接格式
\hypersetup{
	colorlinks=true,
	linkcolor=black,
	urlcolor=blue
}

\setlength\parindent{2em}


%设置页眉
\pagestyle{fancy}
\fancyhead{}
\fancyhead[OL]{\songti {\zihao{5} \@SubjectName} } % O: 奇数页, L: 左页眉 \rightmark:章节号
\fancyhead[OR]{\songti \leftmark} % R: 右页眉 \thepage: 页码
\fancyhead[EL]{\songti {\zihao{5} 数据结构课程设计报告}} % E: 偶数页
\fancyhead[ER]{\songti \leftmark} % \leftmark: 大章节号

% 浮动环境设置
% 默认情况下, \LaTeX{} 要求每页的文字至少占据 20%,否则该页就只单独放置一个浮动环境,
% 而这通常不是我们想要的, 我们将这个要求降低到 5%.
 \renewcommand*{\textfraction}{0.05}
% 有时如果多个浮动环境连续放在一起, \LaTeX{}
% 会将它们分在几个不同页，即使它们可在同一页放
% 得下. 我们可以通过修改 |\topfraction| 和 |\bottomfraction| 分别设置顶端和底端的浮
% 动环境的最大比例.
 \renewcommand*{\topfraction}{0.9}
 \renewcommand*{\bottomfraction}{0.8}
% 有时\LaTeX{}会把一个浮动环境单独放在一页,
% 我们要求这个环境至少要占据 85% 才能单独放在一页.
% 注意:  |\floatpagefraction| 的数值必须小于 |\topfraction|.
 \renewcommand*{\floatpagefraction}{0.85}
% 关于图片 graphicx
% 如果图片没有指定后缀, 依次按下列顺序搜索
\DeclareGraphicsExtensions{.pdf,.eps,.jpg,.png}
% 设置图表搜索路径, 可以给图表文件夹取如下名字
\graphicspath{{figures/}{figure/}{pictures/}%
	{picture/}{pic/}{pics/}{image/}{images/}}
% 图表标题
\DeclareCaptionFont{minusfive}{\songti\zihao{5}}
\captionsetup[figure]{%
	format=hang,   % 标题从第二行开始都有缩进, 应该和 justification=raggedright 的效果一样.
	labelsep=colon, % 分隔符是一个mao hao
	font={minusfive}, % 图的字体, 宋体5hao
	position=bottom % position=bottom, 不代表标题放在下面, 标题仍放在你放\caption的位置.
}
\captionsetup[table]{%
	format=hang,   % 标题从第二行开始都有缩进, 应该和 justification=raggedright 的效果一样.
	labelsep=colon, % 分隔符是一个空格
	font={minusfive}, % 表的字体, 宋体5hao
	position=top % position=bottom, 不代表标题放在下面, 标题仍放在你放\caption的位置.
}
\captionsetup[lstlisting]{%
	format=hang,   % 标题从第二行开始都有缩进, 应该和 justification=raggedright 的效果一样.
	labelsep=colon, % 分隔符是一个空格
	font={minusfive}, % 表的字体, 宋体5hao
	position=top % position=bottom, 不代表标题放在下面, 标题仍放在你放\caption的位置.
}
% 列表环境设置
\setlist{%
	topsep=0.3em, % 列表顶端的垂直空白
	partopsep=0pt, % 列表环境前面紧接着一个空白行时其顶端的额外垂直空白
	itemsep=0ex plus 0.1ex, % 列表项之间的额外垂直空白
	parsep=0pt, % 列表项内的段落之间的垂直空白
	leftmargin=2em, % 环境的左边界和列表之间的水平距离
	rightmargin=0em, % 环境的右边界和列表之间的水平距离
	labelsep=0.5em, % 包含标签的盒子与列表项的第一行文本之间的间隔
	labelwidth=2em % 包含标签的盒子的正常宽度；若实际宽度更宽，则使用实际宽度。
}


\lstnewenvironment{tcode}
  {
    \lstset{basicstyle = \small\ttfamily,
        language=TeX,
        tabsize = 4,
        frame = single,
        escapechar = `,
        breaklines = true,
        breakatwhitespace = true,
        frameround = tttt,
    }
  }
{}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%封面信息
\newcommand*\@SubjectName{}
\newcommand*\@CollegeName{}
\newcommand*\@Major{}
\newcommand*\@GroupNumber{}
\newcommand*\@StudentAnumber{}
\newcommand*\@StudentBnumber{}
\newcommand*\@StudentCnumber{}
\newcommand*\@StudentDnumber{}
\newcommand*\@StudentEnumber{}
\newcommand*\@StudentAname{}
\newcommand*\@StudentBname{}
\newcommand*\@StudentCname{}
\newcommand*\@StudentDname{}
\newcommand*\@StudentEname{}
\newcommand*\@StudentAwork{}
\newcommand*\@StudentBwork{}
\newcommand*\@StudentCwork{}
\newcommand*\@StudentDwork{}
\newcommand*\@StudentEwork{}


\newcommand{\makecover}{
	\begin{titlepage}
		\begin{figure}[t]
			\centering
			\includegraphics[width=13.41cm]{logo_zi.png}
		\end{figure}
	
	\begin{center}
		{ \heiti {\zihao{2}{数据结构课程设计报告}} }\\
		\LARGE \textbf{(2021-2022-2学期)}
	\end{center}

	\begin{figure}[H]
		\centering
		\includegraphics[width=3.81cm]{logo_tu.png}
	\end{figure}
	\begin{center}
	\begin{table}[!b]
		\centering
		\scalebox{1.7}{
	\begin{tabular}{|l|l|l|l|l|}
	\hline
	\multicolumn{1}{|c|}{题目} & \multicolumn{4}{c|}{\@SubjectName}                  \\ \hline
	\multicolumn{1}{|c|}{学院} & \multicolumn{4}{c|}{\@CollegeName}                         \\ \hline
	\multicolumn{1}{|c|}{专业} & \multicolumn{4}{c|}{\@Major}                     \\ \hline
	\multirow{6}{*}{组号}      & \multirow{6}{*}{\@GroupNumber} & 学号       & 姓名  & 分工       \\ \cline{3-5} 
				&                      & {\small \@StudentAnumber} &{\small \@StudentAname}&    {\small \@StudentAwork}      \\ \cline{3-5} 
				&                      & {\small \@StudentBnumber} &{\small \@StudentBname}&   {\small  \@StudentBwork }     \\ \cline{3-5} 
				&                      & {\small \@StudentCnumber} &{\small \@StudentCname}&    {\small \@StudentCwork  }    \\ \cline{3-5} 
				&                      & {\small \@StudentDnumber} &{\small \@StudentDname}&   {\small  \@StudentDwork }    \\ \cline{3-5} 
				&                      & {\small \@StudentEnumber} &{\small \@StudentEname}&    {\small \@StudentEwork }     \\ \hline
				\multicolumn{1}{|c|}{时间} & \multicolumn{4}{c|}{\today}      \\ \hline
				
	\end{tabular}
		}
	\end{table}
\end{center}  
\end{titlepage}
    \newpage
}


\newcommand{\SubjectName}[1]{\renewcommand{\@SubjectName}{#1}}
\newcommand{\CollegeName}[1]{\renewcommand{\@CollegeName}{#1}}
\newcommand{\Major}[1]{\renewcommand{\@Major}{#1}}
\newcommand{\GroupNumber}[1]{\renewcommand{\@GroupNumber}{#1}}
\newcommand{\StudentA}[3]{
	\renewcommand{\@StudentAnumber}{#1}
	\renewcommand{\@StudentAname}{#2}
	\renewcommand{\@StudentAwork}{#3}
}
\newcommand{\StudentB}[3]{
	\renewcommand{\@StudentBnumber}{#1}
	\renewcommand{\@StudentBname}{#2}
	\renewcommand{\@StudentBwork}{#3}
}
\newcommand{\StudentC}[3]{
	\renewcommand{\@StudentCnumber}{#1}
	\renewcommand{\@StudentCname}{#2}
	\renewcommand{\@StudentCwork}{#3}
}
\newcommand{\StudentD}[3]{
	\renewcommand{\@StudentDnumber}{#1}
	\renewcommand{\@StudentDname}{#2}
	\renewcommand{\@StudentDwork}{#3}
}
\newcommand{\StudentE}[3]{
	\renewcommand{\@StudentEnumber}{#1}
	\renewcommand{\@StudentEname}{#2}
	\renewcommand{\@StudentEwork}{#3}
}





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% 目录深度
\setcounter{secnumdepth}{3}
\renewcommand\thesubsection{\arabic{section}\thinspace.\thinspace\arabic{subsection}}
\renewcommand\thesubsubsection{\thesubsection\thinspace.\thinspace\arabic{subsubsection}}

\titleformat{\section}
{\centering\zihao{3}\heiti}{\arabic{section}.}{.5em}{}
\titleformat{\subsection}
{\zihao{-3}\heiti}{\thesubsection}{.5em}{}
\titleformat{\subsubsection}
{\zihao{4}\heiti}{\zihao{-4}\heiti\textrm{\thesubsubsection}}{.5em}{}
\titleformat{\paragraph}[runin]
{\normalfont\normalsize\bfseries}{\theparagraph}{.5em}{}
\titlespacing*{\chapter} {0pt}{50pt}{40pt}
\titlespacing*{\section} {0pt}{3.5ex plus 1ex minus .2ex}{2.3ex plus .2ex}
\titlespacing*{\subsection} {0pt}{3.25ex plus 1ex minus .2ex}{1.5ex plus .2ex}
\titlespacing*{\subsubsection}{0pt}{3.25ex plus 1ex minus .2ex}{1.5ex plus .2ex}
\titlespacing*{\paragraph} {0pt}{3.25ex plus 1ex minus .2ex}{1em}
\titlespacing*{\subparagraph} {\parindent}{3.25ex plus 1ex minus .2ex}{1em}
%设置目录格式
% 节的目录格式
 \titlecontents{section}[0pt]{\songti \zihao{4}}
 {{\thecontentslabel}.\enspace }{}{\titlerule*[0.5pc]{.}\contentspage}
 % 小节的目录格式
 \titlecontents{subsection}[13pt]{\songti \zihao{-4}}
 {\thecontentslabel\hskip.5em}{}{\titlerule*[0.5pc]{.}\contentspage}
 \titlecontents{subsubsection}[35pt]{\songti \zihao{-4}}
 {{\normalfont\textrm{\thecontentslabel}}\hskip.5em}{}{\titlerule*[0.5pc]{.}\normalfont\textrm{\contentspage}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\endinput