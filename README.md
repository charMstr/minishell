parsing: 2 STEPS
	lexer (lexical analizer)	=> creates tokens
	parser	=> process the tokens acording to a grammar and build a AST of all
				the commands we need to run

I]	getting the next command line:
	if you want to handle the multiline: put the terminal in raw mode
	read char by char, and once the ENTER is pressed, send the line to the
	tokeniser (aka lexical analyser, aka lexer) part.

	/!\ The <backslash> and <newline> shall be removed before splitting the
	input into tokens.
	refer to the online flowchart diagram.

II] tokenisation (aka lexing)

	1) char by char, create tokens with the lexer. If the tokens arent finished
	at the end of the user's input (unmatching quotes or parenthesis,
	escaped new-line...):
	--> prompt a PS2. redo it UNTIL the all the tokens are closed.
	note: fix set of metacharacter to separate tokens (unquoted and unescaped)
		<space>, <tab>, <newline>, ;, (, ), |, &, <, >.

	2) then when the token constructs are fully complete we can stop getting
	the user 's input, and start to parse the command.
	
	3) categorizing the tokens as we creat them from left to right.
	Once a token is delimited, make sure its being categorized as required by
	the shell grammar.

	4) separate in between: OPERATOR (including IO_NUMBER...) or TOKEN

    5) (NO NEED TO DO THAT)
		then TOKEN ca be further anylized to be either:
		WORD, NAME , ASSIGNEMENT_WORD, reserved word( {, case, esac, while...)
		
III]	build an abstract tree in the parser section. At least we can start
		just organising the token list into simple commands and compound
		commands.(using just pipes)
		thanks to the operators, we can identify the begining and end of jobs.

V]	Redirection is performed if necessary. 

VI]	Commands are executed.

EXECUTION VOCAB:
	- lets call a simple command a simple_cmd
	- a pipeline: a pipeline or job.
	- An AND-OR list is a sequence of one or more pipelines separated by the
	operators "&&" and "||". 
	- A list is a sequence of one or more AND-OR lists separated by the
	operators ';' and '&'.	 we will call them t_list_sh (because of the libft)
			sequential list: separated by: ';'
			asynchronous list: '&' (WE DONT DO THAT)
