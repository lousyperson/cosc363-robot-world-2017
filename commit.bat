@echo off
git log -2 --oneline
echo.
git status
echo.
set /p commit="Commit message: "
git add -A && git commit -am "%commit%" && git push