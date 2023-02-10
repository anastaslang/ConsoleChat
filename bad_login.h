#pragma once
#include <exception>
struct LoginExcept : public std::exception
{
    const char *what() const noexcept override { return "этот логин уже используется"; }//проверка логина на уникальность
};

