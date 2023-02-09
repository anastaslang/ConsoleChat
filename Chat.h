#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
#include "bad_login.h"
#include "bad_name.h"

class Chat 
{
    bool chatActive_ = false;//эта переменная отвечает за работу чата
    std::vector<User> users_;//контейнер для хранения данных пользователей(логин_пароль_имя)
    std::vector<Message> messages_;//контейнер для хранения сообщений пользователей(кто_кому_текст)
    std::shared_ptr<User> activeUser_ = nullptr;//указатель на активного на данный момент пользователя

    void enter();//вход в чат(ввод и проверка:логин/пароль)
    void registrator();//регистрация нового пользователя
    void showMessage() const;//отправка сообщений
    void showAllUsers() const;//показать всех пользователей
    void writeMessage();//написать и добавить сообщения в контейнер
    std::vector<User>& getAllUsers() { return users_; }//контейнер пользователей
    std::vector<Message>& getAllMessages() { return messages_; }//контейнер сообщений
    //поиск пользователя по логину
    std::shared_ptr<User> getUserByLogin(const std::string& login) const;
    //поиск пользователя по имени    
    std::shared_ptr<User> getUserByName(const std::string& name) const;

public:
    void turnOn();//запуск чата
    bool chatActive() const { return chatActive_; }//индикатор работы чата
    std::shared_ptr<User> getActiveUser() const { return activeUser_; }//показать активного в данный момент пользователя                                     
    void mainMenu();//главное меню
    void userMenu();//меню пользователя
};

