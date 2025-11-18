#ifndef PROPOSITION_H
#define PROPOSITION_H

/*
 * 1  bit	négation
 * 63 bits	identification
 *
 * MSB                         LSB
 * 0          1                64
 * +----------+----------------+
 * | négation | identification |
 * +----------+----------------+
 */

typedef unsigned long long int uint64;
typedef uint64  Premise_t;
typedef uint64	Conclusion_t;

typedef enum FactBase : Premise_t 
{
	Empty			= 0ULL,
	ReservoirEssencePlein 	= 1ULL,
	ClignotantsFonctionnent	= 2ULL,
	EssuieGlaceFonctionnent	= 3ULL,
	PharesFonctionnent	= 4ULL,
	ReservoirAntiGelPlein	= 5ULL,
	ChauffageFonctionne	= 6ULL,
	ClimatisationFonctionne	= 7ULL,
	MoteurFonctionne	= 8ULL,
	MAX_FACT = 1ULL << 63,

} FactBase;

static inline uint64 not(const Premise_t p) { return p ^ (1ULL << 63); }
static inline bool is_not(const Premise_t p) { return (p >> 63) & 1ULL; }

const char* to_str(const FactBase fact);

#endif //PROPOSITION_H
