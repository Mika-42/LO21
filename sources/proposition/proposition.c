#include "proposition.h"

const char* to_str(const FactBase fact)
{ 
	switch(fact) 
	{
		case Empty                  : return "Empty";
		case ReservoirEssencePlein  : return "ReservoirEssencePlein";
		case ClignotantsFonctionnent: return "ClignotantsFonctionnent";
		case EssuieGlaceFonctionnent: return "EssuieGlaceFonctionnent";
		case PharesFonctionnent     : return "PharesFonctionnent";
		case ReservoirAntiGelPlein  : return "ReservoirAntiGelPlein";
		case ChauffageFonctionne    : return "ChauffageFonctionne";
		case ClimatisationFonctionne: return "ClimatisationFonctionne";
		case MoteurFonctionne       : return "MoteurFonctionne";
		default: return "unknow";
	}
}

