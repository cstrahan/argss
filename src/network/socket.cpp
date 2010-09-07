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

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "socket.h"
#include "argss/classes/aerror.h"

Socket::Socket() {
#ifdef WIN32
	m_Socket = socket(AF_INET, SOCK_STREAM, AF_INET);
#else
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
#endif
}

void Socket::Connect(const std::string& host, unsigned short port) {
	struct sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
#ifdef WIN32
	hostAddr.sin_addr.s_addr = inet_addr(host.c_str());
#else
	(void)inet_pton(AF_INET, host.c_str(), &(hostAddr.sin_addr));
#endif
	hostAddr.sin_port = htons(port);

	if (connect(m_Socket, (struct sockaddr*)&hostAddr, sizeof(hostAddr))) {
		rb_raise(ARGSS::AError::id, "Could not connect to the host, make sure the host address is valid and the port is correct.");
	}
}

void Socket::Listen(unsigned short port, int maxclients) {
	struct sockaddr_in machineAddr;
	machineAddr.sin_family = AF_INET;
	machineAddr.sin_addr.s_addr = INADDR_ANY;
	machineAddr.sin_port = htons(port);

	if (bind(m_Socket, (struct sockaddr*)&machineAddr, sizeof(machineAddr))) {
		rb_raise(ARGSS::AError::id, "Could not bind the socket, port specified might be used.");
		return;
	}

	if (listen(m_Socket, maxclients)) {
		rb_raise(ARGSS::AError::id, "Could not set the socket to listening mode, make sure the arguments are right.");
	}
}

Buffer Socket::Receive() {
	Buffer buffer(0);
	unsigned short msglen = 0;
	if (recv(m_Socket, (char*)&msglen, 2, 0) <= 0) {
		rb_raise(ARGSS::AError::id, "Could not receive the message length.");
	} else {
		buffer = Buffer(msglen);
		char* pBufferData = buffer.GetData();
		if (recv(m_Socket, pBufferData, msglen, 0) <= 0) {
			rb_raise(ARGSS::AError::id, "Could not receive the message.");
		}
	}

	return buffer;
}


void Socket::Send(Buffer buffer) {
	unsigned short bufferSize = (unsigned short)buffer.GetSize();
	char* pFinalBuffer = new char[2 + bufferSize];
	memcpy(pFinalBuffer, &bufferSize, 2);
	memcpy(pFinalBuffer + 2, buffer.GetData(), bufferSize);

	if (send(m_Socket, pFinalBuffer, 2 + bufferSize, 0) <= 0) {
		rb_raise(ARGSS::AError::id, "Could not send the message.");
	}

	delete[] pFinalBuffer;
}

void Socket::Shutdown() {
	if (m_Socket) {
#ifdef WIN32
	shutdown(m_Socket, SD_BOTH);
#else
	shutdown(m_Socket, 0);
#endif
	}
}

Socket::~Socket() {
	if (m_Socket) {
		Shutdown();
		closesocket(m_Socket);
	}
}