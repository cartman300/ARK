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

void shellcmd_shutdown(const EFI_SYSTEM_TABLE* SysTab, CHAR16* In) {
	SysTab->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
}

void shellcmd_info(const EFI_SYSTEM_TABLE* SysTab, CHAR16* In) {
	shell_writef(L"Vendor: %s\r\nRevision: %d\r\n", SysTab->FirmwareVendor, SysTab->FirmwareRevision);
	//EFI_SMM_SYSTEM_TABLE2* SMM = (EFI_SMM_SYSTEM_TABLE2*)LocateProtocol(SysTab, NULL);
	shell_writef(L"CPU count: %d\r\n", /*SMM->NumberOfCpus*/ -1);
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable) {
	shell_init(SystemTable);
	shell_register(L"shutdown", L"Shuts down the system", shellcmd_shutdown);
	shell_register(L"info", L"Displays system information", shellcmd_info);

	CHAR16 Buf[80];
	BOOLEAN Running = TRUE;
	while (Running) {
		shell_write(L"> ");
		shell_read(Buf, 80);
		shell_exec(Buf);
	}
	
	DisableInterrupts();
	__halt();
	return EFI_SUCCESS;
}