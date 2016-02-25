
nnoremap <F4> :make!<cr>
nnoremap <F5> :!./build/space-gun<cr>
nnoremap <F6> :cwindow!<cr>
let g:syntastic_cpp_compiler_options = '-Wall -g -std=c++11 -lpthread -L/user/lib -lSDL2'
let g:syntastic_cpp_include_dirs = ['/usr/lib/libgtest_main.a', '/usr/lib/libgtest.a', '/usr/lib/libgmock_main.a', '/usr/lib/libgmock.a']
let g:syntastic_cpp_compiler = 'clang++'
let g:syntastic_cpp_compiler_options = ' -std=c++11 -stdlib=libc++'

let g:syntastic_quiet_messages = {
    \ "!level":  "errors",
    \ "type":    "syntax",
    \ "regex":   '\m\[C03\d\d\]',
    \ "file:p":  ['\m^/usr/include/', '\m\c\.h$'] }
