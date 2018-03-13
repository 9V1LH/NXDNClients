/*
 *   Copyright (C) 2009-2014,2016,2018 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	NXCoreNetwork_H
#define	NXCoreNetwork_H

#include "RingBuffer.h"
#include "UDPSocket.h"
#include "Timer.h"

#include <cstdint>
#include <string>

class CNXCoreNetwork {
public:
	CNXCoreNetwork(const std::string& address, bool debug);
	~CNXCoreNetwork();

	bool open();

	bool write(const unsigned char* data, unsigned int len);

	bool read(unsigned char* data, unsigned int len);

	void close();

	void clock(unsigned int ms);

private:
	CUDPSocket                 m_socket;
	in_addr                    m_address;
	bool                       m_debug;
	CRingBuffer<unsigned char> m_buffer;
};

#endif
