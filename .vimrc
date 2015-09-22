color torte
syn on
set guifont=Consolas:h16:
set number
set showcmd

" use indentation of previous line
set autoindent
" use intelligent indentation for C
set smartindent
" configure tabwidth and insert spaces instead of tabs
set tabstop=4        " tab width is 4 spaces
set expandtab        " expand tabs to spaces
set showmatch
" intelligent comments
set comments=sl:/*,mb:\ *,elx:\ */
set backspace=indent,eol,start
set softtabstop=4
set shiftwidth=4

map <F9> <ESC>:w<CR>:!g++ % -o %< -O2 -std=c++0x<CR>
map <S-F9> <ESC>:w<CR>:!g++ % -o %< -O2 -D_DEBUG_ -std=c++0x<CR>
map <F5> <ESC>:!./%<<CR>
map <F6> <ESC>:w<CR>ggvG"+y
map <S-F5> <ESC>:!./%< < %<.in<CR>
imap <Home> <ESC>^i
com INPUT sp %<.in
