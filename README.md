# ManipulateFileAttributes
A Driver to Manipulate DiskFile Attributes such as CreationTime, LastAccessTime, LastWriteTime, ChangeTime using a runtime driver.
```cpp
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
```
Tbh I have no clue what the use-case for this would be but I thought it would be a cool release.
