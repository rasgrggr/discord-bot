cmake_minimum_required(VERSION 3.20)

project(MyDiscordBot)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/user/DPP/include")
link_directories("C:/Users/user/DPP/build/library")

# OpenSSL 경로 직접 지정
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.lib")


find_package(OpenSSL REQUIRED)

add_executable(MyDiscordBot Discordbot-1.cpp)

target_include_directories(MyDiscordBot PRIVATE
    "C:/Users/user/DPP/include"
    ${OPENSSL_INCLUDE_DIR}
)

target_link_directories(MyDiscordBot PRIVATE
    "C:/Users/user/DPP/build/library"
    "${OPENSSL_ROOT_DIR}/lib"
)

target_link_libraries(MyDiscordBot
    dpp
    OpenSSL::SSL
    OpenSSL::Crypto
)
