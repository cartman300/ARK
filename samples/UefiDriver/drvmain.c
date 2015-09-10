#include "drv.h"

const UINT8 _gDriverUnloadImageCount = 1;

const UINT32 _gUefiDriverRevision = 0x200;
const UINT32 _gDxeRevision = 0x200;

EFI_STATUS EFIAPI UefiUnload(IN EFI_HANDLE ImageHandle) {
	return EFI_ACCESS_DENIED;
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
	return EfiLibInstallDriverBindingComponentName2(ImageHandle, SystemTable, &gDriverBindingProtocol,
		ImageHandle, &gComponentNameProtocol, &gComponentName2Protocol);
}