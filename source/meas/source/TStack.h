//---------------------------------------------------------------------------
#ifndef TStackH
#define TStackH
//---------------------------------------------------------------------------
#endif
// Define stack class
template <class T> class TAtCorStack
{
  private:
     T*  FData;
     int FMaxSize;
     int FHead;
     int FCurrentSize;
  public:
     //----------------------------
     TAtCorStack<T> (const int n)
     {
        FData = new T[n];
        FMaxSize = n;
        FHead = 0;
        FCurrentSize = 0;
     }
     //----------------------------
     ~TAtCorStack<T> ()
     {
        FMaxSize = 0;
        delete [] FData;
     }
     //----------------------------
     T& operator[] (const int i)
     {
        int l = (FHead + i < FMaxSize ? FHead + i : FHead + i - FMaxSize);
        return FData[l];
     }
     //----------------------------
     void Push(const T pValue)
     {
      if (FCurrentSize < FMaxSize)
      {
        FData[FCurrentSize] = pValue;
        FCurrentSize++;
        FHead = 0;
      }
      else
      {
        if (FHead < FMaxSize)
        {
          FData[FHead] = pValue;
          if (FHead == FMaxSize - 1)
            FHead = 0;
          else
            FHead++;
        }
        else
        {
          throw Exception("Template class Stack error");
        }
      }
     }
     //----------------------------
     int Size()
     {
        return FCurrentSize;
/*
        if (FCurrentSize < FMaxSize)
        {
          return FCurrentSize;
        }
        else
        {
          return FMaxSize;
        }
*/
     }
     //----------------------------
     void Clear()
     {
        FHead = 0;
        FCurrentSize = 0;
     }
     //----------------------------
     bool Full()
     {
        return (Size() == FMaxSize);
     }
     //----------------------------
     T& Last()
     {
        if (FCurrentSize == 0)
        {
          throw Exception("Stack has not filled yet");
        }
        if (FCurrentSize < FMaxSize)
           return FData[FCurrentSize-1];
        else
           return (FHead <= 0 ? FData[FMaxSize-1] : FData[FHead-1]);
     }
     //----------------------------
     T& First()
     {
        return FData[FHead];
     }
     //----------------------------
     bool IsEqual(const T pValue)
     {
        if (Full())
        {
          for (int i=0; i<FMaxSize; i++)
          {
            if (FData[i]!=pValue)
              return false;
          }
          return true;
        }
        return false;
     }
     //----------------------------
     void Fill(const T pValue)
     {
        Clear();
        while (!Full())
           Push(pValue);
     }
};

