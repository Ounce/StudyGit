//---------------------------------------------------------------------------

#ifndef TArresterH
#define TArresterH

#include "TRetarder.h"


//---------------------------------------------------------------------------

class TArrester : public TRetarder
{
private:
   AnsiString FPistonModel;
   unsigned short FPistonWorkIndex;

protected:
public:
	TRetarderPositions ioPositions;
   __property AnsiString PistonModel = { read=FPistonModel, write=FPistonModel };
   __property unsigned short PistonWorkIndex = { read=FPistonWorkIndex, write=FPistonWorkIndex };

   TArrester & __fastcall operator = (const TArrester & t);
   TArrester & __fastcall operator = (const AnsiString ModelName);

   __fastcall TArrester();
	bool __fastcall Initialize(const TMeasurementRate MeasurementRate);

	float __fastcall Works(const unsigned short CutTrackNumber, const int CutNumber,
											const float WagonSpeed, const float Start, const float End,
											const float NowTime, const TAxes Axes);
	float __fastcall Work(const float WagonSpeed, const float WheelRadii, const float FlangeHeight, float &ak9);
   void __fastcall Load(const int Handle, const int FileBuild);
   void __fastcall Save(const int Handle);   
};



//---------------------------------------------------------------------------
class TArresterList : public vector<TArrester>
{
private:
protected:
public:
	__fastcall TArresterList();
	TArresterList & __fastcall operator = (const TArresterList & t);
	bool __fastcall Initialize(void);
	TArrester __fastcall New(const AnsiString Model, const unsigned short Index,
									 const float BaseWork, const unsigned short WorkNumber,
									 const float ResistanceWork = 0.005);
	unsigned short __fastcall Index(const AnsiString Model);
	AnsiString __fastcall Model(const unsigned short Index);
	TArrester __fastcall Which(const AnsiString Model);
	TArrester __fastcall Which(const unsigned short Index);
};


//---------------------------------------------------------------------------
class TArresters : public vector<TArrester>
{
private:
   unsigned short __fastcall GetQuantity(void);
   void __fastcall SetQuantity(unsigned short value);

public:
	TItemCaption StopPointCaption, PositionCaption;
	__fastcall TArresters();
   __property unsigned short Quantity = { read=GetQuantity, write=SetQuantity };

	bool __fastcall VerifyInput(const AnsiString ModelText,
										 const AnsiString QuantityText,
										 const AnsiString StopPointText);
	bool __fastcall Initialize(const TMeasurementRate MeasurementRate);
	float __fastcall Works(const unsigned short CutTrackNumber, const int CutNumber,
								  const float WagonSpeed, const float Start, const float End,
								  const float NowTime, const TAxes Axes);
   void __fastcall Add(TArrester & NewItem);
   void __fastcall Load(const int Handle, const int FileBuild);
   void __fastcall Save(const int Handle);
	void __fastcall ResetIndex(void);
	TArrester __fastcall Find(const AnsiString SerialNumber);
   void __fastcall WriteListView(TListView * ListView);

   TArresters & __fastcall operator = (const TArresters & t);
};


class TArrestersList : public vector<TArresters>
{

};


#endif
