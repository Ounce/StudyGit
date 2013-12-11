//---------------------------------------------------------------------------


#pragma hdrstop

#include "TBogie.h"
#include <SysUtils.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TBogie::TBogie()
{
   resize(0);
}
;

//---------------------------------------------------------------------------
bool __fastcall TBogie::Initialize(const unsigned short CutNumber,
											  const unsigned short WagonNumber,
											  const unsigned short Number,
											  const float Weight,
											  const eType WagonType)
{
	unsigned short i, q;
	bool S = false;

	q = size();
	for (i = 0; i < q; i++)
		at(i).Initialize(CutNumber, WagonNumber, Number, i, Weight / q);
	return true;
}

//---------------------------------------------------------------------------
TBogie & TBogie::operator = (const TBogie & t)
{
	unsigned short i, q;

	q = t.size();
	for (i = 0; i < q; i++)
		push_back(t[i]);

	fDistance =t.fDistance;
	FWeight = t.FWeight;
	Pos = t.Pos;
	sModel = t.sModel;
	ModelNameLength = t.ModelNameLength;

	return *this;
}

//---------------------------------------------------------------------------
TAxes * __fastcall TBogie::GetAxesPoint(const unsigned short Index)
{
	return &at(Index);
}

//---------------------------------------------------------------------------
float __fastcall TBogie::GetAxesDistance(unsigned short Index)
{
	return at(Index).Distance;
}

//---------------------------------------------------------------------------
void __fastcall TBogie::SetAxesDistance(unsigned short Index, float Distance)
{
	at(Index).Distance = Distance;
}

//---------------------------------------------------------------------------
unsigned short __fastcall TBogie::GetAxesQuantity(void)
{
	return size();
}

//---------------------------------------------------------------------------
void __fastcall TBogie::SetAxesQuantity(unsigned short NewQuantity)
{
	resize(NewQuantity);
}

//---------------------------------------------------------------------------
float __fastcall TBogie::GetAxesPosition(unsigned short Index)
{
	return at(Index).Position;
}

//---------------------------------------------------------------------------
void __fastcall TBogie::AddAxes(const float AxesDistance)
{
	TAxes Axes;

	Axes.Distance = AxesDistance;
	push_back(Axes);
};

//---------------------------------------------------------------------------
void __fastcall TBogie::AddAxes(const TAxes Axes)
{
	push_back(Axes);
};


//---------------------------------------------------------------------------
void __fastcall TBogie::Save(int FileHandle)
{
	unsigned short i;
	unsigned short Quantity;

	ModelNameLength = sModel.Length();
	FileWrite(FileHandle, &ModelNameLength, sizeof(ModelNameLength));

	FileWrite(FileHandle, sModel.c_str(), ModelNameLength);

	Quantity = AxesQuantity;
	FileWrite(FileHandle, &Quantity, sizeof(Quantity));
	for (i = 0; i < AxesQuantity; i++)
		at(i).Save(FileHandle);
}



//---------------------------------------------------------------------------
bool __fastcall TBogie::Load(int FileHandle)
{
	unsigned short i;
	unsigned short Quantity;
	char * ModelName;

	FileRead(FileHandle, &ModelNameLength, sizeof(ModelNameLength));

	ModelName = new char[ModelNameLength + 1];
	i = FileRead(FileHandle, &ModelName, ModelNameLength);
	sModel = ModelName;
	delete [] ModelName;

	FileRead(FileHandle, &Quantity, sizeof(Quantity));
	resize(Quantity);
	for (i = 0; i < Quantity; i++)
		at(i).Load(FileHandle);
	return true;
}


//---------------------------------------------------------------------------
bool __fastcall TBogie::IsEmpty(void)
{
	if (size() == 0) return true;
	else return false;
}


//---------------------------------------------------------------------------
void __fastcall TBogies::Delete(unsigned short Index)
{
	iterator p;
//   p = ;
	erase(&at(Index));
}

//---------------------------------------------------------------------------
void __fastcall TBogies::Save(int FileHandle)
{
	unsigned short i, q;
	q = size();

	FileWrite(FileHandle, &q, sizeof(q));
	for (i = 0; i < q; i++)
		at(i).Save(FileHandle);
}

//---------------------------------------------------------------------------
bool __fastcall TBogies::Load(int FileHandle)
{
	unsigned short i, q;
	FileRead(FileHandle, &q, sizeof(q));
	resize(q);
	for (i = 0; i < q; i++)
		at(i).Load(FileHandle);
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TBogie::SetPos(float value)
{
	unsigned short i, q;
	float P;

	Pos = value;     // This set Position of Bogie's Centre.

	P = value;
	q = size();
	for (i = 0; i < q; i++)
	{
		P -= at(i).Distance;   // Setting the position of axes.
		at(i).Position = P;
	}
};

//---------------------------------------------------------------------------
TAxes __fastcall TBogie::GetAxes(unsigned short Index)
{
	return at(Index);
};

//---------------------------------------------------------------------------
TBogies & __fastcall TBogies::operator = (const TBogies & t)
{
	unsigned short i, q;

	clear();
	q = t.size();
	for (i = 0; i < q; i++)
		push_back(t[i]);

	return *this;
};

//---------------------------------------------------------------------------
TBogieList & __fastcall TBogieList::operator = (const TBogieList & t)
{
	unsigned short i, q;

	q = t.size();
	for (i = 0; i < q; i ++)
		push_back(t[i]);

	return *this;
};


//---------------------------------------------------------------------------
TBogie __fastcall TBogieList::New(const AnsiString ModelName, const float AxesBase,
												const unsigned short Quantity)
{
	unsigned short i;
	TBogie Bogie;
	TAxes A;
	A.Distance = - 0.5 * (Quantity - 1) * AxesBase;
	Bogie.AddAxes(A);
	for (i = 1; i < Quantity; i++)
	{
		A.Distance = AxesBase;
		Bogie.AddAxes(A);
	}
	Bogie.Model = ModelName;
	return Bogie;
}


//---------------------------------------------------------------------------
TBogie __fastcall TBogieList::WhichBogie(const AnsiString ModelName)
{
	unsigned short i, q;

	q = size();
	for (i = 0; i < q; i++)
		if (at(i).Model == ModelName)
			return at(i);
	return at(0);
};


//---------------------------------------------------------------------------
__fastcall TBogieList::TBogieList()
{
	push_back(New("Not Exist"));
	push_back(New("E2"));
	push_back(New("K5", 1.8, 2));
	push_back(New("K6", 1.83, 2));
	push_back(New("F1", 0, 1));
}

//---------------------------------------------------------------------------
void __fastcall TBogie::SideElevation(TCanvas * Canvas, const float XPosition,
												  const int bottom, const float XScale, const float YScale)
{
	//XPosition -- Center Position of the Bogie.
	int i, q;
	float XPos;      //屏蔽了TBogie类中的Position。

	XPos = XPosition;
	q = size();
	for (i = 0; i < q; i++) {
		XPos -= at(i).Distance * XScale;
		at(i).SideElevation(Canvas, XPos, bottom, XScale, YScale);
	}
}

