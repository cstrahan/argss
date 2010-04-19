//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
///         All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///     * Redistributions of source code must retain the above copyright
///       notice, this list of conditions and the following disclaimer.
///     * Redistributions in binary form must reproduce the above copyright
///       notice, this list of conditions and the following disclaimer in the
///       documentation and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
/// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
/// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////////

#ifndef BUFFER_H
#define BUFFER_H

#include <string>

class Buffer {
public:
	Buffer(int size);
	Buffer(const char* pBuffer, int size);

	template<class T> void Write(T obj) {
		// TODO: make it secure, check number of bytes left to fill
		// and fill them and only them.
		memcpy(m_pBuffer + m_Position, &obj, sizeof(obj));
		m_Position += sizeof(T);
	};

	template<class T> T Read() {
		// TODO: read only available bytes, shorten the third parameter
		// to the least possible to read.
		T obj;
		memcpy(&obj, m_pBuffer + m_Position, sizeof(obj));
		return obj;
	};

	void WriteString(const std::string& str);
	std::string ReadString();

	char* GetData() { return m_pBuffer; }
	int GetSize() { return m_Size; }
	int GetPosition() { return m_Position; }

	~Buffer();

private:
	char* m_pBuffer;
	int m_Size;
	int m_Position;

};

#endif