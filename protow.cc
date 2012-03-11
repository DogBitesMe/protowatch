#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "protow.h"

//#define EASYINJECTION
#define TEXTFILE_OUTPUT
	
int tlsIndex;


int __stdcall func2() {
	if (TlsGetValue(tlsIndex) == 0) {
		TlsSetValue(tlsIndex, (void*)((int)TlsGetValue(tlsIndex) + 1));
		return 1;
	}
	return 0;
}

void __stdcall func3() {
	TlsSetValue(tlsIndex, (void*)((int)TlsGetValue(tlsIndex) - 1));
}


//unsigned int D3__std__String = 0x3CE4A528;
unsigned int D3__std__String_delete = 0; 
unsigned int D3__TextFormat__PrintToString = 0;
unsigned int D3__Descriptor__full_name = 0;
unsigned int D3__Message__GetDescriptor = 0;

unsigned int recvheader_entry = 0;
unsigned int recvheader_return = 0;
unsigned int sendheader_entry = 0;
unsigned int sendheader_return = 0;
unsigned int send_message_entry = 0;
unsigned int send_message_return = 0;
unsigned int send_message_entry1 = 0;
unsigned int send_message_return1 = 0;
unsigned int send_message_entry2 = 0;
unsigned int send_message_return2 = 0;
unsigned int message_parse_hook = 0;
unsigned int message_parse_return = 0;
unsigned int deserialize_message = 0;

#define REBASE(lib, var, addr, oldbase) var = lib + addr - oldbase;

/* 0.3
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
	REBASE(bnetlib, D3__std__String, 0x3CE4B234, 0x3C910000)
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB4E280, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CAEB630, 0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3C9E0220, 0x3C910000)
	REBASE(bnetlib, hook_return, 0x3CAD8894, 0x3C910000)

//.text:3CD1D094                 mov     edx, [ecx]
//.text:3CD1D096                 mov     edx, [edx+28h]
//.text:3CD1D099                 lea     eax, [edi+ebx]
//.text:3CD1D09C                 push    eax
//.text:3CD1D09D                 call    edx
	REBASE(bnetlib, outputhook_return, 0x3CD1C1D4, 0x3C910000)

	REBASE(bnetlib, outputhead_return, 0x3CD03639, 0x3C910000)
	REBASE(bnetliv, outputhead, 0x3CD1D094, 0x3C910000)
	REBASE(bnetliv, message_parse_hook, 0x3CAD955C, 0x3C910000)
	 0x3CD0362C // recv header
}
*/

/* 0.3.4774
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	REBASE(bnetlib, D3__std__String_delete, 0x3CE4B550, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB4EF60, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CAEC320, 0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3C9AD830, 0x3C910000)
	REBASE(bnetlib, message_parse_hook, 0x3CAD955C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CAD9564, 0x3C910000)
	
//.text:3CD045BC                 mov     cl, [ebp-2C4h]
//.text:3CD045C2                 movzx   ebx, word ptr [ebp-2BCh]
//.text:3CD045C9                 cmp     cl, 0FEh

	REBASE(bnetlib, recvheader_entry, 0x3CD045BC, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CD045C9, 0x3C910000)

//.text:3CD1D094                 mov     edx, [ecx]
//.text:3CD1D096                 mov     edx, [edx+28h]
//.text:3CD1D099                 lea     eax, [edi+ebx]
//.text:3CD1D09C                 push    eax

	REBASE(bnetlib, send_message_entry, 0x3CD1D094, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD1D09C, 0x3C910000)
}
*/

/* v 0.3.7728
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	REBASE(bnetlib, D3__std__String_delete, 0x3CE84610, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CBF31A0, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB90900,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB8D7A0, 0x3C910000) 
	
//.text:3CB7DB3C                 mov     edx, [eax+10h]
//.text:3CB7DB3F                 call    edx
//.text:3CB7DB41                 movzx   eax, al

	REBASE(bnetlib, message_parse_hook, 0x3CB7DB3C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CB7DB44, 0x3C910000)
	
//.text:3CD045BC                 mov     cl, [ebp-2C4h]
//.text:3CD045C2                 movzx   ebx, word ptr [ebp-2BCh]
//.text:3CD045C9                 cmp     cl, 0FEh

//.text:3CD354CE                 mov     cl, [ebp-2FCh]
//.text:3CD354D4                 movzx   ebx, word ptr [ebp-2F4h]
//.text:3CD354DB                 cmp     cl, 0FEh


	REBASE(bnetlib, recvheader_entry, 0x3CD354CE, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CD354DB, 0x3C910000)

		
//.text:3CD1D094                 mov     edx, [ecx]
//.text:3CD1D096                 mov     edx, [edx+28h]
//.text:3CD1D099                 lea     eax, [edi+ebx]
//.text:3CD1D09C                 push    eax

//.text:3CD4DBBE                 mov     eax, [edx+28h]
//.text:3CD4DBC1                 mov     ecx, esi
//.text:3CD4DBC3                 call    eax
//.text:3CD4DBC5                 pop     edi

	REBASE(bnetlib, sendheader_entry, 0x3CD4DBBE, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD4DBC5, 0x3C910000)
	
//.text:3CD4EE90                 lea     ecx, [edi+ebx]
//.text:3CD4EE93                 push    ecx
//.text:3CD4EE94                 mov     ecx, eax
//.text:3CD4EE96                 call    edx
	
	REBASE(bnetlib, send_message_entry, 0x3CD4EE90, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD4EE96, 0x3C910000)
}
*/
	

/* v 0.4.7841
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)

	REBASE(bnetlib, D3__std__String_delete, 0x3CED4618, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3cc16700, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CBB3FF0,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CBB0E90, 0x3C910000) 
	
//.text:3CBA121C        >>>         mov     edx, [eax+10h]
//.text:3CBA121F                 call    edx
//.text:3CBA1221                 movzx   eax, al
//.text:3CBA1224        <<<         test    eax, eax

//3ced4618
//3cc16700

	REBASE(bnetlib, message_parse_hook, 0x3CBA121C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CBA1224, 0x3C910000)
	
//.text:3CD045BC                 mov     cl, [ebp-2C4h]
//.text:3CD045C2                 movzx   ebx, word ptr [ebp-2BCh]
//.text:3CD045C9                 cmp     cl, 0FEh

//.text:3CD354CE                 mov     cl, [ebp-2FCh]
//.text:3CD354D4                 movzx   ebx, word ptr [ebp-2F4h]
//.text:3CD354DB                 cmp     cl, 0FEh


//.text:3CBA14B4                 call    deserialize_message
//.text:3CBA14B9                 add     esp, 8
//.text:3CBA14BC                 movzx   ecx, al


	REBASE(bnetlib, deserialize_message, 0x3CBA12F0, 0x3C910000)
	REBASE(bnetlib, recvheader_entry, 0x3CBA14B4, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CBA14BC, 0x3C910000)
		
//.text:3CD92D0E                 mov     eax, [edx+28h]
//.text:3CD92D11                 mov     ecx, esi
//.text:3CD92D13                 call    eax
//.text:3CD92D15                 pop     edi


	REBASE(bnetlib, sendheader_entry, 0x3CD92D0E, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD92D15, 0x3C910000)
	
//.text:3CD93FE0                 lea     ecx, [edi+ebx]
//.text:3CD93FE3                 push    ecx
//.text:3CD93FE4                 mov     ecx, eax
//.text:3CD93FE6                 call    edx
	
	REBASE(bnetlib, send_message_entry, 0x3CD93FE0, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD93FE6, 0x3C910000)

//.text:3CD7A468                 mov     edx, [eax+28h]
//.text:3CD7A46B                 add     ecx, ebx
//.text:3CD7A46D                 push    ecx
//.text:3CD7A46E                 mov     ecx, edi
	
	REBASE(bnetlib, send_message_entry1, 0x3CD7A468, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD7A46E, 0x3C910000)
	
//.text:3CD8311C                 lea     ecx, [ebx+edi]
//.text:3CD8311F                 push    ecx
//.text:3CD83120                 mov     ecx, eax
//.text:3CD83122                 call    edx
	
	REBASE(bnetlib, send_message_entry2, 0x3CD8311C, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD83122, 0x3C910000)
}
*/

/* v 0.5.1.8101
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	//3CED4618
	REBASE(bnetlib, D3__std__String_delete, 0x3CEAB618, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB7FD30, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB803B0,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB807B0, 0x3C910000) 
	
	REBASE(bnetlib, deserialize_message, 0x3CB9C1C0, 0x3C910000)
	
//.text:3CBA121C        >>>         mov     edx, [eax+10h]
//.text:3CBA121F                 call    edx
//.text:3CBA1221                 movzx   eax, al
//.text:3CBA1224        <<<         test    eax, eax

//.text:3CB9C0EC        >>>         mov     edx, [eax+10h]
//.text:3CB9C0EF                 call    edx
//.text:3CB9C0F1                 movzx   eax, al
//.text:3CB9C0F4        <<<         test    eax, eax


	REBASE(bnetlib, message_parse_hook, 0x3CB9C0EC, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CB9C0F4, 0x3C910000)
	
//.text:3CBA14B4                 call    deserialize_message
//.text:3CBA14B9                 add     esp, 8
//.text:3CBA14BC                 movzx   ecx, al

//.text:3CB9C384                 call    deserialize_message
//.text:3CB9C389                 add     esp, 8
//.text:3CB9C38C                 movzx   ecx, al


	REBASE(bnetlib, recvheader_entry, 0x3CB9C384, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CB9C38C, 0x3C910000)

//.text:3CD92D0E                 mov     eax, [edx+28h]
//.text:3CD92D11                 mov     ecx, esi
//.text:3CD92D13                 call    eax
//.text:3CD92D15                 pop     edi

//.text:3CD7C14E                 mov     eax, [edx+28h]
//.text:3CD7C151                 mov     ecx, esi
//.text:3CD7C153                 call    eax
//.text:3CD7C155                 pop     edi


	REBASE(bnetlib, sendheader_entry, 0x3CD7C14E, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD7C155, 0x3C910000)
	
//.text:3CD93FE0                 lea     ecx, [edi+ebx]
//.text:3CD93FE3                 push    ecx
//.text:3CD93FE4                 mov     ecx, eax
//.text:3CD93FE6                 call    edx

//.text:3CD7D47B                 lea     ecx, [edi+ebx]
//.text:3CD7D47E                 push    ecx
//.text:3CD7D47F                 mov     ecx, eax
//.text:3CD7D481                 call    edx


	REBASE(bnetlib, send_message_entry, 0x3CD7D47B, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD7D481, 0x3C910000)

//.text:3CD7A468                 mov     edx, [eax+28h]
//.text:3CD7A46B                 add     ecx, ebx
//.text:3CD7A46D                 push    ecx
//.text:3CD7A46E                 mov     ecx, edi
	
//.text:3CD617C8                 mov     edx, [eax+28h]
//.text:3CD617CB                 add     ecx, ebx
//.text:3CD617CD                 push    ecx
//.text:3CD617CE                 mov     ecx, edi

	REBASE(bnetlib, send_message_entry1, 0x3CD617C8, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD617CE, 0x3C910000)
	
//.text:3CD8311C                 lea     ecx, [ebx+edi]
//.text:3CD8311F                 push    ecx
//.text:3CD83120                 mov     ecx, eax
//.text:3CD83122                 call    edx
	
//.text:3CD6C703                 lea     ecx, [ebx+edi]
//.text:3CD6C706                 push    ecx
//.text:3CD6C707                 mov     ecx, eax
//.text:3CD6C709                 call    edx

	
	REBASE(bnetlib, send_message_entry2, 0x3CD6C703, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD6C709, 0x3C910000)
}
*/
	
/* v 0.6.0.8296 	
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	//3CED4618
	REBASE(bnetlib, D3__std__String_delete, 0x3CECA62C, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB8BBB0, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB8C230,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB8C630, 0x3C910000) 
	
	REBASE(bnetlib, deserialize_message, 0x3CBA8010, 0x3C910000)

//UPDATED
//.text:3CB9C0EC        >>>         mov     edx, [eax+10h]
//.text:3CB9C0EF                 call    edx
//.text:3CB9C0F1                 movzx   eax, al
//.text:3CB9C0F4        <<<         test    eax, eax

//.text:3CBA7F3C                 mov     edx, [eax+10h]
//.text:3CBA7F3F                 call    edx
//.text:3CBA7F41                 movzx   eax, al
//.text:3CBA7F44                 test    eax, eax

	REBASE(bnetlib, message_parse_hook, 0x3CBA7F3C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CBA7F44, 0x3C910000)

//UPDATED
//.text:3CBA81D4                 call    deserialize_message
//.text:3CBA81D9                 add     esp, 8
//.text:3CBA81DC                 movzx   ecx, al

	REBASE(bnetlib, recvheader_entry, 0x3CBA81D4, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CBA81DC, 0x3C910000)

//UPDATED	
//.text:3CD96E9E                 mov     eax, [edx+28h]
//.text:3CD96EA1                 mov     ecx, esi
//.text:3CD96EA3                 call    eax
//.text:3CD96EA5                 pop     edi

	REBASE(bnetlib, sendheader_entry, 0x3CD96E9E, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD96EA5, 0x3C910000)
	
//updated
//.text:3CD981CB                 lea     ecx, [edi+ebx]
//.text:3CD981CE                 push    ecx
//.text:3CD981CF                 mov     ecx, eax
//.text:3CD981D1                 call    edx

	REBASE(bnetlib, send_message_entry, 0x3CD981CB, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD981D1, 0x3C910000)

//updated	
//.text:3CD5F539                 mov     edx, [eax+28h]
//.text:3CD5F53C                 add     ecx, ebx
//.text:3CD5F53E                 push    ecx
//.text:3CD5F53F                 mov     ecx, edi

	REBASE(bnetlib, send_message_entry1, 0x3CD5F539, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD5F53F, 0x3C910000)
	
//updated
//.text:3CD87453                 lea     ecx, [ebx+edi]
//.text:3CD87456                 push    ecx
//.text:3CD87457                 mov     ecx, eax
//.text:3CD87459                 call    edx
	
	REBASE(bnetlib, send_message_entry2, 0x3CD87453, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD87459, 0x3C910000)
}
*/

/* v 0.6.0.8392
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	//3CED4618
	REBASE(bnetlib, D3__std__String_delete, 0x3CECA62C, 0x3C910000)
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB8BBB0, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB8C230,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB8C630, 0x3C910000) 
	
	REBASE(bnetlib, deserialize_message, 0x3CBA8010, 0x3C910000)

//UPDATED
//.text:3CB9C0EC        >>>         mov     edx, [eax+10h]
//.text:3CB9C0EF                 call    edx
//.text:3CB9C0F1                 movzx   eax, al
//.text:3CB9C0F4        <<<         test    eax, eax

//.text:3CBA7F3C                 mov     edx, [eax+10h]
//.text:3CBA7F3F                 call    edx
//.text:3CBA7F41                 movzx   eax, al
//.text:3CBA7F44                 test    eax, eax

	REBASE(bnetlib, message_parse_hook, 0x3CBA7F3C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CBA7F44, 0x3C910000)

//UPDATED
//.text:3CBA81D4                 call    deserialize_message
//.text:3CBA81D9                 add     esp, 8
//.text:3CBA81DC                 movzx   ecx, al

	REBASE(bnetlib, recvheader_entry, 0x3CBA81D4, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CBA81DC, 0x3C910000)

//UPDATED	
//.text:3CD96E9E                 mov     eax, [edx+28h]
//.text:3CD96EA1                 mov     ecx, esi
//.text:3CD96EA3                 call    eax
//.text:3CD96EA5                 pop     edi

	REBASE(bnetlib, sendheader_entry, 0x3CD96E9E, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD96EA5, 0x3C910000)
	
//updated
//.text:3CD981CB                 lea     ecx, [edi+ebx]
//.text:3CD981CE                 push    ecx
//.text:3CD981CF                 mov     ecx, eax
//.text:3CD981D1                 call    edx

	REBASE(bnetlib, send_message_entry, 0x3CD981CB, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD981D1, 0x3C910000)

//updated	
//.text:3CD5F539                 mov     edx, [eax+28h]
//.text:3CD5F53C                 add     ecx, ebx
//.text:3CD5F53E                 push    ecx
//.text:3CD5F53F                 mov     ecx, edi

	REBASE(bnetlib, send_message_entry1, 0x3CD5F539, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD5F53F, 0x3C910000)
	
//updated
//.text:3CD87453                 lea     ecx, [ebx+edi]
//.text:3CD87456                 push    ecx
//.text:3CD87457                 mov     ecx, eax
//.text:3CD87459                 call    edx
	
	REBASE(bnetlib, send_message_entry2, 0x3CD87453, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD87459, 0x3C910000)
}
*/

/* v 0.6.0.8610 
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	//3CED4618
	REBASE(bnetlib, D3__std__String_delete, 0x3CEB1688, 0x3C910000) 
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB863F0, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB86A70,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB86E70, 0x3C910000) 
	
	REBASE(bnetlib, deserialize_message, 0x3CBA28B0, 0x3C910000)

//UPDATED
//.text:3CBA7F3C                 mov     edx, [eax+10h]
//.text:3CBA7F3F                 call    edx
//.text:3CBA7F41                 movzx   eax, al
//.text:3CBA7F44                 test    eax, eax

//.text:3CBA27DC                 mov     edx, [eax+10h]
//.text:3CBA27DF                 call    edx
//.text:3CBA27E1                 movzx   eax, al
//.text:3CBA27E4                 test    eax, eax

	REBASE(bnetlib, message_parse_hook, 0x3CBA27DC, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CBA27E4, 0x3C910000)

//UPDATED
//.text:3CBA81D4                 call    deserialize_message
//.text:3CBA81D9                 add     esp, 8
//.text:3CBA81DC                 movzx   ecx, al

//.text:3CBA2A74                 call    deserialize_message
//.text:3CBA2A79                 add     esp, 8
//.text:3CBA2A7C                 movzx   ecx, al

	REBASE(bnetlib, recvheader_entry, 0x3CBA2A74, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CBA2A7C, 0x3C910000)

//UPDATED	
//.text:3CD96E9E                 mov     eax, [edx+28h]
//.text:3CD96EA1                 mov     ecx, esi
//.text:3CD96EA3                 call    eax
//.text:3CD96EA5                 pop     edi

//.text:3CD7B74E                 mov     eax, [edx+28h]
//.text:3CD7B751                 mov     ecx, esi
//.text:3CD7B753                 call    eax
//.text:3CD7B755                 pop     edi

	REBASE(bnetlib, sendheader_entry, 0x3CD7B74E, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD7B755, 0x3C910000)
	
//updated
//.text:3CD981CB                 lea     ecx, [edi+ebx]
//.text:3CD981CE                 push    ecx
//.text:3CD981CF                 mov     ecx, eax
//.text:3CD981D1                 call    edx

//.text:3CD7CA7C                 lea     ecx, [edi+ebx]
//.text:3CD7CA7F                 push    ecx
//.text:3CD7CA80                 mov     ecx, eax
//.text:3CD7CA82                 call    edx

	REBASE(bnetlib, send_message_entry, 0x3CD7CA7C, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD7CA82, 0x3C910000)

//updated	
//.text:3CD5F539                 mov     edx, [eax+28h]
//.text:3CD5F53C                 add     ecx, ebx
//.text:3CD5F53E                 push    ecx
//.text:3CD5F53F                 mov     ecx, edi

	REBASE(bnetlib, send_message_entry1, 0x3CD5F539, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD5F53F, 0x3C910000)
	
//updated
//.text:3CD87453                 lea     ecx, [ebx+edi]
//.text:3CD87456                 push    ecx
//.text:3CD87457                 mov     ecx, eax
//.text:3CD87459                 call    edx

//.text:3CD6B74D                 lea     ecx, [ebx+edi]
//.text:3CD6B750                 push    ecx
//.text:3CD6B751                 mov     ecx, eax
//.text:3CD6B753                 call    edx

	REBASE(bnetlib, send_message_entry2, 0x3CD6B74D, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD6B753, 0x3C910000)
}
*/

/* v 0.8.0.8815 */
void RebaseFunctions()
{
	unsigned int bnetlib = (unsigned int) GetModuleHandle("battle.net.dll");
//	REBASE(bnetlib, D3__std__String, 0x3CE4B258, 0x3C910000)
	//3CED4618
	REBASE(bnetlib, D3__std__String_delete, 0x3CEB2688, 0x3C910000) 
	
	REBASE(bnetlib, D3__TextFormat__PrintToString, 0x3CB86570, 0x3C910000)
	REBASE(bnetlib, D3__Message__GetDescriptor, 0x3CB86BF0,    0x3C910000)
	REBASE(bnetlib, D3__Descriptor__full_name, 0x3CB86FF0, 0x3C910000) 
	
	REBASE(bnetlib, deserialize_message, 0x3CBA2A30, 0x3C910000)

//UPDATED
//.text:3CBA7F3C                 mov     edx, [eax+10h]
//.text:3CBA7F3F                 call    edx
//.text:3CBA7F41                 movzx   eax, al
//.text:3CBA7F44                 test    eax, eax

//.text:3CBA27DC                 mov     edx, [eax+10h]
//.text:3CBA27DF                 call    edx
//.text:3CBA27E1                 movzx   eax, al
//.text:3CBA27E4                 test    eax, eax

//.text:3CBA295C                 mov     edx, [eax+10h]
//.text:3CBA295F                 call    edx
//.text:3CBA2961                 movzx   eax, al
//.text:3CBA2964                 test    eax, eax

	REBASE(bnetlib, message_parse_hook, 0x3CBA295C, 0x3C910000)
	REBASE(bnetlib, message_parse_return, 0x3CBA2964, 0x3C910000)

//UPDATED
//.text:3CBA81D4                 call    deserialize_message
//.text:3CBA81D9                 add     esp, 8
//.text:3CBA81DC                 movzx   ecx, al

//.text:3CBA2A74                 call    deserialize_message
//.text:3CBA2A79                 add     esp, 8
//.text:3CBA2A7C                 movzx   ecx, al

//.text:3CBA2BF4                 call    D3__DeserializeMessage
//.text:3CBA2BF9                 add     esp, 8
//.text:3CBA2BFC                 movzx   ecx, al

	REBASE(bnetlib, recvheader_entry, 0x3CBA2BF4, 0x3C910000)
	REBASE(bnetlib, recvheader_return, 0x3CBA2BFC, 0x3C910000)

//UPDATED	
//.text:3CD96E9E                 mov     eax, [edx+28h]
//.text:3CD96EA1                 mov     ecx, esi
//.text:3CD96EA3                 call    eax
//.text:3CD96EA5                 pop     edi

//.text:3CD7B74E                 mov     eax, [edx+28h]
//.text:3CD7B751                 mov     ecx, esi
//.text:3CD7B753                 call    eax
//.text:3CD7B755                 pop     edi

//.text:3CD7BBFE                 mov     eax, [edx+28h]
//.text:3CD7BC01                 mov     ecx, esi
//.text:3CD7BC03                 call    eax
//.text:3CD7BC05                 pop     edi

	REBASE(bnetlib, sendheader_entry, 0x3CD7BBFE, 0x3C910000)
	REBASE(bnetlib, sendheader_return, 0x3CD7BC05, 0x3C910000)
	
//updated
//.text:3CD981CB                 lea     ecx, [edi+ebx]
//.text:3CD981CE                 push    ecx
//.text:3CD981CF                 mov     ecx, eax
//.text:3CD981D1                 call    edx

//.text:3CD7CA7C                 lea     ecx, [edi+ebx]
//.text:3CD7CA7F                 push    ecx
//.text:3CD7CA80                 mov     ecx, eax
//.text:3CD7CA82                 call    edx

//.text:3CD7CF3C                 lea     ecx, [edi+ebx]
//.text:3CD7CF3F                 push    ecx
//.text:3CD7CF40                 mov     ecx, eax
//.text:3CD7CF42                 call    edx

	REBASE(bnetlib, send_message_entry, 0x3CD7CF3C, 0x3C910000)
	REBASE(bnetlib, send_message_return, 0x3CD7CF42, 0x3C910000)

//not found?
//.text:3CD5F539                 mov     edx, [eax+28h]
//.text:3CD5F53C                 add     ecx, ebx
//.text:3CD5F53E                 push    ecx
//.text:3CD5F53F                 mov     ecx, edi

	REBASE(bnetlib, send_message_entry1, 0x3CD5F539, 0x3C910000)
	REBASE(bnetlib, send_message_return1, 0x3CD5F53F, 0x3C910000)
	
//updated
//.text:3CD87453                 lea     ecx, [ebx+edi]
//.text:3CD87456                 push    ecx
//.text:3CD87457                 mov     ecx, eax
//.text:3CD87459                 call    edx

//.text:3CD6B74D                 lea     ecx, [ebx+edi]
//.text:3CD6B750                 push    ecx
//.text:3CD6B751                 mov     ecx, eax
//.text:3CD6B753                 call    edx

//.text:3CD6BBEA                 lea     ecx, [ebx+edi]
//.text:3CD6BBED                 push    ecx
//.text:3CD6BBEE                 mov     ecx, eax
//.text:3CD6BBF0                 call    edx

	REBASE(bnetlib, send_message_entry2, 0x3CD6BBEA, 0x3C910000)
	REBASE(bnetlib, send_message_return2, 0x3CD6BBF0, 0x3C910000)
}

char* D3__std__string_to_char(unsigned int astr) 
{
	if (*(int *)(astr + 0x18) > 0x0f) {
		return *(char **)(astr + 4);
	} else {
		return (char *)(astr + 4);
	
	}
}

void __fastcall D3__std__String(int ecx) {
	*(unsigned int*)(ecx+0x4) = 0x00;
	*(unsigned int*)(ecx+0x14) = 0x0;
	*(unsigned int*)(ecx+0x18) = 0x0f;
}

int new_std_string() {
	int res = (int)malloc(0x30);
	D3__std__String(res);
	return res;
}

void delete_std_string(int res) {
	asm("		pusha\n\t");
	asm("		mov		0x08(%ebp), %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__std__String_delete));
	asm("		call	*(%eax)\n\t");
	asm("		popa\n\t");
	free((void*)res);
}

void __stdcall LDebugString(const char* stringptr) 
{
    #ifdef TEXTFILE_OUTPUT
	FILE *file;	
	file = fopen("dbgoutput.txt","a+");       
    fprintf(file, "%s\n", stringptr);  
    fclose(file); 
	#endif
	
	OutputDebugString(stringptr);
}

void __stdcall lol_OutputDebugString(unsigned int msg) 
{
	char* stringptr = D3__std__string_to_char(msg);
	
    LDebugString(stringptr);
}

void hexdump(char* data, int size, char * outbuf, int osize) {
	char *abuf = outbuf;
	int remaining = osize - 4;
	for (int i=0; i < size; i++) {
		unsigned int next = (unsigned char) *data++;
		if (next < 0x10) {
			snprintf(abuf, remaining, "0%x ",next);
		} else {
			snprintf(abuf, remaining, "%x ", next);
		}
		abuf+=3;
		remaining-=3;
		if ((i+1) % 16 == 0) {
			snprintf(abuf, remaining, "\n");
			abuf += 1;
			remaining -= 1;
		}
	}
}

void __stdcall print_msg_to_str(int message, int resstr) {
	asm("		pusha\n\t");
	asm("		movl	0x0c(%ebp), %ecx\n\t"
		"		push	%ecx\n\t"
		"		movl	0x08(%ebp), %eax\n\t"
		"		push	%eax\n\t");
	asm("		movl	%0, %%eax\n\t" : : "m"(D3__TextFormat__PrintToString));
	asm("		movl	$0, %ecx\n\t"
		"		call	*%eax\n\t"
        "       add		$8, %esp\n\t"
		);
	asm("		popa\n\t");
}

void __stdcall print_recv_header(int header_message) {
	char buf[300];

	int msg_str = new_std_string();
	print_msg_to_str(header_message, msg_str);
	snprintf(buf, sizeof(buf)-1, "[ Recv ] ");
	LDebugString(buf);
	char *message = D3__std__string_to_char(msg_str);
	for (int i=0; message[i] != 0; i++) {
		if ((message[i] == 10) | (message[i] == 13)) {
			message[i] = 32;
		}
	}
	LDebugString(message);
	delete_std_string(msg_str);
}

void __stdcall print_send_header(int header_message) {
	char buf[300];

	int msg_str = new_std_string();
	print_msg_to_str(header_message, msg_str);
	snprintf(buf, sizeof(buf)-1, "[ Send ] ");
	LDebugString(buf);
	char *message = D3__std__string_to_char(msg_str);
	for (int i=0; message[i] != 0; i++) {
		if ((message[i] == 10) | (message[i] == 13)) {
			message[i] = 32;
		}
	}
	LDebugString(message);
	delete_std_string(msg_str);
}

void __stdcall print_msg(int message)
{
	asm("		sub		$0x50, %esp\n\t");

	//alloc std::string
	asm("		lea		-0x30(%ebp), %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "i"(D3__std__String));
	asm("		call	*%eax\n\t");
	
	//print messagetype
	asm("		movl	0x08(%ebp), %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__Message__GetDescriptor));
	asm("       call    *%eax\n\t"
		"		movl	%eax, %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__Descriptor__full_name));
	asm("       call    *%eax\n\t");
	asm("		movl	%eax, -0x34(%ebp)\n\t");//store result
	
	asm("		push	%eax\n\t");
	asm("		mov		%0, %%eax\n\t" : : "i"(check_ignore_msg));
	asm("       call    *%eax\n\t");
	asm("       test    %eax, %eax\n\t");
	asm("       jnz     1f\n\t");
	
	asm("		movl	-0x34(%ebp), %eax\n\t");
	asm("		push	%eax\n\t");
	asm("		mov		%0, %%eax\n\t" : : "i"(lol_OutputDebugString));
	asm("       call    *%eax\n\t");

	//print message content
	asm("		lea		-0x30(%ebp), %ecx\n\t"
		"		push	%ecx\n\t"
		"		movl	0x08(%ebp), %eax\n\t"
		"		push	%eax\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__TextFormat__PrintToString));
	asm("		movl	$0, %ecx\n\t"
		"		call	*%eax\n\t"
        "       add		$8, %esp\n\t"
		"		lea		-0x30(%ebp), %ecx\n\t"
		"		push	%ecx\n\t"
		);
	asm("		mov		%0, %%eax\n\t" : : "i"(lol_OutputDebugString));
	asm("       call    *%eax\n\t");

	asm("		1:\n\t"); //label to end

	//clean std::string
	asm("		lea		-0x30(%ebp), %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__std__String_delete));
	asm("		call	*(%eax)\n\t");
	
	asm("		add		$0x50, %esp\n\t");
}

void func1()
{
    asm(
		"		pop 	%ebp\n\t"

		"       movl     0x10(%eax), %edx\n\t"
        "       call    *%edx\n\t"
        "       movzx   %al, %eax\n\t"

		"		push    %eax\n\t"

		"		push 	0x0c(%ebp)\n\t" //param to the hooked function
		"		push	%ebp\n\t"
		"		mov		%esp, %ebp\n\t"

		"		sub		$0x200, %esp\n\t"
		"		pusha\n\t"
	);
	
	//skip if anidated:
	asm("		mov		%0, %%eax\n\t" : : "i"(func2)); 
	asm("       call    *%eax\n\t"
		"		test	%eax, %eax\n\t"
		"		jz		1f\n\t");
	
	//print the message:
	asm("		movl	0x04(%ebp), %eax\n\t"
		"		push	%eax\n\t");
	asm("		mov		%0, %%eax\n\t" : : "i"(print_msg));
	asm("       call    *%eax\n\t");
	
	asm("		mov 	%0, %%eax\n\t" : : "i"(func3));
	asm("       call    *%eax\n\t"
		"		1:\n\t"

		"		popa	\n\t"
		"		add		$0x200, %esp\n\t"

		"		pop 	%ebp\n\t"
		"		pop 	%eax\n\t" //param
		"		pop 	%eax\n\t");

	asm("		push	%0\n\t" : : "m"(message_parse_return));
	asm("		ret		\n\t");
}

void sendheader_hook()
{
	asm(
		"	pop     %ebp\n\t"
	);

	asm("	pusha\n\t");
	asm("	push	%esi\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(print_send_header));
	asm("	call    *%eax\n\t");
	asm("	popa\n\t");

//.text:3CD4DBBE                 mov     eax, [edx+28h]
//.text:3CD4DBC1                 mov     ecx, esi
//.text:3CD4DBC3                 call    eax
//.text:3CD4DBC5                 pop     edi

	asm("	mov     0x28(%edx), %eax\n\t"
		"	mov     %esi, %ecx\n\t"
		"	call    *%eax\n\t"
		);
		
	asm("	push	%0\n\t" : : "m"(sendheader_return));
	asm("	ret		\n\t");
}

void __stdcall c_print_msg(int protobuff_msg)
{
	LDebugString("[[");
	print_msg(protobuff_msg);
	LDebugString("]]");
}
	
void send_message_hook()
{
	asm(
		"	pop     %ebp\n\t"
	);

//.text:3CD93FE0                 lea     ecx, [edi+ebx]
//.text:3CD93FE3                 push    ecx
//.text:3CD93FE4                 mov     ecx, eax
//.text:3CD93FE6                 call    edx

//.text:3CD7D47B                 lea     ecx, [edi+ebx]
//.text:3CD7D47E                 push    ecx
//.text:3CD7D47F                 mov     ecx, eax
//.text:3CD7D481                 call    edx

	asm("	pusha\n\t");
	asm("	push	%eax\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(c_print_msg));
	asm("	call    *%eax\n\t");
	asm("	popa\n\t");

    asm(
		"   lea     (%edi, %ebx), %ecx\n\t"
        "   push    %ecx\n\t"
        "   mov     %eax, %ecx\n\t");

	asm("	push	%0\n\t" : : "m"(send_message_return));
	asm("	ret		\n\t");
}

void send_message_hook1()
{
	asm(
		"	pop     %ebp\n\t"
	);

	asm("	pusha\n\t");
	asm("	push	%edi\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(c_print_msg));
	asm("	call    *%eax\n\t");
	asm("	popa\n\t");

//.text:3CD7A468                 mov     edx, [eax+28h]
//.text:3CD7A46B                 add     ecx, ebx
//.text:3CD7A46D                 push    ecx
//.text:3CD7A46E                 mov     ecx, edi

//.text:3CD617C8                 mov     edx, [eax+28h]
//.text:3CD617CB                 add     ecx, ebx
//.text:3CD617CD                 push    ecx
//.text:3CD617CE                 mov     ecx, edi

	asm("	mov     0x28(%eax), %edx\n\t"
		"	add		%ebx, %ecx\n\t"
		"	push	%ecx\n\t"
		);
		
	asm("	push	%0\n\t" : : "m"(send_message_return1));
	asm("	ret		\n\t");
}

char nsend_message_hook2[] = "send_message_hook2\0";

void send_message_hook2()
{
	asm(
		"	pop     %ebp\n\t"
	);

	asm("	pusha\n\t");
	asm("	push	%eax\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(c_print_msg));
	asm("	call    *%eax\n\t");

	asm("	mov		%0, %%eax\n\t" : : "i"(nsend_message_hook2));
	asm("	push	%eax\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(LDebugString));
	asm("	call    *%eax\n\t");

	asm("	popa\n\t");

//.text:3CD8311C                 lea     ecx, [ebx+edi]
//.text:3CD8311F                 push    ecx
//.text:3CD83120                 mov     ecx, eax
//.text:3CD83122                 call    edx


	asm("	lea     (%edi, %ebx), %ecx\n\t"
		"	push	%ecx\n\t"
		"	mov     %eax, %ecx\n\t"
		);

	asm("	push	%0\n\t" : : "m"(send_message_return2));
	asm("	ret		\n\t");
}

void recvheader_hook() {
	asm("	pop %ebp\n\t");

//.text:3CBA14B4                 call    deserialize_message
//.text:3CBA14B9                 add     esp, 8
	asm("	mov		%0, %%eax\n\t" : : "m"(deserialize_message));
	asm("	call    *%eax\n\t");
	asm("	add		$8, %esp");
	
	asm("	pusha\n\t");
	asm("	mov		0x10(%ebp), %esi\n\t");
	asm("	push	%esi\n\t");
	asm("	mov		%0, %%eax\n\t" : : "i"(print_recv_header));
	asm("	call    *%eax\n\t");
	asm("	popa\n\t");
	
	asm ("	push	%0\n\t" : : "m"(recvheader_return));
	asm ("	ret		\n\t");
}

unsigned int __stdcall wrap_getname(unsigned int f)
{

	asm("		push 	%eax\n\t");
	asm("		pusha	\n\t");
	
	asm("		mov		8(%ebp), %ecx\n\t");

	asm("		mov		%0, %%eax\n\t" : : "m"(D3__Message__GetDescriptor));
	asm("       call    *%eax\n\t"
		"		movl	%eax, %ecx\n\t");
	asm("		mov		%0, %%eax\n\t" : : "m"(D3__Descriptor__full_name));
	asm("       call    *%eax\n\t");
	asm("       mov     %eax, -4(%ebp)\n\t");
	
	asm("		popa	\n\t");
	asm("		pop 	%eax\n\t");
}

int __stdcall check_ignore_msg(unsigned int msg)
{
	char* stringptr = D3__std__string_to_char(msg);

	if (strncmp("google.protobuf.FileDescriptorProto", stringptr, 35) == 0) {
		return 1;
	}
	return 0;
}

void hookPushRet( unsigned int address,	unsigned int jumpwhere)
{
  DWORD old;
  VirtualProtect((void*)address, 6, PAGE_EXECUTE_READWRITE, &old);
  *(unsigned char*)(address)  = 0x68;
  *(unsigned int*)(address+1)= jumpwhere;
  *(unsigned char*)(address+5) = 0xc3;
  VirtualProtect((void*)address, 6, old, &old);
  FlushInstructionCache(GetCurrentProcess(), (void*)address, 6);
}

void hookAddr( unsigned int address,	unsigned int calladdr)
{
  DWORD old;
  VirtualProtect((void*)address, 4, PAGE_EXECUTE_READWRITE, &old);

	*(unsigned int*)(address)  = calladdr;

  VirtualProtect((void*)address, 4, old, &old);
  FlushInstructionCache(GetCurrentProcess(), (void*)address, 4);
}

void TryHook() {
	HINSTANCE__* hlib = GetModuleHandle("battle.net.dll");
	if (hlib != 0) {
		RebaseFunctions();

		if (IsBadReadPtr((void*)message_parse_hook,4)) {
			LDebugString("TryHook: bad read ptr?");
			return;
		}
		if (*(unsigned int*)message_parse_hook ==  (unsigned int)&func1) {
			LDebugString("Lib seems already hooked.");
			return;
		}
		
		hookPushRet(recvheader_entry, (unsigned int)&recvheader_hook);
		hookPushRet(message_parse_hook, (unsigned int)&func1);

		hookPushRet(sendheader_entry, (unsigned int)&sendheader_hook);
		hookPushRet(send_message_entry, (unsigned int)&send_message_hook);
		//hookPushRet(send_message_entry1, (unsigned int)&send_message_hook1);
		hookPushRet(send_message_entry2, (unsigned int)&send_message_hook2);

		LDebugString("Lib Should be hooked");
	} else {
		LDebugString("TryHook: battle.net.dll not loaded yet");
	}
}

HINSTANCE__* __stdcall loadlibrary_(LPCWSTR lpLibFileName) {
	HINSTANCE__* lib = LoadLibraryW(lpLibFileName);
	TryHook();
	return lib;
}

int __declspec(dllexport) __stdcall StartDll(int param)
{
  #ifdef TEXTFILE_OUTPUT
	FILE *file;	
	file = fopen("dbgoutput.txt","w+");       
    fprintf(file, "Starting Log\n");  
    fclose(file); 
  #endif
	
  if ((tlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES) {
	MessageBox(NULL, "Error 0: cannt get tls slot", "",0);
	return 0;
  }
  
  //HINSTANCE hlib = LoadLibraryA("bnet/battle.net.dll");

  TryHook();
  
#ifndef EASYINJECTION
  hookAddr(0x011111F4, (unsigned int) &loadlibrary_);

  //code that jmps to the Entry Point of the exe
  TCHAR exepath[1000];
  if (0 == GetModuleFileName(0, exepath, 1000)){
	MessageBox(NULL, "Error 0: cannt getmodulefilename", "",0);
	return 0;
  }
  HINSTANCE__* mhandle = GetModuleHandle(exepath);

  PIMAGE_DOS_HEADER dos_header;
  PIMAGE_NT_HEADERS nt_header;
  dos_header = (PIMAGE_DOS_HEADER) mhandle;
  nt_header = (PIMAGE_NT_HEADERS)((unsigned int)mhandle + dos_header->e_lfanew);
  unsigned int entry_point = ((unsigned int)mhandle + nt_header->OptionalHeader.AddressOfEntryPoint);

  __asm(
          "mov %0, %%eax\n\t"
          "jmp *%%eax\n\t"
		  :
		  :"r"(entry_point)
		  :"%eax", "%ebx"
		);
#endif
}

BOOL WINAPI
DllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            // Code to run when the DLL is loaded
            break;

        case DLL_PROCESS_DETACH:
            // Code to run when the DLL is freed
            break;

        case DLL_THREAD_ATTACH:
            // Code to run when a thread is created during the DLL's lifetime
            break;

        case DLL_THREAD_DETACH:
            // Code to run when a thread ends normally.
            break;
    }
    return TRUE;
}