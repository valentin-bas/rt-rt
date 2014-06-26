#ifndef _ANDROIDBUF_H_
#define _ANDROIDBUF_H_

#include <android/log.h>
#include <streambuf>
 
class androidbuf: public std::streambuf {
public:
    enum { bufsize = 128 }; // ... or some other suitable buffer size
    androidbuf() { this->setp(buffer, buffer + bufsize - 1); }
private:
    int overflow(int c) {
        if (c == traits_type::eof()) {
            *this->pptr() = traits_type::to_char_type(c);
            this->sbumpc();
        }
        return this->sync()? traits_type::eof(): traits_type::not_eof(c);
    }
    int sync() {
        int rc = 0;
        if (this->pbase() != this->pptr()) {
            __android_log_print(ANDROID_LOG_ERROR,
                               "Native",
                               "%s",
                               std::string(this->pbase(),
                                           this->pptr() - this->pbase()).c_str());
            rc = 0;
            this->setp(buffer, buffer + bufsize - 1);
        }
        return rc;
    }
    char buffer[bufsize];
};

#endif