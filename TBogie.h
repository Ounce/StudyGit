//---------------------------------------------------------------------------
/*
* Copyright (c) 2003,��������·�ּ��ٶ�����ϵͳ�о�����
* All rights reserved.
*
* �ļ����ƣ� TBogie.h
* �ļ���ʶ��
* ժ Ҫ�� ����ļ��������շ���ų��顣Ϊ�˷����Ķ��͹�����ԭTWaggon.h�ļ���
*         �����ݷֳ�4���֣�TAxes.h��TBogie.h��TWagon.h��TCut.h��
*
* ��ǰ�汾�� 0.2
* �� �ߣ� ���Ľ�
* ������ڣ� ���ڱ���
*
* ȡ���汾��TWaggon.h
* ԭ���� �� ���Ľ�
* ������ڣ� 2003��11��6��
*/
#ifndef TBogieH
#define TBogieH

#include <vector.h>
#include "TAxes.h"
#include <system.hpp>
//---------------------------------------------------------------------------


class TBogie : public vector<TAxes>
{
public:
   eType Type;
//   __property short Number = {read = iNumber, write = iNumber};
   __property TAxes Axes[unsigned short Index] = { read=GetAxes };
   __property AnsiString Model = {read = sModel, write = sModel};
   __property float Position = {read = Pos, write = SetPos};
	__property float Distance = {read = fDistance, write = fDistance};
   __property float AxesDistance[unsigned short Index]
                            = {read = GetAxesDistance, write = SetAxesDistance};
   __property float Weight = { read=FWeight };

	__property unsigned short AxesQuantity = {read = GetAxesQuantity, write = SetAxesQuantity};
   __property float AxesPosition[unsigned short Index] = { read=GetAxesPosition };

   __fastcall TBogie();
	bool __fastcall Initialize(const unsigned short CutNumber,
										const unsigned short WagonNumber,
                              const unsigned short Number,
										const float Weight,
										const eType WagonType);

   void __fastcall Save(int FileHandle);
   bool __fastcall Load(int FileHandle);
	TBogie & operator = (const TBogie & t);
   void __fastcall AddAxes(const float AxesDistance);
   void __fastcall AddAxes(const TAxes Axes);
   bool __fastcall IsEmpty(void);
	TAxes * __fastcall GetAxesPoint(const unsigned short Index);

	void __fastcall SideElevation(TCanvas * Canvas, const float XPosition, const int bottom,
											const float XScale, const float YScale);
protected:
private:
//   short iNumber;
   AnsiString sModel;
   float Pos;
   float fDistance;
   float FWeight;
   unsigned short ModelNameLength;

   TAxes __fastcall GetAxes(unsigned short Index);
   float __fastcall GetAxesDistance(unsigned short Index);
   void __fastcall SetAxesDistance(unsigned short Index, float Distance);
   unsigned short __fastcall GetAxesQuantity(void);
	void __fastcall SetAxesQuantity(unsigned short NewQuantity);
   float __fastcall GetAxesPosition(unsigned short Index);
   void __fastcall SetPos(float vlaue);
};


class TBogies : public vector<TBogie>
{
public:
//   unsigned short __fastcall NewNumber(void);
   TBogies & __fastcall operator = (const TBogies & t);
   void __fastcall Save(int FileHandle);
   bool __fastcall Load(int FileHandle);
   void __fastcall Delete(unsigned short Index);
protected:
private:

//   bool __fastcall InNumber(unsigned short NewNumber);

};


class TBogieList : public vector<TBogie>
{
public:
   __fastcall TBogieList();
   TBogieList & __fastcall operator = (const TBogieList & t);
   TBogie __fastcall WhichBogie(const AnsiString ModelName);
private:
   TBogie __fastcall New(const AnsiString ModelName, const float AxesBase = 1.75,
                           const unsigned short Quantity = 2);
};


#endif
