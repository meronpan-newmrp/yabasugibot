#include <dpp/dpp.h>
#include <cstdlib>

int main() {
    const dpp::snowflake MRS_ID = 1298304487605403658;

    // トークンの取得
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
                    "やばー"
                )
            );
        }
    });

    bot.guild_command_create(
        dpp::slashcommand("sendmsg", "メッセージを送信", bot.me.id),
        .add_option(
            dpp::command_option(dpp::co_channel, "channel", "送信するチャンネル", true)
        )
        .add_option(
            dpp::command_option(dpp::co_string, "message", "送信するメッセージ", true)
        ),
        MRS_ID
    );

    //コマンド
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "sendmsg") {
            auto channel_id = std::get<dpp::snowflake>(event.get_parameter("channel"));
            auto message = std::get<std::string>(event.get_parameter("message"));

            bot.message_create(
                dpp::message(channel_id, message)
            );

            event.reply(
                dpp::message("メッセージを送信完了！")
                .set_flags(dpp::m_ephemeral)
            );
        }
    });
    // メッセージ受信イベント
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        auto msg = event.msg;

        if (msg.content == "!ping") {
            bot.message_create(
                dpp::message(msg.channel_id, "ピンポォン！！")
            );
        }

        if (msg.content == "!hello") {
            bot.message_create(
                dpp::message(msg.channel_id, "やあ！ぼくはパスタ。")
            );
        }
    });

    bot.start(dpp::st_wait);
}