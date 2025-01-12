#include <dpp/dpp.h>
#include <cstdlib>
#include "/home/snacj/Dev/CPP/Discord-CPP/include/dotenv.h"


int main() {
    dotenv::init(".env");
    const std::string BOT_TOKEN = dotenv::getenv("BOT_TOKEN");

	dpp::cluster bot(BOT_TOKEN);
	 
	bot.on_log(dpp::utility::cout_logger());
	 
	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
	    if (event.command.get_command_name() == "ping") {
	        event.reply("Pong!");
	    }
	});
	 
	bot.on_ready([&bot](const dpp::ready_t& event) {
	    if (dpp::run_once<struct register_bot_commands>()) {
	        bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
	    }
	});
	 
	bot.start(dpp::st_wait);
}
