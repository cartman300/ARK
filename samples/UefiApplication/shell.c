#include "ark.h"

static const EFI_SYSTEM_TABLE* SysTab;
static UINTN Columns;
static UINTN Rows;

void InitializeConsole(const EFI_SYSTEM_TABLE* SystemTable) {
	UINTN BiggestMode = 0;
	for (UINTN i = 0; i < 20; i++)
		if (SystemTable->ConOut->QueryMode(SystemTable->ConOut, i, &Columns, &Rows) == EFI_SUCCESS)
			BiggestMode = i;
	SystemTable->ConOut->SetMode(SystemTable->ConOut, BiggestMode);
	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void shell_init(const EFI_SYSTEM_TABLE* ST) {
	SysTab = ST;
	InitializeConsole(ST);
	shell_write(L"Running ARK x64\n\n\r");
}

void shell_read(CHAR16* Buffer, size_t Len) {

}

void shell_write(CHAR16* Str) {
	SysTab->ConOut->OutputString(SysTab->ConOut, Str);
}