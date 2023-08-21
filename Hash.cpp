#include "Hash.h"
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

std::string Hash::generateSHA256Hash(const std::string& message) {
    using namespace CryptoPP;

    SHA256 hash;
    byte digest[SHA256::DIGESTSIZE];
    hash.Update((const byte*)message.data(), message.size());
    hash.Final(digest);

    std::string hexDigest;
    HexEncoder encoder(new StringSink(hexDigest));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return hexDigest;
}
