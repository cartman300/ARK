#pragma once
#include "ark.h"

typedef void(*SHELL_COMMAND)(const EFI_SYSTEM_TABLE* SysTab, CHAR16* In);

void shell_init(const EFI_SYSTEM_TABLE* SysTab);
BOOLEAN shell_eq(CHAR16* A, CHAR16* B);
void shell_register(CHAR16* Name, CHAR16* Help, SHELL_COMMAND Fnc);
void shell_exec(CHAR16* Command);

EFI_STATUS shell_read(CHAR16* Buffer, size_t Length);
void shell_write(CHAR16* Str);
void shell_writef(CHAR16* Fmt, ...);
