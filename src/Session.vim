let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Dev/ComputationalPhysics/cosmos/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +131 auFontRendering.cpp
badd +16 auCharacter.h
badd +26 auFontRendering.h
badd +38 ~/Dev/ComputationalPhysics/cosmos/src/main.cpp
badd +23 auCharacter.cpp
badd +1 health://
argglobal
%argdel
edit auFontRendering.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 109 + 115) / 231)
exe '2resize ' . ((&lines * 26 + 27) / 54)
exe 'vert 2resize ' . ((&columns * 121 + 115) / 231)
exe '3resize ' . ((&lines * 25 + 27) / 54)
exe 'vert 3resize ' . ((&columns * 121 + 115) / 231)
argglobal
balt auCharacter.h
setlocal foldmethod=expr
setlocal foldexpr=v:lua.require'astroui.folding'.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 64 - ((24 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 64
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("auCharacter.cpp", ":p")) | buffer auCharacter.cpp | else | edit auCharacter.cpp | endif
if &buftype ==# 'terminal'
  silent file auCharacter.cpp
endif
balt auCharacter.h
setlocal foldmethod=expr
setlocal foldexpr=v:lua.require'astroui.folding'.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
5
sil! normal! zo
12
sil! normal! zo
20
sil! normal! zo
20
sil! normal! zo
22
sil! normal! zo
let s:l = 33 - ((21 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 025|
wincmd w
argglobal
if bufexists(fnamemodify("auFontRendering.cpp", ":p")) | buffer auFontRendering.cpp | else | edit auFontRendering.cpp | endif
if &buftype ==# 'terminal'
  silent file auFontRendering.cpp
endif
balt ~/Dev/ComputationalPhysics/cosmos/src/main.cpp
setlocal foldmethod=expr
setlocal foldexpr=v:lua.require'astroui.folding'.foldexpr()
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=99
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 75 - ((22 * winheight(0) + 12) / 24)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 75
normal! 0
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 109 + 115) / 231)
exe '2resize ' . ((&lines * 26 + 27) / 54)
exe 'vert 2resize ' . ((&columns * 121 + 115) / 231)
exe '3resize ' . ((&lines * 25 + 27) / 54)
exe 'vert 3resize ' . ((&columns * 121 + 115) / 231)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
