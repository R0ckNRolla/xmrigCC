/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "base/kernel/Platform.h"


#include <cstring>
#include <uv.h>


#ifdef XMRIG_FEATURE_TLS
#   include <openssl/ssl.h>
#   include <openssl/err.h>
#endif


namespace xmrig {

String Platform::m_userAgent;

thread_local int64_t Platform::m_threadTimeToSleep = {0};
thread_local int64_t Platform::m_threadUsageTime = {0};
thread_local int64_t Platform::m_systemTime = {0};

} // namespace xmrig


void xmrig::Platform::init(const char *userAgent)
{
#   ifdef XMRIG_FEATURE_TLS
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_digests();
#   endif

    if (userAgent) {
        m_userAgent = userAgent;
    }
    else {
        m_userAgent = createUserAgent();
    }
}
