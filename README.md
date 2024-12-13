# Fundamentals-of-Compilers
A collection of programs focused on fundamental concepts of compiler design, including DFA, lexical analysis, parsing, and code optimization, implemented using C, LEX, and YACC.

## 📜 **Contents**

1. **DFA Construction**
   - [DFA from Regular Grammar](DFA/DFA_From_Regular_Grammar.c)
   - [DFA to Accept Odd 0’s and Even 1’s](DFA/DFA_Odd0s_Even1s.l)
   - [DFA to Accept Strings Ending with 11](DFA/DFA_Ending_11.l)

2. **Lexical Analysis**
   - [Lexical Analyzer (Array Input)](LexicalAnalyzers/LexicalAnalyzer_Array.c)
   - [Lexical Analyzer using LEX](LexicalAnalyzers/LexicalAnalyzer_LEX.l)

3. **Parsing**
   - [Predictive Parse Table Construction](Parsers/Predictive_Parse_Table.c)
   - [Predictive Parsing Algorithm](Parsers/Predictive_Parsing.c)

4. **Syntax Trees**
   - [Abstract Syntax Tree (Infix to Postfix)](SyntaxTrees/AST_Infix_To_Postfix.l)
   - [Abstract Syntax Tree with YACC](SyntaxTrees/AST_Infix_To_Postfix.y)

5. **Simple Calculators**
   - [Simple Calculator (LEX)](SimpleCalculators/Simple_Calculator.l)
   - [Simple Calculator (YACC)](SimpleCalculators/Simple_Calculator.y)

6. **Three Address Code**
   - [Three Address Code Generation](ThreeAddressCode/Three_Address_Code.l)
   - [Three Address Code with YACC](ThreeAddressCode/Three_Address_Code.y)

7. **Code Optimization**
   - [Simple Code Optimization Techniques](CodeOptimization/Code_Optimization.c)

8. **Code Generation**
   - [8086 Assembly Code Generation](CodeGeneration/BackEnd_8086.c)

9. **NFA to DFA Conversion**
   - [NFA to DFA Implementation](NFA_To_DFA/NFA_To_DFA.c)

## 🚀 **Compile and Execute the Code**
   🔹 For C Programs
    Open your terminal and navigate to the program directory.<br>
    Compile the program using gcc:<br>
      &nbsp;&nbsp;&nbsp;gcc filename.c -o output<br>
    Run the compiled program:<br>
      &nbsp;&nbsp;&nbsp;./output<br>
  🔹 For LEX Programs<br>
   Use the lex tool to generate the scanner:<br>
      &nbsp;&nbsp;&nbsp;flex filename.l<br>
   Compile the generated C code using gcc:<br>
      &nbsp;&nbsp;&nbsp;gcc lex.yy.c<br>
   Execute the program:<br>
      &nbsp;&nbsp;&nbsp;a.exe<br>
  🔹 For LEX + YACC Programs<br>
   Use the lex tool to process the .lex file:<br>
      &nbsp;&nbsp;&nbsp;flex filename.l<br>
   Use the yacc tool to process the .y file:<br>
      &nbsp;&nbsp;&nbsp;bison -dy filename.y<br>
   Compile the generated files with gcc:<br>
      &nbsp;&nbsp;&nbsp;gcc lex.yy.c y.tab.c<br>
   Run the final executable:<br>
      &nbsp;&nbsp;&nbsp;a.exe<br>

## 💡 **Features**
Covers essential compiler design topics.<br>
Demonstrates practical applications using C, LEX, and YACC.

## 🛠️ **Technologies Used**
Programming Languages: C<br>
Tools: LEX, YACC<br>
Platform: Windows<br>

## 🤝 **Contributing**
Contributions are welcome! If you have ideas for improvement or want to add more examples, feel free to fork this repository and create a pull request.
