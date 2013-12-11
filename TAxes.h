//---------------------------------------------------------------------------
/*
* Copyright (c) 2003,哈尔滨铁路局减速顶调速系统研究中心
* All rights reserved.
*
* 文件名称： TAxes.h
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
#ifndef TAxesH
#define TAxesH

#include <vector.h>
#include <Graphics.hpp>

enum eType {Alone = -2, First = -1, Other = 0, Last = 1};
enum eAxesType {FirstAxes = -1, OtherAxes = 0, LastAxes, LastBogieFirstAxes, LastBogieOtherAxes};

//---------------------------------------------------------------------------
class TAxesPoint	//which cut, which wangon, which begio, which axes is this axes.
{
public:
   unsigned short Cut;
   unsigned short Wagon;
   unsigned short Bogie;
	unsigned short Axes;
};

class TAxesType
{
public:
	bool CutFirstAxes;
	bool OtherAxes;
	bool LastBogieFirstAxes;
	bool CutLastAxes;
	bool LastBogieOtherAxes;
	__fastcall TAxesType();
	TAxesType & __fastcall operator = (const TAxesType & t);
};


class TAxes
{
public:
	float WheelDia;
	float FlangeHeight;
	float FlangeRadii;
	TAxesType Type;
   __property float Distance = {read = fDistance, write = fDistance};
   __property float Position = { read=Pos, write=Pos };
	__property unsigned short CutNumber = { read=FCutNumber, write=FCutNumber };
	__property unsigned short WagonNumber = { read=FWagonNumber, write=FWagonNumber };
	__property unsigned short BogieNumber = { read=FBogieNumber, write=FBogieNumber };
	__property unsigned short AxesNumber = { read=FAxesNumber, write=FAxesNumber };
	__property float Weight = { read=FWeight };

	__fastcall TAxes();
	__fastcall TAxes(float Distance);
	bool __fastcall Initialize(const unsigned short CutNumber,
										const unsigned short WagonNumber,
										const unsigned BogieNumber,
										const unsigned short AxesNumber,
										const float Weight);
	void __fastcall Save(int FileHandle);
	bool __fastcall Load(int FileHandle);

	TAxes & __fastcall operator = (const TAxes & t);
	bool __fastcall operator == (TAxes * t);

	void __fastcall SideElevation(TCanvas * Canvas, const int BogiePosition,
											const int bottom, const float XScale, const float YScale);
protected:

private:
	float Pos;
	float fDistance;  //车轴（Axes）的Distance是车轴间距，第一个车轴是距车辆转向架中心的距离。
//	TAxesPoint AxesPoint;

/*	const unsigned short GetCutNumber(void) { return FCutNumber; }
	unsigned short GetWagonNumber(void) { return AxesPoint.Wagon; }
	unsigned short GetBogieNumber(void) { return AxesPoint.Bogie; }
	unsigned short GetAxesNumber(void) { return AxesPoint.Axes; }
	void SetCutNumber(unsigned short Number) { AxesPoint.Cut = Number; }
	void SetWagonNumber(unsigned short Number) { AxesPoint.Wagon = Number; }
	void SetBogieNumber(unsigned short Number) { AxesPoint.Bogie = Number; }
	void SetAxesNumber(unsigned short Number) { AxesPoint.Axes = Number; }  */

	unsigned short FCutNumber;
	unsigned short FWagonNumber;
	unsigned short FBogieNumber;
	unsigned short FAxesNumber;
	float FWeight;
};

#endif
