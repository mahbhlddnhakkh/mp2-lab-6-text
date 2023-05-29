#include <iostream>
#include "Text.h"

int main()
{
  TText text;
  TString datas1[] = {"Раздел 2", "\t2.1. Полиномы", "\t\t2.1.1. Определение", "\t\t2.1.2. Структура", "\t2.2. Тексты", "\t\t2.2.1. Определение", "\t\t2.2.2. Структура"};
  TString datas2[] = {"Раздел 3", "\t3.1. Таблицы", "\t\t3.1.1. Определение", "\t\t3.1.2. Структура", "\t3.2. Плексы", "\t\t3.2.1. Определение", "\t\t3.2.2. Структура"};
  size_t path1[] = {0}, path2[] = {1};
  
  text.PushDataInLevel(&(datas1[0]), nullptr, 0, false);

  text.PushDataInLevel(&(datas1[1]), nullptr, 0, 0, false);
  text.PushDataInLevel(&(datas1[4]), nullptr, 0, 0, false);

  text.PushDataInLevel(&(datas1[2]), path1, 1, 0, false);
  text.PushDataInLevel(&(datas1[3]), path1, 1, 0, false);

  text.PushDataInLevel(&(datas1[5]), path1, 1, 1, false);
  text.PushDataInLevel(&(datas1[6]), path1, 1, 1, false);

  text.PushDataInLevel(&(datas2[0]), nullptr, 0, false);

  text.PushDataInLevel(&(datas2[1]), nullptr, 0, 1, false);
  text.PushDataInLevel(&(datas2[4]), nullptr, 0, 1, false);

  text.PushDataInLevel(&(datas2[2]), path2, 1, 0, false);
  text.PushDataInLevel(&(datas2[3]), path2, 1, 0, false);

  text.PushDataInLevel(&(datas2[5]), path2, 1, 1, false);
  text.PushDataInLevel(&(datas2[6]), path2, 1, 1, false);

  for (auto& i : text)
  {
    std::cout << i << std::endl;
  }
  return 0;
}
