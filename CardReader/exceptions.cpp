/*
 * Copyright (c) 2017, Sergey Stolyarov <sergei@regolit.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include "stdafx.h"
#include <string>
//#include <pcsclite.h>
// #include <winscard.h>
// #include <wintypes.h>
using namespace std;

#include "xpcsc.hpp"

char* SCardGetLastError(DWORD lErr)
{

	switch (lErr)
	{
	case 0x80100001:
		return "SCARD_F_INTERNAL_ERROR";
		break;

	case 0x80100002:
		return "SCARD_E_CANCELLED";
		break;

	case 0x80100003:
		return "SCARD_E_INVALID_HANDLE";
		break;

	case 0x80100004:
		return "SCARD_E_INVALID_PARAMETER";
		break;

	case 0x80100005:
		return "SCARD_E_INVALID_TARGET";
		break;

	case 0x80100006:
		return "SCARD_E_NO_MEMORY";
		break;

	case 0x80100007:
		return "SCARD_F_WAITED_TOO_LONG";
		break;

	case 0x80100008:
		return "SCARD_E_INSUFFICIENT_BUFFER";
		break;

	case 0x80100009:
		return "SCARD_E_UNKNOWN_READER";
		break;

	case 0x8010000A:
		return "SCARD_E_TIMEOUT";
		break;

	case 0x8010000B:
		return "SCARD_E_SHARING_VIOLATION";
		break;

	case 0x8010000C:
		return "SCARD_E_NO_SMARTCARD";
		break;

	case 0x8010000D:
		return "SCARD_E_UNKNOWN_CARD";
		break;

	case 0x8010000E:
		return "SCARD_E_CANT_DISPOSE";
		break;

	case 0x8010000F:
		return "SCARD_E_PROTO_MISMATCH";
		break;

	case 0x80100010:
		return "SCARD_E_NOT_READY";
		break;

	case 0x80100011:
		return "SCARD_E_INVALID_VALUE";
		break;

	case 0x80100012:
		return "SCARD_E_SYSTEM_CANCELLED";
		break;

	case 0x80100013:
		return "SCARD_F_COMM_ERROR";
		break;

	case 0x80100014:
		return "SCARD_F_UNKNOWN_ERROR";
		break;

	case 0x80100015:
		return "SCARD_E_INVALID_ATR";
		break;

	case 0x80100016:
		return "SCARD_E_NOT_TRANSACTED";
		break;

	case 0x80100017:
		return "SCARD_E_READER_UNAVAILABLE";
		break;

	case 0x80100018:
		return "SCARD_P_SHUTDOWN";
		break;

	case 0x80100019:
		return "SCARD_E_PCI_TOO_SMALL";
		break;

	case 0x8010001A:
		return "SCARD_E_READER_UNSUPPORTED";
		break;

	case 0x8010001B:
		return "SCARD_E_DUPLICATE_READER";
		break;

	case 0x8010001C:
		return "SCARD_E_CARD_UNSUPPORTED";
		break;

	case 0x8010001D:
		return "SCARD_E_NO_SERVICE";
		break;

	case 0x8010001E:
		return "SCARD_E_SERVICE_STOPPED";
		break;

	case 0x8010001F:
		return "SCARD_E_UNEXPECTED";
		break;

	case 0x80100020:
		return "SCARD_E_ICC_INSTALLATION";
		break;

	case 0x80100021:
		return "SCARD_E_ICC_CREATEORDER";
		break;

	case 0x80100022:
		return "SCARD_E_UNSUPPORTED_FEATURE";
		break;

	case 0x80100023:
		return "SCARD_E_DIR_NOT_FOUND";
		break;

	case 0x80100024:
		return "SCARD_E_FILE_NOT_FOUND";
		break;

	case 0x80100025:
		return "SCARD_E_NO_DIR";
		break;

	case 0x80100026:
		return "SCARD_E_NO_FILE";
		break;

	case 0x80100027:
		return "SCARD_E_NO_ACCESS";
		break;

	case 0x80100028:
		return "SCARD_E_WRITE_TOO_MANY";
		break;

	case 0x80100029:
		return "SCARD_E_BAD_SEEK";
		break;

	case 0x8010002A:
		return "SCARD_E_INVALID_CHV";
		break;

	case 0x8010002B:
		return "SCARD_E_UNKNOWN_RES_MNG";
		break;

	case 0x8010002C:
		return "SCARD_E_NO_SUCH_CERTIFICATE";
		break;

	case 0x8010002D:
		return "SCARD_E_CERTIFICATE_UNAVAILABLE";
		break;

	case 0x8010002E:
		return "SCARD_E_NO_READERS_AVAILABLE";
		break;

	case 0x80100065:
		return "SCARD_W_UNSUPPORTED_CARD";
		break;

	case 0x80100066:
		return "SCARD_W_UNRESPONSIVE_CARD";
		break;

	case 0x80100067:
		return "SCARD_W_UNPOWERED_CARD";
		break;

	case 0x80100068:
		return "SCARD_W_RESET_CARD";
		break;

	case 0x80100069:
		return "SCARD_W_REMOVED_CARD";
		break;

	case 0x8010006A:
		return "SCARD_W_SECURITY_VIOLATION";
		break;

	case 0x8010006B:
		return "SCARD_W_WRONG_CHV";
		break;

	case 0x8010006C:
		return "SCARD_W_CHV_BLOCKED";
		break;

	case 0x8010006D:
		return "SCARD_W_EOF";
		break;

	case 0x8010006E:
		return "SCARD_W_CANCELLED_BY_USER";
		break;

	case 0x0000007B:
		return "INACCESSIBLE_BOOT_DEVICE";
		break;

	default:
		return "Invalid Error Code";

	}

}

namespace xpcsc {

PCSCError::PCSCError(long code)
    : std::runtime_error(""), pcsc_code(code)
{
}

const char * PCSCError::what() const throw ()
{
    return SCardGetLastError(pcsc_code);
}

long PCSCError::code() const throw ()
{
    return pcsc_code;
}

ConnectionError::ConnectionError(const char * what)
    : std::runtime_error(what)
{
}

ATRParseError::ATRParseError(const char * what)
    : std::runtime_error(what)
{}

APDUParseError::APDUParseError(const char * what)
    : std::runtime_error(what)
{}

BERTLVParseError::BERTLVParseError(const char * what)
    : std::runtime_error(what)
{}

}
