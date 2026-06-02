#include <dpp/dpp.h>
#include <cstdlib>

int main() {
    // 環境変数からトークン取得（安全）
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token) {
        std::cout << "DISCORD_TOKEN not set!\n";
        return 1;
    }

    dpp::cluster bot(
    token,
    dpp::i_default_intents | dpp::i_message_content
);

    // ログ表示
    bot.on_log(dpp::utility::cout_logger());

    // 起動完了時
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot>()) {
            bot.set_presence(
                dpp::presence(
                    dpp::ps_online,
                    dpp::at_game,
                    "WSL / GCE Bot"
                )
            );
        }
    });

    // メッセージ受信イベント
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        auto msg = event.msg;

        if (msg.content == "!ping") {
            bot.message_create(
                dpp::message(msg.channel_id, "pong 🏓")
            );
        }

        if (msg.content == "!hello") {
            bot.message_create(
                dpp::message(msg.channel_id, "こんにちは！botだよ 🤖")
            );
        }
    });

    bot.start(dpp::st_wait);
}