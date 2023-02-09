#include "Chat.h"

int main()
{
    Chat chat;// создаем объект типа чат
    chat.turnOn();// запускаем чат
    while (chat.chatActive())
    {//индикатор работы чата
        chat.mainMenu();//открывам главное меню и входим по паролю

        while (chat.getActiveUser())
        {//если вход выполнен успешно,то мы увидим активного пользователя(себя)
            chat.userMenu();// меню пользователя
        }
    }
    return 0;
}
