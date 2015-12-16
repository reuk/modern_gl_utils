#!/bin/zsh
setopt extended_glob
ls ./*.(h|cpp) | xargs clang-format -i
