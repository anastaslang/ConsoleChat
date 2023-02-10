#pragma once
#include <exception>
struct NameExcept : public std::exception
{
    const char *what() const noexcept override { return "это имя уже используется"; }//проверка имени на уникальность
 };


