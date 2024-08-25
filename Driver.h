#ifndef DRIVER_H
#define DRIVER_H

#include <ntddk.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);
VOID UnloadDriver(PDRIVER_OBJECT DriverObject);
void BypassCR3(void);
NTSTATUS ManipulateFileAttributes(PUNICODE_STRING FileName);

#endif
