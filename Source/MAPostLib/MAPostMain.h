// ==========  This file is under  LGPL, the GNU Lesser General Public Licence
// ==========  Dialing Posmorphological Module (www.aot.ru)
// ==========  Copyright by Dmitry Pankratov, Alexey Sokirko (1999-2002)


#ifndef __MAPOST_MAIN_H_
#define __MAPOST_MAIN_H_



#include "../common/util_classes.h"
#include "../common/PlmLine.h"       
#include "../MAPostLib/PostMorphInterface.h" 
#include "../MAPostLib/PostLemWord.h" 


#include "../LemmatizerLib/PLMLineCollection.h"
#include "../LemmatizerLib/Lemmatizers.h"
#include "../AgramtabLib/rus_consts.h"
#include "../TrigramLib/TrigramModel.h"
#include "list"       

const char g_strAgramTabRegPath[] = "Software\\Dialing\\Lemmatizer\\Russian\\Agramtab";


struct CFixedColloc
{
	std::string		   m_LemmaStr;
	struct CLemmaAndPOS {
		std::string m_Lemma;
		BYTE   m_POS;
	};
	vector<CLemmaAndPOS> m_Lemmas;
	long		   m_MainWordNo;
	std::string		   m_InterfaceString;
	CFixedColloc(std::string LemmaStr,	long MainWordNo,	std::string InterfaceString,  const CAgramtab* m_piRusGramTab);
	CFixedColloc()
	{
		m_MainWordNo = -1;
	};

};


struct CSurnameSuffix {
	std::string m_Suffix;
	std::string m_GramCode;
	int    m_ParadigmNo;
};

struct CLemmaAndCodes {
	std::string m_Lemma;
	std::string m_GramCodes;
};



typedef list<CPostLemWord> LineCollection ;

typedef LineCollection::iterator CLineIter;
typedef LineCollection::const_iterator CConstLineIter;

typedef CSmallVector<CLemmaAndCodes, 20> SurnameHypotsVec;
struct CFIOFormat;

class CMAPost  : public CPostMorphInteface
{
	//грамматический код ДУРНОВО (неизменяеммое существительное всех родов)
	std::string          m_DURNOVOGramCode;
	list<CPostLemWord>	m_Words;
    

public:
	CMAPost();
	~CMAPost();
public:
	
    
    bool    LoadWords(const CPlmLineCollection *piInTextItems);
	bool	ProcessData(const CPlmLineCollection *piInTextItems);
	bool	Init(const CLemmatizer* RusLemmatizer, const CAgramtab* RusGramTab);
	CLineIter Remove(CLineIter it, bool bRemoveSpaceAfterDeletedWord);
    CLineIter PassSpaces(CLineIter it);
    CLineIter BackSpaces(CLineIter it);
    CLineIter NextNotSpace(CLineIter it);


protected:
	const CLemmatizer*			m_pRusLemmatizer;
	const CAgramtab*			m_pRusGramTab;
	vector<CFixedColloc>        m_FixedCollocs;
    CTrigramModel               m_TrigramModel;
	bool                        m_bUseTrigrams;

	

	std::string			m_LogFileName;

	

	void RunRules();
	int Count() const	{ return m_Words.size(); };

	std::string		GetSimilarNumAncode (const std::string&  Lemma, const std::string&  Flexia, bool IsNoun);
	bool		HasParadigmOfFormAndPoses(std::string WordForm, poses_mask_t Poses) const;
	bool		NounHasObviousPluralContext(CLineIter it);
    

	

protected: 
	//rules
	void Odnobuk();
	void Cifrdef();
	void ILeDefLe();
	void Memlem();
	void ParticipleAndVerbInOneForm();
	void PronounP_Pronoun_Homonymy();
	void FixedCollocations();
	bool ReadCollocs();
	void CorrectOborots();
	void SemiAdjectives();
	void SemiNouns();
	void Rule_UZHE();
	void Rule_Ideclinable();
	void Rule_DeadPlurals();
	void Rule_RelationalAdjective();
	void Rule_ExpandIndeclinableGramcodes();
	void OtherRules();
	
	std::string GetNormSurnameSuffix(long ParadigmNo) const;
	void Rule_QuoteMarks();
	void Rule_ILE();
	void Rule_KAK_MOZHNO();
	void Rule_Redublication();
	void Rule_CHTO_ZA();
	void Rule_VOT_UZHE();
	void Rule_Fio();

	bool CanBeDubleDelimiter(CLineIter it);
	void InsertComma(CLineIter it);
	void Rule_UnknownNames();
	void Rule_SOROK();
	void Rule_Abbreviation();
	// по-восточному
	void Rule_AdverbFromAdjectives();
	void log(std::string s);
	void SaveToFile(std::string s);
	CLineIter AddCollocation(CLineIter start_it, CLineIter end_it, CLineIter main_it, bool HasEndtSent,  int CollocNo);
	void Rule_FilterProperName();
	void Rule_ChangePatronymicLemmas();
	void Rule_Interjections();
    bool FilterPostMorphWords();
    bool FilterOnePostLemWord(CPostLemWord& W, WORD tagid, WORD tagid2) const;
    void Rule_TwoPredicates();
    void SolveAmbiguityUsingRuleForTwoPredicates(CLineIter start, CLineIter end);
    bool SetFioFormat (const CFIOFormat* Format, CLineIter it); 

};






#endif //__MAPOST_H_



