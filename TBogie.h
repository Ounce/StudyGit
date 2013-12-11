//---------------------------------------------------------------------------
/*
* Copyright (c) 2003,哈尔滨铁路局减速顶调速系统研究中心
* All rights reserved.
*
* 文件名称： TBogie.h
* 文件标识：
* 摘 要： 这个文件定义了驼峰溜放车组。为了方便阅读和管理，将原TWaggon.h文件中
*         的内容分成4部分：TAxes.h、TBogie.h、TWagon.h、TCut.h。
*
* 当前版本： 0.2
* 作 者： 李文建
* 完成日期： 正在编制
*
* 取代版本：TWaggon.h
* 原作者 ： 李文建
* 完成日期： 2003年11月6日
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
