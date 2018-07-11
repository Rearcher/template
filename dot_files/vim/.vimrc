set nocompatible              " be iMproved, required
filetype off                  " required
set shell=/bin/bash

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
" Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
" Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
" Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
" Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line


" about search
set ignorecase
set smartcase
set hlsearch
set incsearch

set background=dark
syntax enable

set t_Co=256
colorscheme molokai

" No annoying sound
set noerrorbells
set novisualbell

" encoding,filetype
set encoding=utf8
set ffs=unix,dos,mac

" files,backups,undo
set nobackup
set nowb
set noswapfile

" about tab
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
set backspace=indent,eol,start

" linebreak on 500 characters
set lbr
set tw=500
set number
set ai "Auto indent
set si "Smart indent
set wrap "Wrap lines

" shortcuts
map <F5> :call Compile()<CR>
map <F6> :call Debug() <CR>
map <F2> :call ToHex() <CR>
map <F3> :call RecoverFromHex() <CR>

func! Compile()
	if &filetype == "cpp"
		exec "w"
		exec "!g++ -std=c++14 -lpthread -g -Wall % -o %<"
		exec "! ./%<"
	elseif &filetype == "javascript"
		exec "w"
		exec "!node --harmony --use_strict %"
	elseif &filetype == "c"
		exec "w"
		exec "!gcc -g -Wall % -o %<"
		exec "! ./%<"
	elseif &filetype == "sh"
		exec "w"
		exec "!bash %"
	endif
endfunc
" %<
func! Debug() 
	if &filetype == "cpp"
		exec "!g++ -std=c++14 -lpthread -g -Wall % -o %<"
		exec "!cgdb %<"
	elseif &filetype == "c"
		exec "!gcc -g -Wall % -o %<"
		exec "! ./%<"
	endif
endfunc

func! ToHex()
	exec "%!xxd"
endfunc

func! RecoverFromHex()
	exec "%!xxd -r"
endfunc
