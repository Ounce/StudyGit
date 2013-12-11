//---------------------------------------------------------------------------

#ifndef TIOH
#define TIOH
#include <ComCtrls.hpp>
#include <vector.h>


//---------------------------------------------------------------------------
enum eLanguage {Chinese = 0, English};
enum eMeasurement { MetricMeasurement = 0, BritishMeasurement };
enum eMeasurementType {uLength, uSpeed, uGrade, uWeight};
//enum eUnitType {Length, Weight, Speed};


class TIOCaption
{
public:
	int Index;
	AnsiString ChineseCaption;
	AnsiString EnglishCaption;
	AnsiString __fastcall GetCaption(const eLanguage Language);
};

class TIOCaptions : public vector<TIOCaption>
{
public:
	TIOCaption & __fastcall operator [] (const int Index);
	void __fastcall AddItem(TIOCaption IOCaption);
	int __fastcall GetIndex(const AnsiString Caption);
	__property int Size = { read=size, write=resize };
};

//---------------------------------------------------------------------------
class TIO
{
public:
	float Value;
	float MeasurementRate;
	float MetricValue;
	TIOCaption CaptionName;
	TIOCaption MeasurementName;

	__fastcall TIO();
	void __fastcall SetMeasurement(const int Measurement);
	void __fastcall SetMeasurementType(const eMeasurementType MeasurementType);
	void __fastcall Save(const int Handle);
	void __fastcall Load(const int Handle, eMeasurement);
};

class TMeasurementRate
{
public:
	float Length;
	float Speed;
	float Grade;
	float Weight;
	__fastcall TMeasurementRate();
	__property eMeasurement Measurement = { read=FMeasurement, write=SetMeasurement };
private:
	eMeasurement FMeasurement;
	void __fastcall SetMeasurement(const eMeasurement NewMeasurement);
};


class TItemCaption
{
public:
	AnsiString ChineseCaption, EnglishCaption;
	AnsiString BritishUnitName, MetricUnitName;
	__fastcall TItemCaption();
	AnsiString __fastcall GetCaption(const eLanguage Language);
	AnsiString __fastcall GetUnitName(const eMeasurement Measurement);
	void __fastcall SetCaption(const eMeasurementType MeasurementType,
										const AnsiString NewChineseCaption,
	                           const AnsiString NewEnglishCaption);
};


#endif
