#ifndef MorphologyHolder_H
#define MorphologyHolder_H

#include "../common/utilit.h"
#include "../LemmatizerLib/PLMLineCollection.h"
#include "../GraphanLib/GraphmatFile.h"
#include "../AgramtabLib/RusGramTab.h"
#include "../AgramtabLib/GerGramTab.h"
#include "../AgramtabLib/EngGramTab.h"
#include "../AgramtabLib/rus_consts.h"
#include "../AgramtabLib/eng_consts.h"
#include "../AgramtabLib/ger_consts.h"

class CMorphologyHolder
{
public:
	bool							m_bTimeStatis;
	MorphLanguageEnum				m_CurrentLanguage;
	CPlmLineCollection				m_PlmLines;
	CAgramtab*						m_pGramTab;
	CLemmatizer*					m_pLemmatizer;
	CGraphmatFile					m_Graphan;

	CMorphologyHolder();
	~CMorphologyHolder();

	bool GetMorphology(std::string str, bool bFile, int& CountOfWords);
    bool LoadLemmatizer(MorphLanguageEnum langua);
	bool LoadGraphanAndLemmatizer(MorphLanguageEnum langua);
	void DeleteProcessors();
	DwordVector GetParadigmIdsByNormAndAncode(std::string &str, const std::string &code) const;
	void		string_to_ids(const char *str, DwordVector &ids, bool bNorm) const;
	std::string		id_to_string(long id) const;
	CFormInfo		id_to_paradigm(long id) const;
};



#endif
