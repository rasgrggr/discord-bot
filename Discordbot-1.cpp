#include <dpp/dpp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <random>

using namespace std;

string get_token_from_file() {
    ifstream file("token.txt");
    string token;
    if (file.is_open()) {
        getline(file, token);
        file.close();
    }
    return token;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << unitbuf; // 버퍼 즉시 출력

    string token = get_token_from_file();
    if (token.empty()) {
        cerr << "토큰을 불러올 수 없습니다. token.txt 파일을 확인하세요." << endl;
        return 1;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    random_device rd;
    mt19937 gen(rd());

    vector<string> responses = {
        "넌 인간인가?",
        "누구냐 넌.",
        "무슨일인가?",
        "어딘가 수상한데...."
    };

    bot.on_log([](const dpp::log_t& event) {
        cout << "[" << event.severity << "] " << event.message << endl;
        });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        cout << "봇 로그인 완료: " << bot.me.username << endl;
        });

    bot.on_message_create([&bot, &gen, &responses](const dpp::message_create_t& event) {
        cout << "메시지 받음: " << event.msg.content << endl;

        if (event.msg.content == "!대사") {
            uniform_int_distribution<> dis(0, responses.size() - 1);
            string reply = responses[dis(gen)];
            bot.message_create(dpp::message(event.msg.channel_id, reply));
            cout << "명령어 인식됨! 응답: " << reply << endl;
        }
        });

    bot.start(dpp::st_wait); // 동기 방식으로 실행
    return 0;
}
