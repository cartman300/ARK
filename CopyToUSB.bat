@echo off
if exist G:\EFI\ rd /S /Q G:\EFI\
xcopy /E image\efi G:\EFI\
pause