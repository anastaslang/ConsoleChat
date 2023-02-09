#include <iostream>
#include <ostream>
#include "Chat.h"

void Chat::turnOn() 
{
    chatActive_ = true;
}
//поиск пользователя по логину
std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const 
{
   for (auto &user : users_)
   {
   
    if (login == user.getUserLogin())
        return std::make_shared<User>(user);
   }
   return nullptr;
}
//поиск пользователя по имени
std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
    for (auto &user : users_)
    {
        if (name == user.getUserName())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

void Chat::enter()//вход в чат, ввод пары логин/пароль
{
    std::string login, password;
    char operation;

    do
    {
        std::cout << "\033[1m\033[35m" << "Логин: " << "\033[0m";
        std::cin >> login;
        std::cout << "\033[1m\033[35m" << "Пароль: " << "\033[0m";
        std::cin >> password;

        activeUser_ = getUserByLogin(login);

        if (activeUser_ == nullptr || (password != activeUser_->getUserPassword()))
        {
            activeUser_ = nullptr;
            std::cout <<"\033[31m"<< "Неверный логин или пароль..." << std::endl;
            std::cout << "\033[32m" << "(0)выход " << "\033[31m" << "или попробуйте еще" << "\033[0m"<< std::endl;

            std::cin >> operation;

            if (operation == '0')
                break;
        }
    } while (!activeUser_);
}

void Chat:: registrator()//регистрация
{
    std::string login, password, name;
    std::cout << "\033[33m" << "Логин: " << "\033[0m";
    std::cin >> login;
    std::cout << "\033[33m" << "Пароль: " << "\033[0m";
    std::cin >> password;
    std::cout << "\033[33m" << "Имя: " << "\033[0m";
    std::cin  >> name;
//проверка логина на уникальность
    if (getUserByLogin(login) || login == "всех")
    {
        throw LoginExcept();
    }
//проверка имени на уникальность
    if (getUserByName(name) || name == "всех")
    {
        throw NameExcept();
    }
//создаем объект типа User и сохраняем в контейнере пользователей
    User user = User(login, password, name);
    users_.push_back(user);
    activeUser_ = std::make_shared<User>(user);
}

void Chat::showMessage() const //показать сообщения
{
    std::string from;
    std::string to;

    std::cout << "\033[1m\033[34m" << "    СOOБЩЕНИЯ    " << "\033[0m" << std::endl;
    for (auto &mess : messages_)
    {
        //показать сообения.От активного пользователя и для всех.
        if (activeUser_->getUserLogin() == mess.getFrom() || activeUser_->getUserLogin() == mess.getTo() || mess.getTo() == "всех")
        {
            from = (activeUser_->getUserLogin() == mess.getFrom()) ? "меня" : getUserByLogin(mess.getFrom())->getUserName();
            if (mess.getTo() == "всех")
            {
              to = "всех";
            }
            else
            {
              to = (activeUser_->getUserLogin() == mess.getTo()) ? "меня " : getUserByLogin(mess.getTo())->getUserName();
            }
            std::cout << "\033[1m\033[34m" << "Сообщение от " << from << " для " << to << std::endl;
            std::cout << "текст сообщения: " << "\033[0m"  << mess.getText() <<  std::endl;
        }
    }
    std::cout << "\033[36m" << "***************" << "\033[0m" << std::endl;
}

void Chat::mainMenu()//главное меню
{
    activeUser_ = nullptr;

    char operation;
    do 
    {
        std::cout << "\033[34m" << "Добро пожаловать в чат! Выберите действие:" << std::endl; 
        std::cout << "\033[1m\033[35m" << "(1)Войти в свой аккаунт" << std::endl;
        std::cout << "\033[33m" << "(2)Регистрация" << std::endl;
        std::cout << "\033[32m" << "(0)Выход из чата" << std::endl;
        std::cout << "\033[36m" << "***************" << "\033[0m" << std::endl;
        std::cin >> operation;
  // выбор операции
        switch (operation)
        {
            case '1'://вход
                enter();
                break;
            case '2'://регистрация и проверка на уникальность
                try
                {
                    registrator();
                }
                catch (const std::exception &e)
                {
                    std::cout << "\033[31m" << e.what() << "\033[0m" << std::endl;
                }
                break;
            case '0':
                chatActive_ = false;//деактивация чата
                break;
            default: 
                std::cout << "\033[31m" << "Введите 1, 2, или 0 " << "\033[0m" << std::endl;
                break;
        }
    } while (!activeUser_ && chatActive_);
}

void Chat::userMenu() //меню пользователя
{
    char operation;
    std::cout << "\033[34m"<< "Здравствуйте, " << "\033[1m\033[35m" << activeUser_->getUserName() << std::endl;
    while (activeUser_)
    {
        std::cout << "\033[1m\033[34m" << "Выберите действие: " << "\033[1m\033[35m" << std::endl;
        std::cout << "(1)Показать сообщения" << std::endl;
        std::cout << "(2)Написать сообщение" << std::endl;
        std::cout << "(3)Показать всех зарегистрированных пользователей" << std::endl;
        std::cout <<"\033[32m" << "(0)Выход из аккаунта" << std::endl;
        std::cout << "\033[36m" << "*************** " << "\033[0m" << std::endl;
        std::cin >> operation;
    //выбор операции
        switch (operation)
        {
        case '1':
            showMessage();//показать сообщения для активного пользователя и для всех
            break;
        case '2':
            addMessage();//написать и отправить сообщение
            break;
        case '3':
            showAllUsersName();//показать всех зарегистрированных пользователей
            break;
        case '0':
            activeUser_ = nullptr;//выход
            break;
        default:
            std::cout << "\033[31m" << "Вы ничего не выбрали" << "\033[0m" << std::endl;
            break;
        }
    }
}

void Chat::showAllUsersName() const//показать всех пользователей
{
    std::string name;

    std::cout << "\033[1m\033[34m" << "ВСЕ ПОЛЬЗОВАТЕЛИ ЧАТА: " << std::endl;
    for (auto &use : users_)
    {
        std::cout << "\033[1m\033[34m" << "имя: " << "\033[0m" << use.getUserName() << std::endl;
        std::cout << "\033[1m\033[34m" << "логин: "<< "\033[0m" << use.getUserLogin() << std::endl;
    }
   
}

void Chat::addMessage()//написание и  добавление сообщений в контейнер
{
    std::string to, text;
    std::cout << "\033[1m\033[34m" << "Для кого будет сообщение?(напишите имя или слово 'всех'):" << "\033[0m" << std::endl;
    std::cin >> to;
    std::cout << "\033[1m\033[34m" << "Текст сообщения: " << "\033[0m";
    std::cin.ignore();
    getline(std::cin, text);

    if (!(to == "всех" || getUserByName(to))) //если не удалось найти получателя по имени
    {
        std::cout << "\033[31m" << "Не удалось найти получателя по имени " << to << "\033[0m" << std::endl;
        return;
    }
    if (to == "всех")//сохраняем сообщения в контейнер для всех пользователей
        messages_.push_back(Message{activeUser_->getUserLogin(), "всех", text});
    else//иначе сохраняем для конкретного пользователя
        messages_.push_back(Message{activeUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text});
}  
             
