inoremap { {}<Left>
inoremap {<CR> {<CR>}<Esc>O
inoremap {{ {
inoremap {} {}

autocmd filetype cpp nnoremap <F9> :w <bar> !g++ -std=c++14 % -o %:r -Wl,--stack,268435456<CR>
autocmd filetype cpp nnoremap <F10> :!%:r<CR>
autocmd filetype python nnoremap <F10> :w <bar> !py %<CR>
nnoremap <C-n> :NERDTree<CR>

set guifont=JetBrains_Mono:h18:cRUSSIAN:qDRAFT
set ts=4
set sw=4
set smarttab
set expandtab
set number
set backspace=indent,eol,start

call plug#begin('~/.vim/plugged')

Plug 'morhetz/gruvbox'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'scrooloose/nerdtree'

call plug#end()
colorscheme gruvbox
set background=dark
