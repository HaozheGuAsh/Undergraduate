// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sql_parser.hpp"

// User implementation prologue.

#line 51 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:407
// Unqualified %code blocks.
#line 30 "sql_parser.yy" // lalr1.cc:408

   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "sql_driver.h"
   #include "sql_expr.h"
   #include "sql_scanner.h"

#undef yylex
#define yylex scanner.yylex

    char linebuf[500];

#line 69 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:408


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "sql_parser.yy" // lalr1.cc:474
namespace UCD {
#line 155 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  SQLParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  SQLParser::SQLParser (UCD::SQLScanner  &scanner_yyarg, UCD::SQLDriver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  SQLParser::~SQLParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  SQLParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  SQLParser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  SQLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  SQLParser::by_type::by_type ()
     : type (empty)
  {}

  inline
  SQLParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  SQLParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  SQLParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  SQLParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  SQLParser::by_state::by_state ()
    : state (empty)
  {}

  inline
  SQLParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  SQLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  SQLParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  SQLParser::symbol_number_type
  SQLParser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  SQLParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  SQLParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  SQLParser::stack_symbol_type&
  SQLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  SQLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 5: // "string"

#line 96 "sql_parser.yy" // lalr1.cc:599
        { delete (yysym.value.str); }
#line 375 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:599
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  SQLParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  SQLParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  SQLParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  SQLParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SQLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SQLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SQLParser::debug_level_type
  SQLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SQLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline SQLParser::state_type
  SQLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  SQLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SQLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SQLParser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 113 "sql_parser.yy" // lalr1.cc:847
    { YYACCEPT; }
#line 617 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 114 "sql_parser.yy" // lalr1.cc:847
    { YYABORT; }
#line 623 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 119 "sql_parser.yy" // lalr1.cc:847
    {   driver.evalexpr(driver.optimize(driver.compile(driver.cvt_itoe(driver.makeexpr(OP_INSERTROW, 2, (yystack_[5].value.num), (yystack_[2].value.num))))));
		    (yylhs.value.num)=0;
		    driver.clear();
		}
#line 632 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 5:
#line 124 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "Multi-row insert not implemented yet\n";
		    driver.clear();
		}
#line 640 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 128 "sql_parser.yy" // lalr1.cc:847
    {   driver.print_relation(driver.evalexpr(driver.optimize(driver.compile(driver.cvt_itoe((yystack_[1].value.num))))));
		    driver.clear();
		}
#line 648 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 132 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "UPDATE not implemented yet\n";
		    driver.clear();
		}
#line 656 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 136 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "DELETE not implemented yet\n";
		    driver.clear();
		}
#line 664 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 140 "sql_parser.yy" // lalr1.cc:847
    {   driver.evalexpr(driver.optimize(driver.compile(driver.cvt_itoe(driver.makeexpr(OP_CREATETABLE, 2, (yystack_[4].value.num), (yystack_[2].value.num))))));
		    (yylhs.value.num)=0;
		    driver.clear();
		}
#line 673 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 145 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "DESCRIBE not implemented yet\n";
		    driver.clear();
		}
#line 681 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 149 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "SHOW TABLES not implemented yet\n";
		    driver.clear();
		}
#line 689 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 153 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "DROP TABLE not implemented yet\n";
		    driver.clear();
		}
#line 697 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 157 "sql_parser.yy" // lalr1.cc:847
    {   driver.clear(); YYACCEPT; }
#line 703 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 160 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.setname(OP_TABLENAME, (yystack_[0].value.str)); }
#line 709 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 162 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "Invalid tablename\n"; driver.clear(); YYACCEPT; }
#line 715 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 165 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.setname(OP_COLNAME, (yystack_[0].value.str)); }
#line 721 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 167 "sql_parser.yy" // lalr1.cc:847
    {   std::cout << "Invalid column name\n"; driver.clear(); YYACCEPT; }
#line 727 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 171 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr((yystack_[1].value.num), 2, (yystack_[2].value.num), (yystack_[0].value.num)); }
#line 733 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 172 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr((yystack_[3].value.num), 2, (yystack_[4].value.num), (yystack_[1].value.num)); }
#line 739 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 173 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr((yystack_[3].value.num), 2, (yystack_[4].value.num), (yystack_[1].value.num)); }
#line 745 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 174 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[1].value.num); }
#line 751 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 175 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[1].value.num); }
#line 757 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 176 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 763 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 179 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_FCALL, 2, driver.setname(OP_FNAME, (yystack_[3].value.str)), (yystack_[1].value.num)); }
#line 769 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 180 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_FCALL, 2, driver.setname(OP_FNAME, (yystack_[2].value.str)), 0); }
#line 775 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 183 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), 0); }
#line 781 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 184 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), (yystack_[2].value.num)); }
#line 787 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 187 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.setname(OP_COLNAME, (yystack_[0].value.str)); }
#line 793 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 188 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makenum((yystack_[0].value.num)); }
#line 799 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 189 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makestrexpr((yystack_[0].value.str)); }
#line 805 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 194 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[4].value.num);
		  if((yystack_[3].value.num)) (yylhs.value.num) = driver.makeexpr(OP_SELECTION, 2, (yylhs.value.num), (yystack_[3].value.num));
		  if((yystack_[2].value.num)) (yylhs.value.num) = driver.makeexpr(OP_GROUP, 2, (yylhs.value.num), (yystack_[2].value.num));
		  (yylhs.value.num) = driver.makeexpr(OP_PROJECTION, 2, (yylhs.value.num), (yystack_[6].value.num));
		  if((yystack_[1].value.num)) (yylhs.value.num) = driver.makeexpr(OP_SELECTION, 2, (yylhs.value.num), (yystack_[1].value.num));
		  if((yystack_[0].value.num)) (yylhs.value.num) = driver.makeexpr(OP_SORT, 2, (yylhs.value.num), (yystack_[0].value.num));
		}
#line 817 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 203 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = 0; }
#line 823 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 204 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 829 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 207 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = 0; }
#line 835 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 208 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 841 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 211 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = 0; }
#line 847 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 212 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 853 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 215 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), 0); }
#line 859 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 216 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), (yystack_[2].value.num)); }
#line 865 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 222 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = 0; }
#line 871 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 223 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 877 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 226 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), 0); }
#line 883 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 227 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), (yystack_[2].value.num)); }
#line 889 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 230 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, (yystack_[0].value.num), 0); }
#line 895 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 231 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, (yystack_[1].value.num), 0); }
#line 901 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 232 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, (yystack_[1].value.num), driver.makeexpr(OP_NULL, 0, 0, 0)); }
#line 907 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 233 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, driver.setname(OP_COLNAME, (yystack_[0].value.str)), 0); }
#line 913 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 234 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, driver.setname(OP_COLNAME, (yystack_[1].value.str)), 0); }
#line 919 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 235 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_SORTSPEC, 2, driver.setname(OP_COLNAME, (yystack_[1].value.str)), driver.makeexpr(OP_NULL, 0, 0, 0)); }
#line 925 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 238 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), 0); }
#line 931 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 239 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), (yystack_[2].value.num)); }
#line 937 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 242 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_OUTCOLNAME, 2, (yystack_[2].value.num), (yystack_[0].value.num)); }
#line 943 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 243 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_OUTCOLNAME, 2, (yystack_[0].value.num), (yystack_[0].value.num)); }
#line 949 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 246 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = (yystack_[0].value.num); }
#line 955 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 247 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_PRODUCT, 2, (yystack_[2].value.num), (yystack_[0].value.num)); }
#line 961 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 250 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makenum((yystack_[0].value.num)), 0); }
#line 967 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 251 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makestrexpr((yystack_[0].value.str)), 0); }
#line 973 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 252 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makeexpr(OP_NULL,0,0, 0), 0); }
#line 979 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 253 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makenum((yystack_[0].value.num)), (yystack_[2].value.num)); }
#line 985 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 254 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makestrexpr((yystack_[0].value.str)), (yystack_[2].value.num)); }
#line 991 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 255 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, driver.makeexpr(OP_NULL, 0, 0, 0), (yystack_[2].value.num)); }
#line 997 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 256 "sql_parser.yy" // lalr1.cc:847
    { std::cout << "Unterminated string detected.\n"; driver.clear(); YYACCEPT; }
#line 1003 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 259 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), 0); }
#line 1009 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 260 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_RLIST, 2, (yystack_[0].value.num), (yystack_[2].value.num)); }
#line 1015 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 263 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_COLUMNDEF, 2, (yystack_[0].value.num), 0); }
#line 1021 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 264 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_COLUMNDEF, 2, (yystack_[1].value.num), 1); }
#line 1027 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 265 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = driver.makeexpr(OP_COLUMNDEF, 2, (yystack_[2].value.num), 3); }
#line 1033 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 268 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_EQUAL; }
#line 1039 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 269 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_NOTEQ; }
#line 1045 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 270 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_GT; }
#line 1051 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 271 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_LT; }
#line 1057 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 272 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_GEQ; }
#line 1063 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 273 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_LEQ; }
#line 1069 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 274 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_PLUS; }
#line 1075 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 275 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_BMINUS; }
#line 1081 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 276 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_TIMES; }
#line 1087 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 277 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_DIVIDE; }
#line 1093 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 278 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_AND; }
#line 1099 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;

  case 81:
#line 279 "sql_parser.yy" // lalr1.cc:847
    { (yylhs.value.num) = OP_OR; }
#line 1105 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
    break;


#line 1109 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  SQLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  SQLParser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char SQLParser::yypact_ninf_ = -44;

  const signed char SQLParser::yytable_ninf_ = -17;

  const short int
  SQLParser::yypact_[] =
  {
     113,   -28,    10,    26,    28,    50,    40,    28,    46,    56,
      39,    85,   -44,    44,   -44,    54,    19,   -44,   -44,    63,
     -44,     0,   -44,   -44,     8,   -44,    28,    62,   -44,    82,
      28,    28,    66,    87,    28,   -44,   -44,   -44,   -44,    20,
      88,   111,    75,    90,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,    35,    28,    10,    -3,
     -44,    90,   118,    91,   -44,   -44,    94,   -44,   187,    55,
     -44,   -44,   -44,   -44,   -44,    63,   -44,   -44,    27,   -44,
      96,   100,    99,    51,    90,   -44,   -44,    51,   130,    89,
      51,    28,   137,    77,   -44,    51,   149,    69,    71,   -44,
     187,   -44,   -44,   187,   -44,   138,   136,   -44,   -44,   -44,
     -44,    74,    76,   -44,   120,   -44,   115,    90,    90,    51,
     153,   128,    84,    51,   -44,   -44,   -44,   -44,   125,   -44,
     187,   158,   -44,   -44,   -44,   -44,   -44,   168,    90,     6,
     -44,   -44,   -10,     4,   127,   -44,   -44,   -44,   -44,   -44,
       6,   -44
  };

  const unsigned char
  SQLParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,    13,     0,    29,    30,    31,     0,
      55,     0,    24,    18,     0,    52,     0,     0,    14,     0,
       0,     0,     0,     0,     0,     3,     1,     6,    17,     0,
      29,     0,     0,     0,    71,    74,    75,    80,    81,    70,
      72,    73,    76,    77,    78,    79,     0,     0,     0,     0,
      15,     0,     0,     0,    10,    11,     0,    26,    27,     0,
      23,    22,    16,    54,    29,     0,    19,    56,    33,    53,
       0,     0,     0,     0,     0,    12,    25,     0,     0,     0,
       0,     0,    37,     0,     5,     0,     0,    67,     0,    65,
      28,    20,    21,    34,    57,     0,    35,    64,    58,    59,
      60,     0,     0,     8,     0,    68,     0,     0,     0,     0,
      42,     0,     0,     0,    69,     9,    66,    41,    38,    39,
      36,     0,    32,     4,    61,    62,    63,     0,     0,     0,
       7,    40,    46,    49,    43,    44,    47,    48,    50,    51,
       0,    45
  };

  const short int
  SQLParser::yypgoto_[] =
  {
     -44,   -44,   -44,    -4,   -43,   -18,   -44,   -44,   131,   -17,
     -44,   -44,   -44,   -44,    36,   -44,   -44,    38,   -44,   132,
     -44,   -44,   -44,    92,   -44
  };

  const short int
  SQLParser::yydefgoto_[] =
  {
      -1,    11,    12,    29,    20,    21,    22,    69,    23,    13,
      92,   120,   106,   128,   129,   132,   144,   145,    24,    25,
      78,   111,    98,    99,    56
  };

  const short int
  SQLParser::yytable_[] =
  {
      73,    41,    42,    32,     2,   146,   147,    15,    43,    72,
     142,    15,    14,    16,    17,    18,    80,    57,    82,   148,
     149,    68,    59,    40,    17,    18,    62,    63,   -16,    27,
      66,    28,    44,    45,    46,    47,    48,    90,    74,    17,
      18,    97,    81,    49,    26,    50,    51,    52,    53,    54,
      55,    19,    58,    77,    40,    17,    18,    88,    89,    30,
      39,    19,    67,   -16,    31,    96,    40,    17,    18,   100,
       2,    91,   103,    33,    97,   127,    75,   112,   107,    35,
      34,   108,   109,   110,    37,    36,   123,   104,   134,   135,
     136,    15,    19,    72,    38,   127,   143,    86,   114,    87,
     115,   130,    60,    61,    19,   137,    64,   143,    44,    45,
      46,    47,    48,   116,     1,   117,   121,    71,   122,    49,
       2,    50,    51,    52,    53,    54,    55,    65,    83,    39,
       3,   102,    84,     4,    85,     5,     6,    93,     7,     8,
      94,     9,    95,    44,    45,    46,    47,    48,   105,   119,
     118,   124,    10,    70,    49,   125,    50,    51,    52,    53,
      54,    55,    44,    45,    46,    47,    48,   131,   133,   138,
     139,   150,   101,    49,   141,    50,    51,    52,    53,    54,
      55,    44,    45,    46,    47,    48,     0,    76,   151,   113,
      79,     0,    49,     0,    50,    51,    52,    53,    54,    55,
      44,    45,    46,    47,    48,     0,     0,     0,   140,   126,
       0,    49,     0,    50,    51,    52,    53,    54,    55,    44,
      45,    46,    47,    48,     0,     0,     0,     0,     0,     0,
      49,     0,    50,    51,    52,    53,    54,    55
  };

  const short int
  SQLParser::yycheck_[] =
  {
      43,    19,    19,     7,     7,    15,    16,     1,     8,     3,
       4,     1,    40,     3,     4,     5,    19,     9,    61,    15,
      16,    39,    26,     3,     4,     5,    30,    31,     9,     1,
      34,     3,    32,    33,    34,    35,    36,    10,     3,     4,
       5,    84,    59,    43,    18,    45,    46,    47,    48,    49,
      50,    41,    44,    57,     3,     4,     5,    75,    75,     9,
      41,    41,    42,    44,    24,    83,     3,     4,     5,    87,
       7,    44,    90,    27,   117,   118,    41,    95,     1,    40,
      24,     4,     5,     6,    40,     0,    10,    91,     4,     5,
       6,     1,    41,     3,    40,   138,   139,    42,    29,    44,
      31,   119,    40,    21,    41,   123,    40,   150,    32,    33,
      34,    35,    36,    42,     1,    44,    42,    42,    44,    43,
       7,    45,    46,    47,    48,    49,    50,    40,    10,    41,
      17,    42,    41,    20,    40,    22,    23,    41,    25,    26,
      40,    28,    43,    32,    33,    34,    35,    36,    11,    13,
      12,    31,    39,    42,    43,    40,    45,    46,    47,    48,
      49,    50,    32,    33,    34,    35,    36,    14,    40,    44,
      12,    44,    42,    43,   138,    45,    46,    47,    48,    49,
      50,    32,    33,    34,    35,    36,    -1,    56,   150,    40,
      58,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    40,   117,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50
  };

  const unsigned char
  SQLParser::yystos_[] =
  {
       0,     1,     7,    17,    20,    22,    23,    25,    26,    28,
      39,    52,    53,    60,    40,     1,     3,     4,     5,    41,
      55,    56,    57,    59,    69,    70,    18,     1,     3,    54,
       9,    24,    54,    27,    24,    40,     0,    40,    40,    41,
       3,    56,    60,     8,    32,    33,    34,    35,    36,    43,
      45,    46,    47,    48,    49,    50,    75,     9,    44,    54,
      40,    21,    54,    54,    40,    40,    54,    42,    56,    58,
      42,    42,     3,    55,     3,    41,    59,    54,    71,    70,
      19,    60,    55,    10,    41,    40,    42,    44,    56,    60,
      10,    44,    61,    41,    40,    43,    56,    55,    73,    74,
      56,    42,    42,    56,    54,    11,    63,     1,     4,     5,
       6,    72,    56,    40,    29,    31,    42,    44,    12,    13,
      62,    42,    44,    10,    31,    40,    74,    55,    64,    65,
      56,    14,    66,    40,     4,     5,     6,    56,    44,    12,
      40,    65,     4,    55,    67,    68,    15,    16,    15,    16,
      44,    68
  };

  const unsigned char
  SQLParser::yyr1_[] =
  {
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75
  };

  const unsigned char
  SQLParser::yyr2_[] =
  {
       0,     2,     1,     2,     8,     5,     2,     9,     6,     7,
       3,     3,     4,     2,     1,     2,     1,     2,     1,     3,
       5,     5,     3,     3,     1,     4,     3,     1,     3,     1,
       1,     1,     8,     0,     2,     0,     2,     0,     3,     1,
       3,     1,     0,     3,     1,     3,     1,     2,     2,     1,
       2,     2,     1,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     3,     3,     1,     1,     3,     1,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SQLParser::yytname_[] =
  {
  "$end", "error", "$undefined", "IDENT", "\"integer\"", "\"string\"",
  "NUL", "SELECT", "AS", "FROM", "WHERE", "GROUP", "BY", "HAVING", "ORDER",
  "ASC", "DESC", "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE",
  "CREATE", "TABLE", "DESCRIBE", "SHOW", "TABLES", "DROP", "PRIMARY",
  "DISTINCT", "KEY", "NOTEQ", "GEQ", "LEQ", "AND", "OR", "NOT", "ERROR",
  "QUIT", "';'", "'('", "')'", "'='", "','", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "$accept", "program", "sql_command", "tablename",
  "colname", "expr", "fcall", "fncargs", "value", "select_expr",
  "whereclause", "havingclause", "groupclause", "grouplist", "groupspec",
  "orderclause", "orderlist", "orderspec", "projection", "outcol", "join",
  "data_list", "column_decls", "column_decl", "bin_op", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  SQLParser::yyrline_[] =
  {
       0,   113,   113,   114,   118,   123,   127,   131,   135,   139,
     144,   148,   152,   156,   160,   161,   165,   166,   170,   171,
     172,   173,   174,   175,   176,   179,   180,   183,   184,   187,
     188,   189,   193,   203,   204,   207,   208,   211,   212,   215,
     216,   219,   222,   223,   226,   227,   230,   231,   232,   233,
     234,   235,   238,   239,   242,   243,   246,   247,   250,   251,
     252,   253,   254,   255,   256,   259,   260,   263,   264,   265,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279
  };

  // Print the state stack on the debug stream.
  void
  SQLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  SQLParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  SQLParser::token_number_type
  SQLParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    49,    47,    44,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      46,    43,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
    };
    const unsigned int user_token_number_max_ = 294;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "sql_parser.yy" // lalr1.cc:1155
} // UCD
#line 1650 "/mnt/Data/Code/ECS165B/parser/sql_parser.cpp" // lalr1.cc:1155
#line 282 "sql_parser.yy" // lalr1.cc:1156


void UCD::SQLParser::error( const location_type &l, const std::string &err_message ) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
