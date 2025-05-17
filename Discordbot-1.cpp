#include <dpp/dpp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <random>

std::string get_token_from_file() {
    std::ifstream file("token.txt");
    std::string token;
    if (file.is_open()) {
        std::getline(file, token);
        file.close();
    }
    return token;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << std::unitbuf; // 버퍼 즉시 출력

    std::string token = get_token_from_file();
    if (token.empty()) {
        std::cerr << "토큰을 불러올 수 없습니다. token.txt 파일을 확인하세요." << std::endl;
        return 1;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::string> responses = {
        "넌 인간인가?",
        "누구냐 넌.",
        "무슨일인가?",
        "어딘가 수상한데...."
    };

    bot.on_log([](const dpp::log_t& event) {
        std::cout << "[" << event.severity << "] " << event.message << std::endl;
        });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        std::cout << "봇 로그인 완료: " << bot.me.username << std::endl;
        });

    bot.on_message_create([&bot, &gen, &responses](const dpp::message_create_t& event) {
        std::cout << "메시지 받음: " << event.msg.content << std::endl;

        if (event.msg.content == "!대사") {
            std::uniform_int_distribution<> dis(0, responses.size() - 1);
            std::string reply = responses[dis(gen)];
            bot.message_create(dpp::message(event.msg.channel_id, reply));
            std::cout << "명령어 인식됨! 응답: " << reply << std::endl;
        }
        });

    bot.start(dpp::st_wait); // 동기 방식으로 실행
    return 0;
}
