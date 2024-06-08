import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

public class LexicalAnalyser {

	private enum State {
		START, FRACTION, INTEGER, OPERATOR, WHITESPACE, DOT;
	}
	public static List<Token> analyse(String input) throws NumberException, ExpressionException {
		List<Token> tokens = new ArrayList<>();
		State state = State.START;
		StringBuilder currentNumber = new StringBuilder();

		for (int i = 0; i <input.length(); i++) {
			char x = input.charAt(i);
			Token.TokenType type = Token.typeOf(x);


			switch(state) {
				case START:
				if (x == '.') {
					throw new NumberException();
				}

				if (type == Token.TokenType.NUMBER) {
					if (x == '0') {
						state = State.DOT;
					}
					else {
						state = State.INTEGER;
					}
					currentNumber.append(x);
				}
				else if (type == Token.TokenType.PLUS || type == Token.TokenType.MINUS || type == Token.TokenType.TIMES || type == Token.TokenType.DIVIDE) {
					if (tokens.isEmpty() || (tokens.size() > 0 && tokens.get(tokens.size() -1).getType().isOperator())){
						throw new ExpressionException();
					}
					tokens.add(new Token(type));
					state = State.OPERATOR;
				}
				else if (Character.isWhitespace(x)) {
					state = State.WHITESPACE;
				}
				else {
					throw new ExpressionException();
				}
				break;



				case INTEGER:
					if (type == Token.TokenType.NUMBER) {
						currentNumber.append(x);
					}
					else if ( x == '.') {
						if (!currentNumber.toString().equals("0")) {
						throw new NumberException();
					} 
						state = State.DOT;
				}   else {
						tokens.add(new Token(Double.parseDouble(currentNumber.toString())));
						currentNumber.setLength(0);
						state = State.START;
						i--;
					}
				break;


				case FRACTION:
				if (type == Token.TokenType.NUMBER) {
					currentNumber.append(x);
				}
				else {  
					if (currentNumber.toString().startsWith("0.")) {
						tokens.add(new Token(Double.parseDouble(currentNumber.toString())));
						currentNumber.setLength(0);
						state = State.START;
						i--;
					}
					else {
						throw new NumberException();
					}
				}
				
				break;

				case OPERATOR:

				if (type == Token.TokenType.NUMBER) {
					if (x == '0') {
						state = State.DOT;
					} else {
						state = State.INTEGER;
					}
					currentNumber.append(x);
				} 
				else if (type == Token.TokenType.PLUS || type == Token.TokenType.MINUS || type == Token.TokenType.TIMES || type == Token.TokenType.DIVIDE) {
					throw new ExpressionException();
				}
				else if (Character.isWhitespace(x)) {
					
				}
				else {
					throw new ExpressionException();
				}
				break;


				case WHITESPACE:
				if (type == Token.TokenType.NUMBER) {
					if (!tokens.isEmpty() && tokens.get(tokens.size() - 1).getType() == Token.TokenType.NUMBER) {
						throw new ExpressionException();
					}
					state = State.INTEGER;
					currentNumber.append(x);
				} 
				else if (!Character.isWhitespace(x)) {
					state = State.START;
					i--;
				}

				break;

				case DOT:
				if (type != Token.TokenType.NUMBER) {
					if (currentNumber.toString().equals("0")  && i == input.length() - 1 ) {
						throw new NumberException();
					}
					currentNumber.append(x);
					state = State.FRACTION;
				}
				else {
					throw new NumberException();
				}

				break;

				default:
					throw new ExpressionException();

			}
		}
		if (state == State.DOT) {
			throw new NumberException();
		}
 		else if (state == State.OPERATOR && currentNumber.length() == 0) {
			throw new ExpressionException();
		}
		else if (state == State.INTEGER || state == State.FRACTION ) {
			tokens.add(new Token (Double.parseDouble(currentNumber.toString())));
		}
		else if (state == State.OPERATOR && currentNumber.length() > 0) {
			throw new ExpressionException();
		}

		return tokens;

	}

}
