# InfProtection_lab2
Лабораторная работа студента 4-го курса Смирнова С.Ю.

### Задание:
> Реализовать шифрование и дешифрование с использованием одного из предложенных алгоритмов

## Описание
Основано на https://github.com/serd2011/TP_EncryptorApp

Приложение состоит из двух частей – библиотеки шифрования и графического интерфейса.    
Для удобства пользователя во время работы появляется индикатор прогресса выполнения.    
Работу шифратора можно прервать в любой момент нажатием кнопки 'Отмена'

![Интерфейс программы](./Resources/examples/main_window_done_state.png?raw=true "Интерфейс")

Интерфейс программы создан с использованием библиотеки wxWidgets

## Build
- Создать файлы проекта для IDE с помощью premake. (Экземпляр добавлен в папку ``` vendor/premake/ ```)

- Получить библиотеку [wxWidgets](https://www.wxwidgets.org/) и добавить ее к проекту.
