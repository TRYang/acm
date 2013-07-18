syntax enable
syntax on
filetype plugin indent on
set wildmenu
set helplang=cn
set cin
set sw=4
set sta
set number
set history=1000
set autoindent
set smartindent
set tabstop=2
set shiftwidth=2
set expandtab
set showmatch
set ruler
set background=dark
set nohlsearch
set cursorline
set mouse=a

map<F2> ggVG:!xclip -sel clip<CR>u
vmap<F2> :!xclip -sel clip<CR>u
""map<F2> ggVG"+y
map<F3> :s!^!#!<CR>
map<F4> :s!^#!!<CR>
au FileType cpp,c,java map <buffer> <F3> :s!^!//!<CR>
au FileType cpp,c,java map <buffer> <F4> :s!^//!!<CR>

map<C-h> gT
map<C-l> gt
map<F9> :make<CR>

au FileType asm set ft=ia64

au FileType c setlocal mp=gcc\ %\ -std=gnu99
au FileType c map <buffer> <C-F5> :!./a.out<CR>

au FileType cpp setlocal mp=g++\ %\ -std=gnu++0x
au FileType cpp map <buffer> <F5> :!./a.out<CR>
au FileType cpp map <buffer> <C-F5> :!./a.out < test.in<CR>

au FileType java setlocal mp=javac\ %
au FileType java map <buffer> <F5> :!java %:r<CR>
au FileType java map <buffer> <C-F5> :!java %:r < test.in<CR>

au FileType python setlocal mp=python\ %
au FileType python map <buffer> <C-F5> :!python %<CR>

au FileType tex setlocal mp=xelatex\ %
au FileType tex map <buffer> <C-F5> :!evince %:r.pdf<CR>

au FileType pascal setlocal mp=fpc\ %
au FileType pascal map <buffer> <C-F5> :!./%:r<CR>
