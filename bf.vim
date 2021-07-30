" Vim Syntax File
" Language: Brainfuck Extended
" Maintainer: Gaultier Delbarre
if exists("b:current_syntax")
	finish
endif


let b:current_syntax = "bf"

" Syntax to match
" Comments
syntax region BFComment start="/\*" end="\*/"
syntax region BFComment start="//" end="\n"

" Statements
syntax match BFStatement "[+-,.]"

" Positioners
syntax match BFPosition "[<>^~|]"

" Constants
syntax match BFConstant "\[-\]"

" Todos and Includes
syntax region BFInclude start="@" end="@"
syntax match BFInclude "!"
syntax match BFInclude ".*\(todo\|TODO\|Todo\).*"
syntax match BFInclude "\({\|}\)"

" Highlighting Types
highlight link BFStatement Keyword
highlight link BFComment Comment
highlight link BFInclude Todo
highlight link BFConstant Constant
highlight link BFPosition PreProc
