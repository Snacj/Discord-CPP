#include <dpp/dpp.h>
#include <cstdlib>
#include "/home/snacj/Dev/CPP/Discord-CPP/include/dotenv.h"

#define GUILD_ID 715258302501748847


int main() {
    dotenv::init(".env");
    const std::string BOT_TOKEN = dotenv::getenv("BOT_TOKEN");

	dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());
 
    /* Use the on_user_context_menu event to look for user context menu actions */
    bot.on_user_context_menu([](const dpp::user_context_menu_t& event) {
        /* check if the context menu name is High Five */
        if (event.command.get_command_name() == "high five") {
            dpp::user user = event.get_user();
            dpp::user author = event.command.get_issuing_user();
            event.reply(author.get_mention() + " slapped " + user.get_mention());
        }
    });

     bot.on_slashcommand([&bot](const dpp::slashcommand_t & event) {
	        /* Check which command they ran */
	        if (event.command.get_command_name() == "ping") {
	            event.reply("Pong!");
	        } else if (event.command.get_command_name() == "pong") {
	            event.reply("Ping!");
	        } else if (event.command.get_command_name() == "ding") {
	            event.reply("Dong!");
	        } else if (event.command.get_command_name() == "dong") {
	            event.reply("Ding!");
	        }
	    });
 
    bot.on_ready([&bot](const dpp::ready_t &event) {
        if (dpp::run_once<struct clear_bot_commands>()) {
            bot.guild_bulk_command_delete(GUILD_ID);
        }
        if (dpp::run_once<struct register_bot_commands>()) {
            /* Create some commands */
            dpp::slashcommand pingcommand("ping", "Pong!", bot.me.id);
            dpp::slashcommand pongcommand("pong", "Ping!", bot.me.id);
            dpp::slashcommand dingcommand("ding", "Dong!", bot.me.id);
            dpp::slashcommand dongcommand("dong", "Ding!", bot.me.id);
 
            /* Register our commands in a list using bulk */
            /* Create the command */
            dpp::slashcommand command;
            command.set_name("High Five")
                .set_application_id(bot.me.id)
                .set_type(dpp::ctxm_user);
 
            /* Register the command */
            bot.guild_command_create(command, GUILD_ID); 
            bot.guild_command_create(pingcommand, GUILD_ID); 
            bot.guild_command_create(pongcommand, GUILD_ID); 
            bot.guild_command_create(dingcommand, GUILD_ID); 
            bot.guild_command_create(dongcommand, GUILD_ID); 
        }
    });
 
    /* Start bot */
    bot.start(dpp::st_wait);
 
    return 0;
}	 
