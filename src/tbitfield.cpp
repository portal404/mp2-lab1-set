#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


TBitField::TBitField()
{
  bitLen = 0;
  memLen = 0;
  pMem = nullptr;
}

TBitField::TBitField(int bitLen_, TELEM *pMem_, int memLen_)
{

  bitLen = bitLen_;
  pMem = pMem_;
  memLen = memLen_;
}

TBitField::TBitField(int len)
{
  if (len <= 0) throw "no";
  bitLen = len;
  memLen = (len + 8 * sizeof(TELEM) - 1) / 8 * sizeof(TELEM);
  pMem = new TELEM[memLen]{0}; // Я это у Миши взял, у меня код падал :))))))
}

TBitField::~TBitField()
{
  if (pMem)
  {
    delete[] pMem;
    pMem = nullptr;
    bitLen = 0;
    memLen = 0;
  }
}

TBitField::TBitField(TBitField &bf)
{
  if (bf.pMem)
  {
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++) pMem[i] = bf.pMem[i];
  } else
  {
    bitLen = 0;
    memLen = 0;
    pMem = nullptr;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n >= bitLen || n < 0) throw "Error! Your index is out of range!";
  return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n >= bitLen || n < 0) throw "Error! Your index is out of range!";
  return 1 << (n % (sizeof(TELEM) * 8));
}

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n >= bitLen || n < 0) throw "Error! Your index is out of range!";
  TELEM mask = GetMemMask(n);
  int i = GetMemIndex(n);
  pMem[i] |= mask;
}

void TBitField::ClrBit(const int n)
{
  int index = GetMemIndex(n);
  TELEM mask = GetMemMask(n);
  pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  int i = GetMemIndex(n);
  TELEM mask = GetMemMask(n);
  return (pMem[i] & mask) != 0;
}

// битовые операции

TBitField &TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf) return *this;
  delete[] pMem;
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  int i = 0;
  for (; i < memLen; ++i) pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.bitLen) return 0;
  int i = 0;
  for (; i < bitLen; ++i)
  {
    if (bf.GetBit(i) != (GetBit(i))) return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int resLen = max(bitLen, bf.bitLen);
  TBitField res(resLen);
  int i = 0;
  for (; i < bitLen; ++i)
  {
    if (GetBit(i)) res.SetBit(i);
  }
  for (i = 0; i < bf.bitLen; ++i)
  {
    if (bf.GetBit(i)) res.SetBit(i);
  }
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int resLen = max(bitLen, bf.bitLen);
  TBitField res(resLen);
  int i = 0;
  for (; i < min(bitLen, bf.bitLen); ++i)
  {
    res.pMem[i] = pMem[i] & bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res = TBitField(bitLen);
  int i = 0;
  for (; i < bitLen; ++i)
    if (!GetBit(i))
    {
      res.SetBit(i);
    }

  return res;
}


// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{ // мяу
  int l;
  std::cout << "Bit count: ";
  istr >> l;
  if (l <= 0) throw "Length cannot be 0 or less!";
  TBitField res(l);
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  return ostr;
}
