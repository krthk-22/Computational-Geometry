\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{Assignment}[2024/08/03 v1.0 Algorithms in Computational Geometry]

\LoadClass[12pt]{article}

\RequirePackage{amsmath,amsthm,amssymb}
\RequirePackage{geometry,enumerate,xcolor,multicol}
\RequirePackage{graphicx}
\RequirePackage{fancyhdr}
\RequirePackage{color,soul}
\RequirePackage{tikz}
\RequirePackage{hyperref, etoolbox}
\RequirePackage[backend=biber,style=numeric, sorting=none]{biblatex}
\hypersetup{
    colorlinks=true,
    linkcolor=blue,
    urlcolor=blue,
    citecolor=blue    
}
\geometry{
    a4paper,
    total={170mm,257mm},
    left=10mm,
    right=10mm,
    top=20mm,
}

% Define a command for the problem set number
\newcommand{\assignmentnumber}{}
\newcommand{\setassignmentnumber}[1]{\renewcommand{\assignmentnumber}{#1}}
\newcommand{\Startdate}{}
\newcommand{\setstartdate}[1]{\renewcommand{\Startdate}{#1}}
\newcommand{\Enddate}{}
\newcommand{\setenddate}[1]{\renewcommand{\Enddate}{#1}}


% Initialize the topics list
\newcommand{\topicslist}{}

% Define a command to add a topic to the list
\newcommand{\addtopic}[1]{\g@addto@macro\topicslist{\item #1}}

% Define a command to print the list of topics
\newcommand{\printtopics}{
    \begin{itemize}
        \topicslist
    \end{itemize}
}

% Define a command for the authors
\newcommand{\authorslist}{}

% Define a command to add an author to the list
\newcommand{\addauthor}[1]{\g@addto@macro\authorslist{\item #1}}

% Define a command to print the list of authors
\newcommand{\printauthors}{
    \begin{itemize}
        \authorslist
    \end{itemize}
}

% Command to print topics and authors
\newcommand{\printtopicsandauthors}{
    \begin{multicols}{2}
    \begin{itemize}
        \item {\bf Topics focused: }\\
        \begin{minipage}[t]{\textwidth}
            \printtopics
        \end{minipage}
        \item {\bf Solved by: }\\
        \begin{minipage}[t]{\textwidth}
            \printauthors
        \end{minipage}
    \end{itemize}
    \end{multicols}
}

% Custom title page
\newcommand{\maketitlepage}{
    \begin{center}
    \vspace{-1cm}
    {\Large {\bf Algorithms in Computational Geometry}}\\
    \bigskip
    {\Large {\bf Assignment - \assignmentnumber}}
    \bigskip
    \hrule
    \bigskip
    {\bf Assignment posed on: \Startdate} \hfill {\bf Assignment submitted by: \Enddate}
    \bigskip
    \hrule
    \end{center}
}

\pagestyle{fancy}
\fancyhf{}
\fancyhead[R]{Assignment-\assignmentnumber}
\fancyhead[L]{Algorithms in Computational Geometry}
\fancyfoot[C]{\thepage}
\renewcommand{\headrulewidth}{1pt}
\renewcommand{\footrulewidth}{1pt}

% Define the problem environment
\newenvironment{problem}[1][Problem]{%
    \begin{trivlist}
    \item[\hskip \labelsep {\bfseries #1}\hskip \labelsep]}{%
    \end{trivlist}}

\endinput
