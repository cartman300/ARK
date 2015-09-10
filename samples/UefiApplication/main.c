#include "ark.h"

extern CONST UINT32 _gUefiDriverRevision = 0;

EFI_STATUS EFIAPI UefiUnload(IN EFI_HANDLE ImageHandle) {
	ASSERT(FALSE);
}

void Crash(const CHAR16* Msg, EFI_STATUS S) {
	Print(L"ERROR: %s; %r\r\n", Msg, S);
	DisableInterrupts();
	__halt();
}

void* LocateProtocol(IN EFI_SYSTEM_TABLE* ST, IN EFI_GUID* GUID) {
	void* Ret;
	EFI_STATUS S = ST->BootServices->LocateProtocol(GUID, NULL, &Ret);
	if (EFI_ERROR(S))
		Crash(L"Cannot locate protocol", S);
	return Ret;
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable) {
	shell_init(SystemTable);
	BOOLEAN Running = TRUE;

	CHAR16 Buf[80];
	while (Running) {
		shell_write(L"> ");
		shell_read(Buf, 80);
		shell_write(L"You wrote: ");
		shell_write(Buf);

		
	}

	DisableInterrupts();
	__halt();
	SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
	return EFI_SUCCESS;
}