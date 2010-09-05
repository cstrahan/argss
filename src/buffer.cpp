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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "buffer.h"

Buffer::Buffer(int size) {
	m_pBuffer = new char[size];
	m_Size = size;
	m_Position = 0;
}

Buffer::Buffer(const char* pBuffer, int size) {
	m_pBuffer = strdup(pBuffer);
	m_Size = size;
	m_Position = 0;
}

void Buffer::WriteString(const std::string& str) {
	// TODO: make it memory secure
	memcpy(m_pBuffer + m_Position, str.c_str(), str.size());
	m_Position += str.size();
}

std::string Buffer::ReadString() {
	unsigned int size = strlen(m_pBuffer + m_Position) + 1;
	char* pBuffer = new char[size];
	// TODO: make it memory secure
	memcpy(pBuffer, m_pBuffer + m_Position, size);
	m_Position += size;
	std::string str(pBuffer);

	delete[] pBuffer;

	return str;
}

Buffer::~Buffer() {
	delete[] m_pBuffer;
}
