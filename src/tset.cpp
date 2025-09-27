// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : bitField(mp)
{
  if (mp < 0) throw "Out of range!";
  maxPower = mp;
}

// конструктор копирования

TSet::TSet(TSet &s) : bitField(s.bitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(-1)
{
}

TSet::operator TBitField()
{
  return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
  if (elem >= maxPower || elem < 0) throw "element out of range!";
  return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
  bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
  bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet &TSet::operator=(const TSet &s) // присваивание
{
  if (*this != s)
  {
    maxPower = s.maxPower;
    bitField = s.bitField;
  }
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return bitField == s.bitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  //return (bitField != s.bitField);
  return bitField != s.bitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  int n = max(maxPower, s.maxPower);
  TSet res = TSet(n);
  res.bitField = bitField | s.bitField;
  return res;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
  if (elem >= maxPower || elem < 0) throw "Error! Your index is out of range!";
  TSet res(*this);
  res.InsElem(elem);
  return res;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
  TSet res(*this);
  res.DelElem(elem);
  return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  int temp = max(maxPower, s.maxPower);
  TSet res(temp);
  res.bitField = bitField & s.bitField;
  return res;
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(*this);
  res.bitField = ~bitField;
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int t, n;
  istr >> n;
  int i = 0;
  for (; i < n; ++i)
  {
    istr >> t;
    s.InsElem(t);
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TSet &s) // вывод
{
  for (int i = 0; i < s.maxPower; ++i)
  {
    if (s.IsMember(i)) ostr << i;
  }
  return ostr;
}
