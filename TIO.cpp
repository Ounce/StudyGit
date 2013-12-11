//---------------------------------------------------------------------------


#pragma hdrstop

#include "TIO.h"
#include "CoFunction.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
TIOCaption & __fastcall TIOCaptions::operator [] (const int Index)
{
	return at(Index);
}

void __fastcall TIOCaptions::AddItem(TIOCaption Item)
{
	push_back(Item);
}

int __fastcall TIOCaptions::GetIndex(const AnsiString Caption)
{
	int i, q;
	for (i = 0; i < size(); i++) {
		if (at(i).ChineseCaption == Caption || at(i).EnglishCaption == Caption) {
			return i;
		}
	}
	return -1;
}

AnsiString __fastcall TIOCaption::GetCaption(const eLanguage Language)
{
	switch (Language) {
;
	case English :
		return EnglishCaption;
		break;
	case Chinese :
		break	default:
		return ChineseCaption;
	};
}

//---------------------------------------------------------------------------
__fastcall TIO::TIO()
{

};

//---------------------------------------------------------------------------
void __fastcall TIO::SetMeasurement(const int Measurement)
{
/*	switch (Measurement) {
	case BritishMeasurement:
		switch (MeasurementType) {
		case Length:
			MeasurementRate = 0.3048;
			break;
		case Speed:
			MeasurementRate = 0.4444;
			break;
		case Grade:
			MeasurementRate = 0.1;
			break;
		default:
			;
		}
	case MetricMeasurement:
		MeasurementRate = 1;
	default:
		;
	}   */
}

//---------------------------------------------------------------------------
void __fastcall TIO::Save(const int Handle)
{
	WriteFloat(Handle, Value);
	return;
}

//---------------------------------------------------------------------------
void __fastcall TIO::Load(const int Handle, const eMeasurement Measurement)
{
	Value = ReadFloat(Handle);
	switch (Measurement) {
	case MetricMeasurement:
		MetricValue = Value;
		break;
	case BritishMeasurement:
		MetricValue = Value * MeasurementRate;
		break;
	default:
		;
	}
}

//---------------------------------------------------------------------------
__fastcall TMeasurementRate::TMeasurementRate()
{
	FMeasurement = MetricMeasurement;
	Length = 1;
	Speed = 1;
	Grade = 1;
	Weight = 1;
}

//---------------------------------------------------------------------------
void __fastcall TMeasurementRate::SetMeasurement(const eMeasurement NewMeasurement)
{
	FMeasurement = NewMeasurement;
	switch (NewMeasurement) {
	case MetricMeasurement:
		Length = 1;
		Speed = 1;
		Grade = 1;
		Weight = 1;
		break;
	case BritishMeasurement:
		Length = 0.3048;
		Speed = 0.4444;
		Grade = 10;
		Weight = 0.9072;
		break;
	default:
		;
	}
	return;
}


//---------------------------------------------------------------------------
__fastcall TItemCaption::TItemCaption()
{
}

void __fastcall TItemCaption::SetCaption(const eMeasurementType MeasurementType,
													  const AnsiString NewChineseCaption,
													  const AnsiString NewEnglishCaption)
{
	switch (MeasurementType) {
		case uLength:
			MetricUnitName = "(m)";
			BritishUnitName = "(ft)";
			break;
		case uWeight:
			MetricUnitName = "(T)";
			BritishUnitName = "(ST)";
			break;
		case uSpeed:
			MetricUnitName = "(m/s)";
			BritishUnitName = "(mph)";
			break;
		case uGrade:
			MetricUnitName = "(бы)";
			BritishUnitName = "(%)";
			break;
	}
	ChineseCaption = NewChineseCaption;
	EnglishCaption = NewEnglishCaption;
	return;
}

AnsiString __fastcall TItemCaption::GetUnitName(const eMeasurement Measurement)
{
	switch (Measurement) {
		case MetricMeasurement:
			return MetricUnitName;
		case BritishMeasurement:
			return BritishUnitName;
	}
}
