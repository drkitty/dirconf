set nocompatible

if exists("g:did_vimrc")
    finish
endif
let g:did_vimrc = 1

set runtimepath=~/.vim,/usr/share/vim/vim74  " or whatever you want
if exists("localrtp")
    let &runtimepath .= ',' . localrtp
endif


"
" DON'T EDIT ANYTHING ABOVE THIS POINT
"
