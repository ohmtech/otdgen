##############################################################################
#
#     src.gypi
#     Copyright (c) 2015 Raphael DINGE
#
#Tab=3########################################################################



{
   'sources':
   [
      # include/
      '../include/otdgen/Central.h',
      '../include/otdgen/Conf.h',
      '../include/otdgen/DocBlock.h',
      '../include/otdgen/DocBlock.hpp',
      '../include/otdgen/DocBlocks.h',
      '../include/otdgen/DocBook.h',
      '../include/otdgen/DocCartouche.h',
      '../include/otdgen/DocChapter.h',
      '../include/otdgen/DocCodeBlock.h',
      '../include/otdgen/DocInformation.h',
      '../include/otdgen/DocInline.h',
      '../include/otdgen/DocLibrary.h',
      '../include/otdgen/DocList.h',
      '../include/otdgen/DocMember.h',
      '../include/otdgen/DocParagraph.h',
      '../include/otdgen/DocParameter.h',
      '../include/otdgen/DocSection.h',
      '../include/otdgen/DocTable.h',
      '../include/otdgen/DocType.h',
      '../include/otdgen/Error.h',
      '../include/otdgen/Expression.h',
      '../include/otdgen/GeneratorBase.h',
      '../include/otdgen/GeneratorGitHubMarkDown.h',
      '../include/otdgen/GeneratorHtml.h',
      '../include/otdgen/GeneratorPlainText.h',
      '../include/otdgen/LexicalAnalyser.h',
      '../include/otdgen/SyntaxicAnalyser.h',
      '../include/otdgen/SyntaxicAnalyser.hpp',
      '../include/otdgen/StructuralAnalyser.h',
      '../include/otdgen/Toc.h',
      '../include/otdgen/Token.h',
      '../include/otdgen/sqlite3.h',
      '../include/otdgen/sqlite3ext.h',

      # src/
      'Central.cpp',
      'Conf.cpp',
      'DocBlocks.cpp',
      'DocBook.cpp',
      'DocChapter.cpp',
      'Error.cpp',
      'Expression.cpp',
      'GeneratorBase.cpp',
      'GeneratorGitHubMarkDown.cpp',
      'GeneratorHtml.cpp',
      'GeneratorPlainText.cpp',
      'LexicalAnalyser.cpp',
      # 'main.cpp'
      'SyntaxicAnalyser.cpp',
      'StructuralAnalyser.cpp',
      'Toc.cpp',
      'Token.cpp',
      'SQLite3Wrap.c',
   ],
}
