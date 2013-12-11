//---------------------------------------------------------------------------


#pragma hdrstop

#include "TAxes.h"
#include <SysUtils.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TAxesType::TAxesType()
{
  	CutFirstAxes = false;
	OtherAxes = false;
	LastBogieFirstAxes = false;
	LastBogieOtherAxes = false;
	CutLastAxes = false;
}

__fastcall TAxes::TAxes()
{
	Pos = 0;
	fDistance = 0;
	WheelDia = 0.84;
	FlangeHeight = 0.025;
};

//---------------------------------------------------------------------------
void __fastcall TAxes::Save(int FileHandle)
{
	void * buff;
	buff = &fDistance;
	FileWrite(FileHandle, buff, sizeof(fDistance));
}

//---------------------------------------------------------------------------
bool __fastcall TAxes::Load(int FileHandle)
{
	void * Buff;
	FileRead(FileHandle, &fDistance, sizeof(fDistance));
//   fDistance = Buff;
	return true;
}

//---------------------------------------------------------------------------
__fastcall TAxes::TAxes(float AxesDistance)
{
	fDistance = AxesDistance;
}

//---------------------------------------------------------------------------
bool __fastcall TAxes::Initialize(const unsigned short CutNumber,
											 const unsigned short WagonNumber,
											 const unsigned BogieNumber,
											 const unsigned short AxesNumber,
											 const float Weight)
{
	FCutNumber = CutNumber;
	FWagonNumber = WagonNumber;
	FBogieNumber = BogieNumber;
	FAxesNumber = AxesNumber;
	FWeight = Weight;
	FlangeRadii = 0.5 * WheelDia + FlangeHeight;

	return true;
};

//---------------------------------------------------------------------------
TAxes & __fastcall TAxes::operator = (const TAxes & t)
{
	FAxesNumber = t.FAxesNumber;
	FBogieNumber = t.FBogieNumber;
	fDistance = t.fDistance;
	FWagonNumber = t.FWagonNumber;
	FCutNumber = t.FCutNumber;
	FWeight = t.FWeight;
	Pos = t.Pos;
	Type = t.Type;
//	AxesPoint = t.AxesPoint;

	return *this;
}

//---------------------------------------------------------------------------
bool __fastcall TAxes::operator == (TAxes * t)
{
	if (WagonNumber == t->WagonNumber && BogieNumber == t->BogieNumber
		 && AxesNumber == AxesNumber && CutNumber == t->CutNumber)
		return true;
	else
		return false;
}

//---------------------------------------------------------------------------
void __fastcall TAxes::SideElevation(TCanvas * Canvas, const int Position,
												 const int bottom, const float XScale, const float YScale)
{
	int x1, x2, y1, y2;
	int center;

	center = Position;
	x1 = center - 0.5 * WheelDia * XScale;
	x2 = center + 0.5 * WheelDia * XScale;
	y1 = bottom - WheelDia * YScale;
	y2 = bottom;
	Canvas->Ellipse(x1, y1, x2, y2);
}

//---------------------------------------------------------------------------
TAxesType & __fastcall TAxesType::operator = (const TAxesType & t)
{
	CutFirstAxes = t.CutFirstAxes;
	OtherAxes = t.OtherAxes;
	LastBogieFirstAxes = t.LastBogieFirstAxes;
	CutLastAxes = t.CutLastAxes;
	LastBogieOtherAxes = t.LastBogieOtherAxes;
	return *this;
}
