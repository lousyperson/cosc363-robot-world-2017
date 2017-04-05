@echo off
set /p commit="Commit message: "
git add -A && git commit -am "%commit%" && git push