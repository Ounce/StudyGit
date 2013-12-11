//---------------------------------------------------------------------------
/*
* Copyright (c) 2003,��������·�ּ��ٶ�����ϵͳ�о�����
* All rights reserved.
*
* �ļ����ƣ� TAxes.h
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
	float fDistance;  //���ᣨAxes����Distance�ǳ����࣬��һ�������Ǿ೵��ת������ĵľ��롣
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
