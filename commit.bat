@echo off
git status
set /p commit="Commit message: "
git add -A && git commit -am "%commit%" && git push