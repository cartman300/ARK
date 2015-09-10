#pragma once
#include "ark.h"

void shell_init(const EFI_SYSTEM_TABLE* SysTab);
void shell_read(CHAR16* Buffer, size_t Len);
void shell_write(CHAR16* Str);