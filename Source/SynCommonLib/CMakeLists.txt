declare_cmake_min_version()

project(SynCommonLib)

add_library(SynCommonLib
BuildInitialClauses.cpp
FindTermins.cpp
Sentence.cpp
ThesaurusForSyntax.cpp
Clause.cpp
Group.cpp
SynPlmLine.cpp
Word.cpp
ClauseCollection.cpp
CoverageKillHomonyms.cpp
FormatCaller.cpp
GLRFormats.cpp
MorphVariant.cpp
RelationsIterator.cpp
SyntaxInit.cpp
oborot.cpp
)

target_link_libraries(SynCommonLib
    LemmatizerLib
    GerPostMorph
    MAPostLib
    SimpleGrammarLib
)

