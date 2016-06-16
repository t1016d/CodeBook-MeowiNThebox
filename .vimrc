color torte
syn on
set guifont=Consolas:h16: nu sc ai si ts=4 sm sts=4 sw=4

map <F9> <ESC>:w<CR>:!g++ % -o %< -O2 -Wall -Wno-unused-result -std=c++0x<CR>
map <S-F9> <ESC>:w<CR>:!g++ % -o %< -O2 -Wall -Wno-unused-result -D_DEBUG_ -std=c++0x<CR>
map <F5> <ESC>:!./%<<CR>
map <F6> <ESC>:w<CR>ggVG"+y
map <S-F5> <ESC>:!./%< < %<.in<CR>
imap <Home> <ESC>^i
com INPUT sp %<.in
