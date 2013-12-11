//---------------------------------------------------------------------------


#pragma hdrstop

#include "TArrester.h"
#include "CoFunction.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


/*
   	__declspec(dllexport) TArrester __fastcall WhichArrester(const AnsiString ModelName);
   	__declspec(dllexport) float __fastcall ArresterWork(const unsigned short WorkIndex,
   																		 const unsigned short PistonWorkIndex,
   																		 const float WagonSpeed,
   																		 const TCriticalSpeed CriticalSpeed);
   	__declspec(dllexport) AnsiString __fastcall WhichArresterName(const unsigned short Index);

*/

extern TArresterList ArresterList;


//---------------------------------------------------------------------------
TArrester & __fastcall TArrester::operator = (const TArrester & t)
{
	Model = t.Model;
	WorkNumber = t.WorkNumber;
	RiseTime = t.RiseTime;
	FCriticalSpeed = t.FCriticalSpeed;
	Index = t.Index;
	ModelIndex = t.ModelIndex;
	SerialNumber = t.SerialNumber;
	Name = t.Name;

	BaseWork = t.BaseWork;
	ResistanceWork = t.ResistanceWork;

	BeginPosition = t.BeginPosition;
	EndPosition = t.EndPosition;
	IsSingleSide = t.IsSingleSide;
	Positions = t.Positions;
	ioPositions = t.ioPositions;
	Quantity = t.Quantity;
	FPistonModel = t.FPistonModel;
	FPistonWorkIndex = t.FPistonWorkIndex;
	return *this;
}

//---------------------------------------------------------------------------
TArrester & __fastcall TArrester::operator = (const AnsiString ModelName)
{
//   *this = WhichArrester(ModelName);

	return *this;
}


//---------------------------------------------------------------------------
__fastcall TArrester::TArrester()
{
	CriticalSpeed = 0;
	CriticalSpeedWindage = 0;
}

//---------------------------------------------------------------------------
bool __fastcall TArrester::Initialize(const TMeasurementRate MeasurementRate)
{
	unsigned short i;    //Todo 5 -o Li Wenjian : Save WorkNumber Temporaryly
	unsigned short q;
	TArrester Arrester;
	TArresterList List;

	float MaxPos, MinPos;

	Arrester = List.Which(Model);
	FPistonModel = Arrester.FPistonModel;
	FPistonWorkIndex = Arrester.FPistonWorkIndex;
	WorkNumber = Arrester.WorkNumber;

	MaxPos = 0;
	MinPos = 10000000;
	q = Positions.size();
	for (i = 0; i < q; i++)
	{
		Positions[i] = ioPositions[i] * MeasurementRate.Length;
		if (Positions[i] > MaxPos) MaxPos = Positions[i];
		if (Positions[i] < MinPos) MinPos = Positions[i];
	}
   Positions.InstallMode = ioPositions.InstallMode;
	BeginPosition = MinPos;
	EndPosition = MaxPos;
	ioBeginPosition = BeginPosition / MeasurementRate.Length;
	ioEndPosition = EndPosition / MeasurementRate.Length;
//   TRetarder::Initialize();   //Todo 5 -o Li Wenjian : It change the WorkNumber!
	return true;
}

//---------------------------------------------------------------------------
float __fastcall TArrester::Work(const float WagonSpeed, const float WheelRadii,
											const float FlangeHeight, float &ak9)
{
	float w;

	w = TRetarder::Work(WagonSpeed, WheelRadii, FlangeHeight, ak9, 0);
	return w;
}

//---------------------------------------------------------------------------
float __fastcall TArrester::Works(const unsigned short CutTrackNumber, const int CutNumber,
											 const float WagonSpeed, const float Start, const float End,
											 const float NowTime, const TAxes Axes)
{
	float w;
	int q;
	float ak9;

	if (!PassIt(CutTrackNumber)) return 0;
	q = PassQuantity(CutTrackNumber, CutNumber, Start, End, NowTime, WagonSpeed, Axes.Type);
	if (q < 1) return 0;
	w = Work(WagonSpeed, 0.5 * Axes.WheelDia, Axes.FlangeHeight, ak9);
	return w * q;
//	return  Work(WagonSpeed) * PassQuantity(CutTrackNumber, Start, End);
}

//---------------------------------------------------------------------------
__fastcall TArresters::TArresters()
{
	StopPointCaption.SetCaption(uLength, "计算停车点", "Stop Point Positiong");
	PositionCaption.SetCaption(uLength, "位置", "Position");
}

bool __fastcall TArresters::VerifyInput(const AnsiString ModelText,
													 const AnsiString QuantityText,
													 const AnsiString StopPointText)
{
	float f;
	TArresterList List;
	if (List.Index(ModelText) == 0) {
		MessageBoxA(NULL, "停车顶型号必须与列表中的某个相同！", "错误！", MB_OK);
		return false;
	}
	if (!IsFloat(QuantityText, f, "停车顶数量不能为负数，也不能为空！", 0)) return false;
	if (!IsFloat(StopPointText, f, "计算停车点不能为负数，不能等于0，也不能为空！", 0)) return false;
	return true;
}

//---------------------------------------------------------------------------
bool __fastcall TArresters::Initialize(const TMeasurementRate MeasurementRate)
{
	unsigned short i, q;
	q = size();
	for (i = 0; i < q; i++)
		if (!at(i).Initialize(MeasurementRate)) return false;
	return true;
};

//---------------------------------------------------------------------------
unsigned short __fastcall TArresters::GetQuantity(void)
{
	return size();
};

//---------------------------------------------------------------------------
void __fastcall TArresters::SetQuantity(unsigned short value)
{
	resize(value);
};

//---------------------------------------------------------------------------
void __fastcall TArresters::Add(TArrester & NewItem)
{
	push_back(NewItem);
};

//---------------------------------------------------------------------------
float __fastcall TArresters::Works(const unsigned short CutTrackNumber, const int CutNumber,
											  const float WagonSpeed, const float Start,
											  const float End, const float NowTime,
											  const TAxes Axes)
{
	float w = 0;
	float w1;
	unsigned short i, q;

	q = size();
	for (i = 0; i < q; i++)
	{
		w += at(i).Works(CutTrackNumber, CutNumber, WagonSpeed, Start, End, NowTime, Axes);
	}

	return w;
};

//---------------------------------------------------------------------------
void __fastcall TArrester::Load(const int Handle, const int FileBuild)
{
	unsigned i ,q;

	Index = ReadFloat(Handle);
	Model = ArresterList.Model(Index);
	Quantity = ReadFloat(Handle);
	ioPositions.resize(Quantity);
   if (FileBuild > 7) ioPositions.InstallMode.Index = ReadFloat(Handle);

	q = Quantity;
	for (i = 0; i < q; i++)
		ioPositions[i] = ReadFloat(Handle);
}

//---------------------------------------------------------------------------
void __fastcall TArrester::Save(const int Handle)
{
	unsigned short i, q;

	WriteFloat(Handle, ModelIndex);
	WriteFloat(Handle, Quantity);
	WriteFloat(Handle, ioPositions.InstallMode.Index);

	q = Quantity;
	for (i = 0; i < q; i++)
		WriteFloat(Handle, ioPositions[i]);
}

//---------------------------------------------------------------------------
void __fastcall TArresters::Load(const int Handle, const int FileBuild)
{
	unsigned short i, q, ii, qq;
	int Index;
	TArrester Arrester;

	q = ReadFloat(Handle);
//	resize(q);
	clear();
	for (i = 0; i < q; i++) {
//		at(i).Load(Handle, FileBuild);

		Index = ReadFloat(Handle);
		Arrester = ArresterList.Which(Index);
		Arrester.Quantity = ReadFloat(Handle);
		Arrester.ioPositions.resize(Arrester.Quantity);
		if (FileBuild > 7) Arrester.ioPositions.InstallMode.Index = ReadFloat(Handle);

//	q = Quantity;
		for (ii = 0; ii < Arrester.Quantity; ii++)
			Arrester.ioPositions[ii] = ReadFloat(Handle);
		push_back(Arrester);
	}
	return;
}

//---------------------------------------------------------------------------
void __fastcall TArresters::Save(const int Handle)
{
	unsigned short i, q;
	q = size();
	WriteFloat(Handle, q);
	for (i = 0; i < q; i++)
		at(i).Save(Handle);
}

void __fastcall TArresters::ResetIndex(void)
{
	for (int i = 0; i < size(); i++)
		at(i).Index = i;
	return;
}

TArrester __fastcall TArresters::Find(const AnsiString SerialNumber)
{
	TArrester A;
	for (int i = 0; i < size(); i++)
		if (at(i).SerialNumber == SerialNumber) return at(i);
	A.ioBeginPosition = -999;
	A.ioEndPosition = -999;
	A.ModelIndex = 0;
	MessageBoxA(NULL, "未找到相应的停车顶数据，该数据可能已经被删除！", "错误！", MB_OK + MB_ICONERROR);
	return A;
}

void __fastcall TArresters::WriteListView(TListView * ListView)
{
	int i, q;
	TListItem *Item;
	ListView->Clear();
	for (i = 0; i < size(); i++) {
		Item = ListView->Items->Add();
		Item->Caption = at(i).Name;
		Item->SubItems->Add(at(i).Model);
		Item->SubItems->Add(at(i).Quantity);
	}
	return;
}

//---------------------------------------------------------------------------
TArresters & __fastcall TArresters::operator = (const TArresters & t)
{
	unsigned short i, q;

	clear();
	q = t.size();
	for (i = 0; i < q; i++)
		push_back(t[i]);

	return *this;
}

//---------------------------------------------------------------------------
TArresterList & __fastcall TArresterList::operator = (const TArresterList & t)
{
	unsigned short i, q;

	q = t.size();
	for (i = 0; i < q; i++)
		push_back(t[i]);

	return *this;
}


//---------------------------------------------------------------------------
unsigned short __fastcall TArresterList::Index(const AnsiString Model)
{
	int i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).Model == Model)
		{
			return at(i).ModelIndex;
		}
	}
	return at(0).ModelIndex;
}

//---------------------------------------------------------------------------
AnsiString __fastcall TArresterList::Model(const unsigned short Index)
{
	int i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).ModelIndex == Index)
		{
			return at(i).Model;
		}
	}
	return at(0).Model;
}

//---------------------------------------------------------------------------
TArrester __fastcall TArresterList::Which(const AnsiString Model)
{
	int i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).Model == Model)
		{
			return at(i);
		}
	}
	return at(0);
}

//---------------------------------------------------------------------------
TArrester __fastcall TArresterList::Which(const unsigned short Index)
{
	int i, q;
	q = size();
	for (i = 0; i < q; i++)
	{
		if (at(i).ModelIndex == Index)
		{
			return at(i);
		}
	}
	MessageBoxA(NULL, "停车顶型号出现问题，请与软件作者联系！", "错误！", MB_OK + MB_ICONERROR);
	return at(0);
}

//---------------------------------------------------------------------------
TArrester __fastcall TArresterList::New(const AnsiString ModelName,
											  const unsigned short ModelIndex,
											  const float BaseWork,
											  const unsigned short WorkNumber,
											  const float ResistanceWork)
{
	TArrester Arrester;
	Arrester.ModelIndex = ModelIndex;
	Arrester.Model = ModelName;
	Arrester.BaseWork = BaseWork;
	Arrester.ResistanceWork = ResistanceWork;
	Arrester.WorkNumber = WorkNumber;

	return Arrester;
}

//---------------------------------------------------------------------------
__fastcall TArresterList::TArresterList()
{

	push_back(New("Not Exist", 0, 0, 0));
	push_back(New("T101", 1001, 0.102, 3021));
	push_back(New("T102", 1002, 0.086, 3021));
//	push_back(New("T104", 1003, 0.1, 1003));
	push_back(New("GST201", 2001, 0.102, 3021));
	push_back(New("GST202", 2002, 0.0765, 3021));
//	push_back(New("GST301", 3001, 0.1, 3001));
	push_back(New("T2000", 2003, 0.117, 8011));
}

//---------------------------------------------------------------------------
bool __fastcall TArresterList::Initialize(void)
{

}
