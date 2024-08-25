#include "Driver.h"

void BypassCR3() {
    // Dont fucking use this, this isnt my code and it wont work
    ULONG_PTR originalCR3 = __readcr3();
    ULONG_PTR newCR3 = originalCR3;
    __writecr3(newCR3);


    __writecr3(originalCR3);
}

NTSTATUS ManipulateFileAttributes(PUNICODE_STRING FileName) {
    OBJECT_ATTRIBUTES objAttr;
    HANDLE fileHandle;
    IO_STATUS_BLOCK ioStatusBlock;
    FILE_BASIC_INFORMATION fileInfo;

    InitializeObjectAttributes(&objAttr, FileName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

    NTSTATUS status = ZwCreateFile(&fileHandle, FILE_WRITE_ATTRIBUTES, &objAttr, &ioStatusBlock, NULL, 0,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, FILE_OPEN, 0, NULL, 0);

    if (NT_SUCCESS(status)) {
        fileInfo.CreationTime.QuadPart = 0x01C7D0B360D80000;
        fileInfo.LastAccessTime.QuadPart = 0x01C7D0B360D80000;
        fileInfo.LastWriteTime.QuadPart = 0x01C7D0B360D80000;
        fileInfo.ChangeTime.QuadPart = 0x01C7D0B360D80000;

        status = ZwSetInformationFile(fileHandle, &ioStatusBlock, &fileInfo, sizeof(fileInfo), FileBasicInformation);
        ZwClose(fileHandle);
    }

    return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = UnloadDriver;

    DbgPrint("FileImmutabilityDriver geladen.\n");

    BypassCR3();
    ManipulateFileAttributes("cz.exe");

    return STATUS_SUCCESS;
}

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("FileImmutabilityDriver unloading.\n");
}
