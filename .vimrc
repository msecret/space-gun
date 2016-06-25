
nnoremap <F4> :make!<cr>
nnoremap <F5> :!./build/space-gun<cr>
nnoremap <F6> :cwindow!<cr>

let g:syntastic_cpp_compiler_options = '-std=c++11'
let g:syntastic_cpp_include_dirs = ['/usr/lib', '/usr/local/lib']

let g:syntastic_cpp_check_header = 1
let g:syntastic_cpp_auto_refresh_includes = 1
