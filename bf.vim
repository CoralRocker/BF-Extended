" Vim Syntax File
" Language: Brainfuck Extended
" Maintainer: Gaultier Delbarre
if exists("b:current_syntax")
	finish
endif


let b:current_syntax = "bf"
syntax region BFComment start="/\*" end="\*/"
syntax match BFStatement "[+-,.<>]"
syntax region BFInclude start="@" end="@"
syntax match BFInclude "!"
highlight link BFStatement Keyword
highlight link BFComment Comment
highlight link BFInclude Todo
