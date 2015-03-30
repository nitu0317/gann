% ib-assignment.cls
% Copyright 2009 Ankur Dave <ankurdave@gmail.com>
% 
% Licensed under the CC-GNU GPL version 2.0 or later.
% See http://creativecommons.org/licenses/GPL/2.0
% 
% See http://ankurdave.com/tex for more document classes.

\ProvidesClass{ib-assignment}

\LoadClass[12pt]{article}

% fields that user can set (in addition to title, author, etc)
\makeatletter
	\newcommand{\candidatenum}[1]{\def \@candidatenum {#1}}
	\newcommand{\subtitle}[1]{\def \@subtitle {#1}}
	\newcommand{\subject}[1]{\def \@subject {#1}}
	\newcommand{\wordcount}[1]{\def \@wordcount {#1}}
    \newcommand{\setabcount}[1]{\def \@setabcount {#1}}
	\newcommand{\email}[1]{\def \@email {#1}}
    \newcommand{\advisor}[1]{\def \@advisor {#1}}
	\candidatenum{}
	\subtitle{}
	\subject{}
	\wordcount{}
	\email{}
    \advisor{}
    \setabcount{}
    
\makeatother

% margins
\usepackage[top=1in,bottom=1in,left=1in,right=1in]{geometry}

% fonts
\usepackage{newcent}
\usepackage{fouriernc}
\renewcommand{\ttdefault}{cmtt}
\usepackage{bm}

% alignment
% (must be before indentation because raggedright clears parindent)
\raggedright

% indentation
\usepackage{indentfirst}
\setlength{\parindent}{18pt}
\setlength{\parskip}{3pt}

% spacing
\usepackage{setspace}
\doublespacing

% references
\usepackage{varioref}

% figures
\usepackage[pdftex]{graphicx}


% page headings and numbering
\makeatletter
	\usepackage{fancyhdr}
	\pagestyle{fancy}
	\renewcommand{\footrulewidth}{\headrulewidth}
	\fancyhf{}

	\newcommand{\updateheaders}{
		\ifx \@candidatenum \@empty
			\relax
		\else
			\fancyfoot[R]{Candidate \#\@candidatenum}
		\fi
		
		\ifx \@author \@empty
			\relax
		\else
			\fancyfoot[L]{\@author}
		\fi

		\ifx \@subtitle \@empty
			\fancyhead[L]{\@title}
		\else
			\fancyhead[L]{\@title: \@subtitle}
		\fi
	}

	\fancyhead[R]{\thepage}
\makeatother

\makeatletter
	\newcommand{\abcount}
    {
    	\ifx \@setabcount \@empty
        	\relax
         \else
         	\vspace{0.5in}
            \hfill Word Count: \@setabcount \\
         \fi
    }
\makeatother

% title
\makeatletter
\def \maketitle {%
	\begin{titlepage}
		~\vfill
		\begin{center}
			{\Large \@title} \\
			\ifx \@subtitle \@empty
				\relax
			\else
				\vspace{0.5em}
				{\large \@subtitle} \\
			\fi
		
			\vspace{0.5in}
		\end{center}
		
		\vfill
			\ifx @author \@empty
				\relax
                			\hfill \@date
			\else
				\hfill \@author \\
				\ifx \@candidatenum \@empty
					\relax
				\else
					\hfill Candidate \#\@candidatenum \\
				\fi
                \hfill \@date \\
                \ifx\@subject \@empty
					\relax
				\else
					\hfill \@subject \\
				\fi
                
                \ifx\@advisor \@empty
					\relax
				\else
					\hfill \@advisor \\
				\fi
			\fi
		
			\ifx \@wordcount \@empty
				\relax
			\else
				\hfill Word Count: \@wordcount \\
			\fi
				


	\end{titlepage}
}
\makeatother