// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len <= 0)
    throw  1;
  bitLen = len;
  memLen = len / (8 * sizeof(TELEM)) + 1;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem)
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > bitLen))
    throw 1;
  return  n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n < 0) || (n > bitLen))
    throw 1;
  return (1 << (n % (8 * sizeof(TELEM))));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n > -1) && (n < bitLen))
    pMem[GetMemIndex(n)] |= GetMemMask(n);
  else
    throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n > -1) && (n < bitLen))
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
  else
    throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n > -1) && (n < bitLen))
    return pMem[GetMemIndex(n)] & GetMemMask(n);
  else
    throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  bitLen = bf.bitLen;
  if (memLen != bf.memLen)
  {
    memLen = bf.memLen;
    if (pMem != NULL)
      delete pMem;
    pMem = new TELEM[memLen];
  }
  if (pMem != NULL)
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int res = 1;
  if (bitLen != bf.bitLen)
    res = 0;
  else
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
      {
        res = 0;
        break;
      }
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int res = 0;
  if (bitLen != bf.bitLen)
    res = 1;
  else
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
      {
        res = 1;
        break;
      }
  return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int len = bitLen;
  if (bf.bitLen > len)
    len = bf.bitLen;
  TBitField temp(len);
  for (int i = 0; i < memLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    temp.pMem[i] |= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int len = bitLen;
  if (bf.bitLen > len)
    len = bf.bitLen;
  TBitField temp(len);
  for (int i = 0; i < memLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    temp.pMem[i] &= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField tmp(bitLen);
  for (int i = 0; i < bitLen; i++)
  {
    if (this->GetBit(i) == 0)
      tmp.SetBit(i);
  }
  return tmp;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
  int i = 0;
  char sym;
  do
  {
    istr >> sym;
  } while (sym != ' ');
  while (1)
  {
    if (sym == '0')
      bf.ClrBit(i++);
    else if (sym == '1')
      bf.SetBit(i++);
    else
      break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
  {
    if (bf.GetBit(i) == 1)
      ostr << '1';
    else
      ostr << '0';
  }
  return ostr;
}
