# QuizGame
A quiz game application that uses a file to read questions and answers from and has varying difficulty levels. Player progress is stored in a file after the quiz concludes. This C project supports dynamic memory allocation and command line arguments with error handling.

Known bugs:
Codeblocks and minGW does not compile the program correctly causing the last letter of each answer to be missing. (E.G pennsylvania is now pennsylvani)

Syntax in QnA file: Question_Answer

Difficulty levels: 
1: Answers are displayed as a '?' character.

2: The length of the answer is displayed using '-' characters for each individual letter.

3: The first and last letter of the answer are displayed, the rest of the letters are displayed with '-' characters.

4: Two random letters of the answer are displayed, the rest of the letters are displayed with '-' characters.

5: All of the letters of the answer are displayed but the letters are jumbled.

6-10: Selects a random difficulty from the difficulties listed above.
                  
Running the QuizGame program:
                  Open your command line/terminal and execute the compiled program (You must provide the file name and difficulty level as command line arguments).
                  A question will pop up, the answer will be below it in the format specified by the difficulty level. (more info on Difficulty levels is available above).
                  Answer the question correctly and receive a point, fail and you get no points, you only have one chance to answer a question.
                  Current score (out of no. of questions) is displayed shortly after answering a question.
                  Once the quiz concludes, the game will prompt you with a question asking if you wish to see which questions you answered incorrectly and their answers.
                  A file is created upon quiz completion called quiz_history.txt which contains (filename - no. of questions answered correctly - no. of questions - difficulty).
                  The quiz_history.txt does not append and is instead recreated for every quiz session completed.
