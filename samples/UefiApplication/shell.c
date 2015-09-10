#include "ark.h"

static const EFI_SYSTEM_TABLE* SysTab;
static UINTN Columns;
static UINTN Rows;

static rsize_t CmdCount;
static SHELL_COMMAND Commands[512];
static CHAR16* CommandNames[512];
static CHAR16* HelpTexts[512];

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
	CmdCount = 0;
	InitializeConsole(ST);
	shell_write(L"Running ARK x64\n\n\r");
}

BOOLEAN shell_eq(CHAR16* A, CHAR16* B) {
	while (*A != 0 || *B != 0) {
		if (*A != *B)
			return FALSE;
		A++;
		B++;
	}
	return TRUE;
}

void shell_register(CHAR16* Name, CHAR16* Help, SHELL_COMMAND Fnc) {
	Commands[CmdCount] = Fnc;
	CommandNames[CmdCount] = Name;
	HelpTexts[CmdCount] = Help;
	CmdCount++;
}

void shell_exec(CHAR16* Command) {
	if (shell_eq(Command, L"help")) {
		for (size_t i = 0; i < CmdCount; i++)
			shell_writef(L"%s - %s\r\n", CommandNames[i], HelpTexts[i]);
	} else {
		for (size_t i = 0; i < CmdCount; i++)
			if (shell_eq(Command, CommandNames[i])) {
				Commands[i](SysTab, Command);
				return;
			}
		shell_writef(L"Invalid command: '%s'\r\n", Command);
	}
}

EFI_STATUS shell_read(CHAR16* Buffer, size_t Length) {
	EFI_INPUT_KEY Key;
	EFI_STATUS Stat;
	UINTN                           Len = 0;

	for (;;) {
		WaitForSingleEvent(SysTab, SysTab->ConIn->WaitForKey);

		Stat = SysTab->ConIn->ReadKeyStroke(SysTab->ConIn, &Key);
		if (EFI_ERROR(Stat))
			return Stat;

		if (Key.UnicodeChar == '\n' || Key.UnicodeChar == '\r') {
			shell_write(L"\r\n");
			break;
		}

		if (Key.UnicodeChar == '\b') {
			if (Len) {
				shell_write(L"\b \b");
				Len -= 1;
			}
			continue;
		}

		if (Key.UnicodeChar >= ' ') {
			if (Len < Length - 1) {
				Buffer[Len] = Key.UnicodeChar;
				Buffer[Len + 1] = 0;
				shell_write(&Buffer[Len]);
				Len += 1;
			}
			continue;
		}
	}

	Buffer[Len] = 0;
	return EFI_SUCCESS;
}

void shell_write(CHAR16* Str) {
	SysTab->ConOut->OutputString(SysTab->ConOut, Str);
}

void shell_writef(CHAR16* Fmt, ...) {
	VA_LIST Lst;
	VA_START(Lst, Fmt);
	CHAR16* Str = CatVSPrint(L"", Fmt, Lst);
	VA_END(Lst);
	shell_write(Str);
	FreePool(Str);
}