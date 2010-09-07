/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include <string>
#include "tools/win32/registry.h"

///////////////////////////////////////////////////////////
/// Unicode std::string to LPCWSTR
///////////////////////////////////////////////////////////
std::wstring s2ws2(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

///////////////////////////////////////////////////////////
/// Read String value
///////////////////////////////////////////////////////////
std::string Registry::ReadStrValue(HKEY hkey, std::string key, std::string val) {
	char value[1024];
	DWORD size = 1024;
	DWORD type = REG_SZ;
	HKEY key_handle;
#if UNICODE
	std::wstring wkey = s2ws2(key.c_str());
#else
	std::string wkey = key;
#endif
	if (RegOpenKeyEx(hkey, wkey.c_str(), NULL, KEY_QUERY_VALUE, &key_handle)) {
		return "";
	}
#if UNICODE
	std::wstring wval = s2ws2(val.c_str());
#else
	std::string wval = val;
#endif
	if (RegQueryValueEx(key_handle, wval.c_str(), NULL, &type, (LPBYTE)&value, &size)) {
		return "";
	}
	RegCloseKey(key_handle);

	std::string string_value = "";
	for (unsigned int i = 0; i < size; i++) {
		if (value[i] != '\0' ) {
			string_value += value[i];
		}
	}
	return string_value;
}

///////////////////////////////////////////////////////////
/// Read Binary value
///////////////////////////////////////////////////////////
int Registry::ReadBinValue(HKEY hkey, std::string key, std::string val, unsigned char* bin) {
	DWORD size = 1024;
	DWORD type = REG_BINARY;
	HKEY key_handle;
#if UNICODE
	std::wstring wkey = s2ws2(key.c_str());
#else
	std::string wkey = key;
#endif
	if (RegOpenKeyEx(hkey, wkey.c_str(), NULL, KEY_QUERY_VALUE, &key_handle)) {
		return 0;
	}
#if UNICODE
	std::wstring wval = s2ws2(val.c_str());
#else
	std::string wval = val;
#endif
	if (RegQueryValueEx(key_handle, wval.c_str(), NULL, &type, bin, &size)) {
		return 0;
	}
	RegCloseKey(key_handle);

	return size;
}

#endif
