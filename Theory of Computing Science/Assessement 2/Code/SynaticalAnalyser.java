import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;
import java.util.*;

public class SyntacticAnalyser {
	public static ParseTree parse(List<Token> tokens) throws SyntaxException {
		if (tokens.size() == 0) {
			throw new SyntaxException("Empty input!");
		}
		//The Parse Tree
		ParseTree outputTree = new ParseTree();
		TreeNode root = new TreeNode(TreeNode.Label.prog, null);
		outputTree.setRoot(root);
		TreeNode activeNode = root;
		//STACK
		Deque<Object> stack = new ArrayDeque<>();
		stack.push(TreeNode.Label.terminal);// add $ to the stack
		stack.push(TreeNode.Label.prog);
		//PARSING TABLE
		Map<Pair<TreeNode.Label, Object>, GrammarRule> table = GetParsingTable();

		int readingHead = 0;

		while (!stack.isEmpty()) {
			Object newSymbol = stack.pop();
			if (newSymbol.equals("marker")) {
				activeNode = activeNode.getParent();
			}
			else {
			if (newSymbol == TreeNode.Label.terminal) {
				if (readingHead >= tokens.size()) {
					return outputTree;
				}
				else {
					throw new SyntaxException("Stack empty before all input string read.");
				}
			}
			if (isTerminal(newSymbol)) {
				if (newSymbol instanceof Token.TokenType) {
					if (tokens.get(readingHead).getType() == Token.TokenType.ID || tokens.get(readingHead).getType() == Token.TokenType.NUM || tokens.get(readingHead).getType() == Token.TokenType.CHARLIT || tokens.get(readingHead).getType() == Token.TokenType.STRINGLIT) {
						String value = tokens.get(readingHead).getValue().get();
						Token tempToken = new Token( (Token.TokenType) newSymbol, value);
						TreeNode tempNode = new TreeNode(TreeNode.Label.terminal, tempToken, activeNode);
						activeNode.addChild(tempNode);
					}
					else {
						Token tempToken = new Token( (Token.TokenType) newSymbol);
						TreeNode tempNode = new TreeNode(TreeNode.Label.terminal, tempToken, activeNode);
						activeNode.addChild(tempNode);
					}
				}
				else if (newSymbol instanceof Token) {
					Token tempToken = (Token) newSymbol;
					TreeNode tempNode = new TreeNode(TreeNode.Label.terminal, tempToken, activeNode);
					activeNode.addChild(tempNode);
				}
				if (tokens.get(readingHead).getType() == newSymbol || tokens.get(readingHead).equals(newSymbol)) {//check if matches token
					readingHead++;
				}
				else {
					throw new SyntaxException("Error. Mismatch between stack and input");
				}
			}
			else {
				Token token = tokens.get(readingHead);

				if (newSymbol != TreeNode.Label.epsilon) {
					if (newSymbol != TreeNode.Label.prog) {
						TreeNode tempNode = new TreeNode((TreeNode.Label)newSymbol, activeNode);
						activeNode.addChild(tempNode);
						activeNode = tempNode;
					}
					List<Object> toAdd = new ArrayList<>();
					try {
						toAdd = table.get(new Pair(newSymbol, token.getType())).GetRule();
					}
					catch (NullPointerException e) {
						try {
						toAdd = table.get(new Pair(newSymbol, token.getValue().get())).GetRule();
						}
						catch (NullPointerException e2) {
							throw new SyntaxException("Invalid Syntax in input code");
						}
					}
					stack.push("marker");
					for (int i = toAdd.size() - 1; i >= 0; i--) {
						stack.push(toAdd.get(i));
					}
			}
			else {
				TreeNode tempNode = new TreeNode((TreeNode.Label)newSymbol, activeNode);
				activeNode.addChild(tempNode);
			}
			}
			}
		}
		return outputTree;
	}

	private static Map<Pair<TreeNode.Label, Object>, GrammarRule> GetParsingTable() {
		Map<TreeNode.Label, List<GrammarRule>> grammar = GenerateGrammar();
		Map<Pair<TreeNode.Label, Object>, GrammarRule> ParsingTable = new HashMap<>();

		//ParsingTable.put(new Pair(TreeNode.Label.NAME, Token.TokenType.NAME), grammar.get(TreeNode.Label.NAME).get(#));
		//prog
		ParsingTable.put(new Pair(TreeNode.Label.prog, Token.TokenType.PUBLIC), grammar.get(TreeNode.Label.prog).get(0));

		//los
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.los).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.ELSE), grammar.get(TreeNode.Label.los).get(1));

		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.WHILE), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.FOR), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.IF), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.ID), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, "int"), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, "boolean"), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, "char"), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.PRINT), grammar.get(TreeNode.Label.los).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.los, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.los).get(0));

		//stat
		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.WHILE), grammar.get(TreeNode.Label.stat).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.FOR), grammar.get(TreeNode.Label.stat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.IF), grammar.get(TreeNode.Label.stat).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.ID), grammar.get(TreeNode.Label.stat).get(3));

		ParsingTable.put(new Pair(TreeNode.Label.stat, "int"), grammar.get(TreeNode.Label.stat).get(4));
		ParsingTable.put(new Pair(TreeNode.Label.stat, "boolean"), grammar.get(TreeNode.Label.stat).get(4));
		ParsingTable.put(new Pair(TreeNode.Label.stat, "char"), grammar.get(TreeNode.Label.stat).get(4));

		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.PRINT), grammar.get(TreeNode.Label.stat).get(5));
		ParsingTable.put(new Pair(TreeNode.Label.stat, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.stat).get(6));

		//while
		ParsingTable.put(new Pair(TreeNode.Label.whilestat, Token.TokenType.WHILE), grammar.get(TreeNode.Label.whilestat).get(0));

		//for
		ParsingTable.put(new Pair(TreeNode.Label.forstat, Token.TokenType.FOR), grammar.get(TreeNode.Label.forstat).get(0));

		//for start
		ParsingTable.put(new Pair(TreeNode.Label.forstart, "int"), grammar.get(TreeNode.Label.forstart).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.forstart, "boolean"), grammar.get(TreeNode.Label.forstart).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.forstart, "char"), grammar.get(TreeNode.Label.forstart).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.forstart, Token.TokenType.ID), grammar.get(TreeNode.Label.forstart).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.forstart, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.forstart).get(2));

		//for arith //!! does it need + and - ??
		ParsingTable.put(new Pair(TreeNode.Label.forarith, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.forarith).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.forarith, Token.TokenType.ID), grammar.get(TreeNode.Label.forarith).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.forarith, Token.TokenType.NUM), grammar.get(TreeNode.Label.forarith).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.forarith, Token.TokenType.RPAREN), grammar.get(TreeNode.Label.forarith).get(1));

		//if
		ParsingTable.put(new Pair(TreeNode.Label.ifstat, Token.TokenType.IF), grammar.get(TreeNode.Label.ifstat).get(0));

		//else if
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.ELSE), grammar.get(TreeNode.Label.elseifstat).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.WHILE), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.FOR), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.IF), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.ID), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, "int"), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, "boolean"), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, "char"), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.PRINT), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.elseifstat).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.elseifstat, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.elseifstat).get(1));

		//else?if
		ParsingTable.put(new Pair(TreeNode.Label.elseorelseif, Token.TokenType.ELSE), grammar.get(TreeNode.Label.elseorelseif).get(0));

		//poss if
		ParsingTable.put(new Pair(TreeNode.Label.possif, Token.TokenType.IF), grammar.get(TreeNode.Label.possif).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.possif, Token.TokenType.LBRACE), grammar.get(TreeNode.Label.possif).get(1));

		//assign
		ParsingTable.put(new Pair(TreeNode.Label.assign, Token.TokenType.ID), grammar.get(TreeNode.Label.assign).get(0));

		//decl
		ParsingTable.put(new Pair(TreeNode.Label.decl, "int"), grammar.get(TreeNode.Label.decl).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.decl, "boolean"), grammar.get(TreeNode.Label.decl).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.decl, "char"), grammar.get(TreeNode.Label.decl).get(0));

		//poss assign
		ParsingTable.put(new Pair(TreeNode.Label.possassign, Token.TokenType.ASSIGN), grammar.get(TreeNode.Label.possassign).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.possassign, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.possassign).get(1));

		//print
		ParsingTable.put(new Pair(TreeNode.Label.print, Token.TokenType.PRINT), grammar.get(TreeNode.Label.print).get(0));

		//type
		ParsingTable.put(new Pair(TreeNode.Label.type, "int"), grammar.get(TreeNode.Label.type).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.type, "boolean"), grammar.get(TreeNode.Label.type).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.type, "char"), grammar.get(TreeNode.Label.type).get(2));

		//expr
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.PLUS), grammar.get(TreeNode.Label.expr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.MINUS), grammar.get(TreeNode.Label.expr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.expr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.ID), grammar.get(TreeNode.Label.expr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.NUM), grammar.get(TreeNode.Label.expr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.TRUE), grammar.get(TreeNode.Label.expr).get(0));//AAAA
		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.FALSE), grammar.get(TreeNode.Label.expr).get(0));//AAAAA

		ParsingTable.put(new Pair(TreeNode.Label.expr, Token.TokenType.SQUOTE), grammar.get(TreeNode.Label.expr).get(1));

		//char expr
		ParsingTable.put(new Pair(TreeNode.Label.charexpr, Token.TokenType.SQUOTE), grammar.get(TreeNode.Label.charexpr).get(0));

		//bool expr
		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.boolexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.boolexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.AND), grammar.get(TreeNode.Label.boolexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.OR), grammar.get(TreeNode.Label.boolexpr).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.RPAREN), grammar.get(TreeNode.Label.boolexpr).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.boolexpr).get(1));

		ParsingTable.put(new Pair(TreeNode.Label.boolexpr, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.boolexpr).get(1));//AAAAA

		//bool op
		ParsingTable.put(new Pair(TreeNode.Label.boolop, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.boolop).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.boolop, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.boolop).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.boolop, Token.TokenType.AND), grammar.get(TreeNode.Label.boolop).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.boolop, Token.TokenType.OR), grammar.get(TreeNode.Label.boolop).get(1));

		//bool eq
		ParsingTable.put(new Pair(TreeNode.Label.booleq, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.booleq).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.booleq, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.booleq).get(1));

		//bool log
		ParsingTable.put(new Pair(TreeNode.Label.boollog, Token.TokenType.AND), grammar.get(TreeNode.Label.boollog).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.boollog, Token.TokenType.OR), grammar.get(TreeNode.Label.boollog).get(1));

		//rel expr
		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.PLUS), grammar.get(TreeNode.Label.relexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.MINUS), grammar.get(TreeNode.Label.relexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.relexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.ID), grammar.get(TreeNode.Label.relexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.NUM), grammar.get(TreeNode.Label.relexpr).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.TRUE), grammar.get(TreeNode.Label.relexpr).get(1));

		ParsingTable.put(new Pair(TreeNode.Label.relexpr, Token.TokenType.FALSE), grammar.get(TreeNode.Label.relexpr).get(2));

		//rel expr'
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.LT), grammar.get(TreeNode.Label.relexprprime).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.LE), grammar.get(TreeNode.Label.relexprprime).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.GT), grammar.get(TreeNode.Label.relexprprime).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.GE), grammar.get(TreeNode.Label.relexprprime).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.AND), grammar.get(TreeNode.Label.relexprprime).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.OR), grammar.get(TreeNode.Label.relexprprime).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.RPAREN), grammar.get(TreeNode.Label.relexprprime).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.relexprprime).get(1));

		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.relexprprime).get(1));//AAA
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.relexprprime).get(1));//AAA
		ParsingTable.put(new Pair(TreeNode.Label.relexprprime, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.relexprprime).get(1));//AAA

		//rel op
		ParsingTable.put(new Pair(TreeNode.Label.relop, Token.TokenType.LT), grammar.get(TreeNode.Label.relop).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.relop, Token.TokenType.LE), grammar.get(TreeNode.Label.relop).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.relop, Token.TokenType.GT), grammar.get(TreeNode.Label.relop).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.relop, Token.TokenType.GE), grammar.get(TreeNode.Label.relop).get(3));

		//arith expr
		ParsingTable.put(new Pair(TreeNode.Label.arithexpr, Token.TokenType.PLUS), grammar.get(TreeNode.Label.arithexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.arithexpr, Token.TokenType.MINUS), grammar.get(TreeNode.Label.arithexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.arithexpr, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.arithexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.arithexpr, Token.TokenType.ID), grammar.get(TreeNode.Label.arithexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.arithexpr, Token.TokenType.NUM), grammar.get(TreeNode.Label.arithexpr).get(0));

		//arith expr'
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.PLUS), grammar.get(TreeNode.Label.arithexprprime).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.MINUS), grammar.get(TreeNode.Label.arithexprprime).get(1));

		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.LT), grammar.get(TreeNode.Label.arithexprprime).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.LE), grammar.get(TreeNode.Label.arithexprprime).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.GT), grammar.get(TreeNode.Label.arithexprprime).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.GE), grammar.get(TreeNode.Label.arithexprprime).get(2));

		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.AND), grammar.get(TreeNode.Label.arithexprprime).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.OR), grammar.get(TreeNode.Label.arithexprprime).get(2));

		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.RPAREN), grammar.get(TreeNode.Label.arithexprprime).get(2));
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.arithexprprime).get(2));

		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.arithexprprime).get(2));//AAAA
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.arithexprprime).get(2));//AAAA
		ParsingTable.put(new Pair(TreeNode.Label.arithexprprime, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.arithexprprime).get(2));//AAAA

		//term
		ParsingTable.put(new Pair(TreeNode.Label.term, Token.TokenType.PLUS), grammar.get(TreeNode.Label.term).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.term, Token.TokenType.MINUS), grammar.get(TreeNode.Label.term).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.term, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.term).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.term, Token.TokenType.ID), grammar.get(TreeNode.Label.term).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.term, Token.TokenType.NUM), grammar.get(TreeNode.Label.term).get(0));

		//term'
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.TIMES), grammar.get(TreeNode.Label.termprime).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.DIVIDE), grammar.get(TreeNode.Label.termprime).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.MOD), grammar.get(TreeNode.Label.termprime).get(2));

		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.PLUS), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.MINUS), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.LT), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.LE), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.GT), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.GE), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.AND), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.OR), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.RPAREN), grammar.get(TreeNode.Label.termprime).get(3));
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.RBRACE), grammar.get(TreeNode.Label.termprime).get(3));

		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.SEMICOLON), grammar.get(TreeNode.Label.termprime).get(3));//AAAAAA
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.EQUAL), grammar.get(TreeNode.Label.termprime).get(3));//AAAAAA
		ParsingTable.put(new Pair(TreeNode.Label.termprime, Token.TokenType.NEQUAL), grammar.get(TreeNode.Label.termprime).get(3));//AAAAAA

		//factor
		ParsingTable.put(new Pair(TreeNode.Label.factor, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.factor).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.factor, Token.TokenType.ID), grammar.get(TreeNode.Label.factor).get(1));
		ParsingTable.put(new Pair(TreeNode.Label.factor, Token.TokenType.NUM), grammar.get(TreeNode.Label.factor).get(2));

		//print expr
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.PLUS), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.MINUS), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.LPAREN), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.ID), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.NUM), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.TRUE), grammar.get(TreeNode.Label.printexpr).get(0));
		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.FALSE), grammar.get(TreeNode.Label.printexpr).get(0));

		ParsingTable.put(new Pair(TreeNode.Label.printexpr, Token.TokenType.DQUOTE), grammar.get(TreeNode.Label.printexpr).get(1));

		return ParsingTable;
	}


	private static boolean isTerminal(Object symbol) {
		return symbol instanceof Token.TokenType || symbol instanceof Token;
	}


	//HELPER METHODS
	//can add mutliple rules to the list and then link the approrpiate key with that list to build the grammar.
	private static Map<TreeNode.Label, List<GrammarRule>> GenerateGrammar() {
		Map<TreeNode.Label, List<GrammarRule>> grammar = new LinkedHashMap();

		//prog
		List<GrammarRule> allRules = new ArrayList<>();
		allRules.add(new GrammarRule(new String[] {"public", "class", "<<ID>>", "{", "public", "static", "void", "main", "(", "String[]", "args", ")", "{", "<<los>>", "}", "}"}));
		grammar.put(TreeNode.Label.prog, allRules);

		//los
		List<GrammarRule> allRules1 = new ArrayList<>();
		allRules1.add(new GrammarRule(new String[] {"<<stat>>", "<<los>>"}));
		allRules1.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.los, allRules1);

		//stat
		List<GrammarRule> allRules2 = new ArrayList<>();
		allRules2.add(new GrammarRule(new String[] {"<<while>>"}));
		allRules2.add(new GrammarRule(new String[] {"<<for>>"}));
		allRules2.add(new GrammarRule(new String[] {"<<if>>"}));
		allRules2.add(new GrammarRule(new String[] {"<<assign>>", ";"}));
		allRules2.add(new GrammarRule(new String[] {"<<decl>>", ";"}));
		allRules2.add(new GrammarRule(new String[] {"<<print>>", ";"}));
		allRules2.add(new GrammarRule(new String[] {";"}));
		grammar.put(TreeNode.Label.stat, allRules2);

		//while
		List<GrammarRule> allRules3 = new ArrayList<>();
		allRules3.add(new GrammarRule(new String[] {"while", "(", "<<rel expr>>", "<<bool expr>>", ")", "{", "<<los>>", "}"}));
		grammar.put(TreeNode.Label.whilestat, allRules3);

		//for
		List<GrammarRule> allRules4 = new ArrayList<>();
		allRules4.add(new GrammarRule(new String[] {"for", "(", "<<for start>>", ";", "<<rel expr>>", "<<bool expr>>", ";", "<<for arith>>", ")", "{", "<<los>>", "}"}));
		grammar.put(TreeNode.Label.forstat, allRules4);

		//for start
		List<GrammarRule> allRules5 = new ArrayList<>();
		allRules5.add(new GrammarRule(new String[] {"<<decl>>"}));
		allRules5.add(new GrammarRule(new String[] {"<<assign>>"}));
		allRules5.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.forstart, allRules5);

		//for arith
		List<GrammarRule> allRules6 = new ArrayList<>();
		allRules6.add(new GrammarRule(new String[] {"<<arith expr>>"}));
		allRules6.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.forarith, allRules6);

		//if
		List<GrammarRule> allRules7 = new ArrayList<>();
		allRules7.add(new GrammarRule(new String[] {"if", "(", "<<rel expr>>", "<<bool expr>>", ")", "{", "<<los>>", "}", "<<else if>>"}));
		grammar.put(TreeNode.Label.ifstat, allRules7);

		//else if
		List<GrammarRule> allRules8 = new ArrayList<>();
		allRules8.add(new GrammarRule(new String[] {"<<else?if>>", "{", "<<los>>", "}", "<<else if>>"}));
		allRules8.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.elseifstat, allRules8);

		//else?if
		List<GrammarRule> allRules9 = new ArrayList<>();
		allRules9.add(new GrammarRule(new String[] {"else", "<<poss if>>"}));
		grammar.put(TreeNode.Label.elseorelseif, allRules9);

		//poss if
		List<GrammarRule> allRules10 = new ArrayList<>();
		allRules10.add(new GrammarRule(new String[] {"if", "(", "<<rel expr>>", "<<bool expr>>", ")"}));
		allRules10.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.possif, allRules10);

		//assign
		List<GrammarRule> allRules11 = new ArrayList<>();
		allRules11.add(new GrammarRule(new String[] {"<<ID>>", "=", "<<expr>>"}));
		grammar.put(TreeNode.Label.assign, allRules11);

		//decl
		List<GrammarRule> allRules12 = new ArrayList<>();
		allRules12.add(new GrammarRule(new String[] {"<<type>>", "<<ID>>", "<<poss assign>>"}));
		grammar.put(TreeNode.Label.decl, allRules12);

		//poss assign
		List<GrammarRule> allRules13 = new ArrayList<>();
		allRules13.add(new GrammarRule(new String[] {"=", "<<expr>>"}));
		allRules13.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.possassign, allRules13);

		//print
		List<GrammarRule> allRules14 = new ArrayList<>();
		allRules14.add(new GrammarRule(new String[] {"System.out.println", "(", "<<print expr>>", ")"}));
		grammar.put(TreeNode.Label.print, allRules14);

		//type
		List<GrammarRule> allRules15 = new ArrayList<>();
		allRules15.add(new GrammarRule(new String[] {"int"}));
		allRules15.add(new GrammarRule(new String[] {"boolean"}));
		allRules15.add(new GrammarRule(new String[] {"char"}));
		grammar.put(TreeNode.Label.type, allRules15);

		//expr
		List<GrammarRule> allRules16 = new ArrayList<>();
		allRules16.add(new GrammarRule(new String[] {"<<rel expr>>", "<<bool expr>>"}));
		//allRules16.add(new GrammarRule(new String[] {"<<bool expr>>"}));
		allRules16.add(new GrammarRule(new String[] {"<<char expr>>"}));
		grammar.put(TreeNode.Label.expr, allRules16);

		//char expr
		List<GrammarRule> allRules17 = new ArrayList<>();
		allRules17.add(new GrammarRule(new String[] {"'", "<<char>>", "'"}));
		grammar.put(TreeNode.Label.charexpr, allRules17);

		//bool expr
		List<GrammarRule> allRules18 = new ArrayList<>();
		allRules18.add(new GrammarRule(new String[] {"<<bool op>>", "<<rel expr>>", "<<bool expr>>"}));
		allRules18.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.boolexpr, allRules18);

		//bool op
		List<GrammarRule> allRules19 = new ArrayList<>();
		allRules19.add(new GrammarRule(new String[] {"<<bool eq>>"}));
		allRules19.add(new GrammarRule(new String[] {"<<bool log>>"}));
		grammar.put(TreeNode.Label.boolop, allRules19);

		//bool eq
		List<GrammarRule> allRules20 = new ArrayList<>();
		allRules20.add(new GrammarRule(new String[] {"=="}));
		allRules20.add(new GrammarRule(new String[] {"!="}));
		grammar.put(TreeNode.Label.booleq, allRules20);

		//bool log
		List<GrammarRule> allRules21 = new ArrayList<>();
		allRules21.add(new GrammarRule(new String[] {"&&"}));
		allRules21.add(new GrammarRule(new String[] {"||"}));
		grammar.put(TreeNode.Label.boollog, allRules21);

		//rel expr
		List<GrammarRule> allRules22 = new ArrayList<>();
		allRules22.add(new GrammarRule(new String[] {"<<arith expr>>", "<<rel expr'>>"}));
		allRules22.add(new GrammarRule(new String[] {"true"}));
		allRules22.add(new GrammarRule(new String[] {"false"}));
		grammar.put(TreeNode.Label.relexpr, allRules22);

		//rel expr'
		List<GrammarRule> allRules23 = new ArrayList<>();
		allRules23.add(new GrammarRule(new String[] {"<<rel op>>", "<<arith expr>>"}));
		allRules23.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.relexprprime, allRules23);

		//rel op
		List<GrammarRule> allRules24 = new ArrayList<>();
		allRules24.add(new GrammarRule(new String[] {"<"}));
		allRules24.add(new GrammarRule(new String[] {"<="}));
		allRules24.add(new GrammarRule(new String[] {">"}));
		allRules24.add(new GrammarRule(new String[] {">="}));
		grammar.put(TreeNode.Label.relop, allRules24);

		//arith expr
		List<GrammarRule> allRules25 = new ArrayList<>();
		allRules25.add(new GrammarRule(new String[] {"<<term>>", "<<arith expr'>>"}));
		grammar.put(TreeNode.Label.arithexpr, allRules25);

		//arith expr'
		List<GrammarRule> allRules26 = new ArrayList<>();
		allRules26.add(new GrammarRule(new String[] {"+", "<<term>>", "<<arith expr'>>"}));
		allRules26.add(new GrammarRule(new String[] {"-", "<<term>>", "<<arith expr'>>"}));
		allRules26.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.arithexprprime, allRules26);

		//term
		List<GrammarRule> allRules27 = new ArrayList<>();
		allRules27.add(new GrammarRule(new String[] {"<<factor>>", "<<term'>>"}));
		grammar.put(TreeNode.Label.term, allRules27);

		//term'
		List<GrammarRule> allRules28 = new ArrayList<>();
		allRules28.add(new GrammarRule(new String[] {"*", "<<factor>>", "<<term'>>"}));
		allRules28.add(new GrammarRule(new String[] {"/", "<<factor>>", "<<term'>>"}));
		allRules28.add(new GrammarRule(new String[] {"%", "<<factor>>", "<<term'>>"}));
		allRules28.add(new GrammarRule(new String[] {"<<epsilon>>"}));
		grammar.put(TreeNode.Label.termprime, allRules28);

		//factor
		List<GrammarRule> allRules29 = new ArrayList<>();
		allRules29.add(new GrammarRule(new String[] {"(", "<<arith expr>>", ")"}));
		allRules29.add(new GrammarRule(new String[] {"<<ID>>"}));
		allRules29.add(new GrammarRule(new String[] {"<<num>>"}));
		grammar.put(TreeNode.Label.factor, allRules29);

		//print expr
		List<GrammarRule> allRules30 = new ArrayList<>();
		allRules30.add(new GrammarRule(new String[] {"<<rel expr>>", "<<bool expr>>"}));
		allRules30.add(new GrammarRule(new String[] {"\"", "<<string lit>>", "\""}));
		grammar.put(TreeNode.Label.printexpr, allRules30);

		return grammar;
	}

}

class GrammarRule {

	private List<Object> rule;

	public GrammarRule(String[] definition) {
		this.rule = readRule(definition);
	}

	public List<Object> GetRule() {
		return this.rule;
	}

	public Object GetFirstChar() {
		return this.rule.get(0);
	}

	public String ToString() {//test method -- remove later??
		String string = "";
		for (Object x : rule) {
			string += x;
		}
		return string;
	}


	//Takes in a string array written in a similar way to the theoretical grammar and returns a list containing:
	//Token.TokenType
	//TreeNode.Label
	//Token(Token.TokenType, "str")
	//This list is essentially one 'possible' grammatical rule. (Then stored in a GrammarRule object)
	private static List<Object> readRule(String[] definition) {
		List<Object> rule = new ArrayList<>();
		for (String item : definition) {
			switch (item) {
				//TERMINALS
				case "+":
					rule.add(Token.TokenType.PLUS);
					break;
				case "-":
					rule.add(Token.TokenType.MINUS);
					break;
				case "*":
					rule.add(Token.TokenType.TIMES);
					break;
				case "/":
					rule.add(Token.TokenType.DIVIDE);
					break;
				case "%":
					rule.add(Token.TokenType.MOD);
					break;//here!
				case "=":
					rule.add(Token.TokenType.ASSIGN);
					break;
				case "==":
					rule.add(Token.TokenType.EQUAL);
					break;
				case "!=":
					rule.add(Token.TokenType.NEQUAL);
					break;
				case "<":
					rule.add(Token.TokenType.LT);
					break;
				case ">":
					rule.add(Token.TokenType.GE);
					break;
				case "<=":
					rule.add(Token.TokenType.LE);
					break;
				case ">=":
					rule.add(Token.TokenType.GE);
					break;
				case "(":
					rule.add(Token.TokenType.LPAREN);
					break;
				case ")":
					rule.add(Token.TokenType.RPAREN);
					break;
				case "{":
					rule.add(Token.TokenType.LBRACE);
					break;
				case "}":
					rule.add(Token.TokenType.RBRACE);
					break;
				case "&&":
					rule.add(Token.TokenType.AND);
					break;
				case "||":
					rule.add(Token.TokenType.OR);
					break;
				case ";":
					rule.add(Token.TokenType.SEMICOLON);
					break;
				case "public":
					rule.add(Token.TokenType.PUBLIC);
					break;
				case "class":
					rule.add(Token.TokenType.CLASS);
					break;
				case "static":
					rule.add(Token.TokenType.STATIC);
					break;
				case "void":
					rule.add(Token.TokenType.VOID);
					break;
				case "main":
					rule.add(Token.TokenType.MAIN);
					break;
				case "String[]":
					rule.add(Token.TokenType.STRINGARR);
					break;
				case "args":
					rule.add(Token.TokenType.ARGS);
					break;
				case "int":
					rule.add(new Token(Token.TokenType.TYPE, "int"));//????
					break;
				case "boolean":
					rule.add(new Token(Token.TokenType.TYPE, "boolean"));
					break;
				case "char":
					rule.add(new Token(Token.TokenType.TYPE, "char"));
					break;
				case "System.out.println":
					rule.add(Token.TokenType.PRINT);
					break;
				case "while":
					rule.add(Token.TokenType.WHILE);
					break;
				case "for":
					rule.add(Token.TokenType.FOR);
					break;
				case "if":
					rule.add(Token.TokenType.IF);
					break;
				case "else":
					rule.add(Token.TokenType.ELSE);
					break;
				case "\"":
					rule.add(Token.TokenType.DQUOTE);
					break;
				case "'":
					rule.add(Token.TokenType.SQUOTE);
					break;
				case "true":
					rule.add(Token.TokenType.TRUE);
					break;
				case "false":
					rule.add(Token.TokenType.FALSE);
					break;

				//TERMINALS with types
				case "<<ID>>":
					rule.add(Token.TokenType.ID);
					break;
				case "<<num>>":
					rule.add(Token.TokenType.NUM);
					break;
				case "<<char>>":
					rule.add(Token.TokenType.CHARLIT);
					break;
				case "<<string lit>>":
					rule.add(Token.TokenType.STRINGLIT);
					break;
				
				//NON-TERMINALS
				case "<<prog>>":
					rule.add(TreeNode.Label.prog);
					break;
				case "<<los>>":
					rule.add(TreeNode.Label.los);
					break;
				case "<<stat>>":
					rule.add(TreeNode.Label.stat);
					break;
				case "<<while>>":
					rule.add(TreeNode.Label.whilestat);
					break;
				case "<<for>>":
					rule.add(TreeNode.Label.forstat);
					break;
				case "<<for start>>":
					rule.add(TreeNode.Label.forstart);
					break;
				case "<<for arith>>":
					rule.add(TreeNode.Label.forarith);
					break;
				case "<<if>>":
					rule.add(TreeNode.Label.ifstat);
					break;
				case "<<else if>>":
					rule.add(TreeNode.Label.elseifstat);
					break;
				case "<<else?if>>":
					rule.add(TreeNode.Label.elseorelseif);
					break;
				case "<<poss if>>":
					rule.add(TreeNode.Label.possif);
					break;
				case "<<assign>>":
					rule.add(TreeNode.Label.assign);
					break;
				case "<<decl>>":
					rule.add(TreeNode.Label.decl);
					break;
				case "<<poss assign>>":
					rule.add(TreeNode.Label.possassign);
					break;
				case "<<print>>":
					rule.add(TreeNode.Label.print);
					break;
				case "<<type>>":
					rule.add(TreeNode.Label.type);
					break;
				case "<<expr>>":
					rule.add(TreeNode.Label.expr);
					break;
				case "<<char expr>>":
					rule.add(TreeNode.Label.charexpr);
					break;
				case "<<bool expr>>":
					rule.add(TreeNode.Label.boolexpr);
					break;
				case "<<bool op>>":
					rule.add(TreeNode.Label.boolop);
					break;
				case "<<bool eq>>":
					rule.add(TreeNode.Label.booleq);
					break;
				case "<<bool log>>":
					rule.add(TreeNode.Label.boollog);
					break;
				case "<<rel expr>>":
					rule.add(TreeNode.Label.relexpr);
					break;
				case "<<rel expr'>>":
					rule.add(TreeNode.Label.relexprprime);
					break;
				case "<<rel op>>":
					rule.add(TreeNode.Label.relop);
					break;
				case "<<arith expr>>":
					rule.add(TreeNode.Label.arithexpr);
					break;
				case "<<arith expr'>>":
					rule.add(TreeNode.Label.arithexprprime);
					break;
				case "<<term>>":
					rule.add(TreeNode.Label.term);
					break;
				case "<<term'>>":
					rule.add(TreeNode.Label.termprime);
					break;
				case "<<factor>>":
					rule.add(TreeNode.Label.factor);
					break;
				case "<<print expr>>":
					rule.add(TreeNode.Label.printexpr);
					break;
				case "<<epsilon>>":
					rule.add(TreeNode.Label.epsilon);//our lingo <<epsilon>>
					break;
			
				default:
					System.out.println("Unknown syntax! " + item);
					break;
			}
		}
		return rule;
	}
}

class Pair<A, B> {
	private final A a;
	private final B b;

	public Pair(A a, B b) {
		this.a = a;
		this.b = b;
	}

	public A fst() {
		return a;
	}

	public B snd() {
		return b;
	}

	@Override
	public int hashCode() {
		return 3 * a.hashCode() + 7 * b.hashCode();
	}

	@Override
	public String toString() {
		return "{" + a + ", " + b + "}";
	}

	@Override
	public boolean equals(Object o) {
		if ((o instanceof Pair<?, ?>)) {
			Pair<?, ?> other = (Pair<?, ?>) o;
			return other.fst().equals(a) && other.snd().equals(b);
		}

		return false;
	}

}
