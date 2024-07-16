// HWID Library

native cpuid(int, &int, &int, &int, &int);
native GetVolumeInformation(const string[], const string[], &int, &int, &int, &string);
native GetSystemFirmwareTable(int, int, &int, &string);

// CPU ID
GetCPUID() {
    new eax, ebx, ecx, edx;
    cpuid(1, eax, ebx, ecx, edx);
    new cpuId[32];
    format(cpuId, sizeof(cpuId), "%x%x%x%x", eax, ebx, ecx, edx);
    return cpuId;
}

// Disk Serial Number
GetDiskSerialNumber() {
    new serialNumber[16];
    GetVolumeInformation("C:\\", "", 0, 0, 0, serialNumber, sizeof(serialNumber));
    return serialNumber;
}

// Motherboard ID
GetMotherboardID() {
    new firmwareTable[1024];
    new firmwareTableSize = 1024;
    GetSystemFirmwareTable(0x00000000, firmwareTableSize, firmwareTable);
    new motherboardId[32];
    for (new i = 0; i < firmwareTableSize; i += 16) {
        if (firmwareTable[i] == 0x01 && firmwareTable[i + 1] == 0x04) {
            format(motherboardId, sizeof(motherboardId), "%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x",
                firmwareTable[i + 2], firmwareTable[i + 3], firmwareTable[i + 4], firmwareTable[i + 5],
                firmwareTable[i + 6], firmwareTable[i + 7], firmwareTable[i + 8], firmwareTable[i + 9],
                firmwareTable[i + 10], firmwareTable[i + 11], firmwareTable[i + 12], firmwareTable[i + 13],
                firmwareTable[i + 14], firmwareTable[i + 15]);
            return motherboardId;
        }
    }
    return "";
}

// HWID Function
GetHWID() {
    new hwid[128];
    format(hwid, sizeof(hwid), "%s-%s-%s", GetCPUID(), GetDiskSerialNumber(), GetMotherboardID());
    return hwid;
}