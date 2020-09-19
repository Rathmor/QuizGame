#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int getNumberOfLinesInFile(char *filename) {
    FILE *file;
    char c;
    int noOfLines = -1;
    if ((file = fopen(filename, "r")) == NULL) {
        printf("File not found!\n");
        return -1;
    }
    c = getc(file);
    while (c != EOF) {
        if (c == '\n') {
            noOfLines = noOfLines + 1;
        }
        c = getc(file);
    }
    return noOfLines;
}

void loadQnA(char *filename, char **questions, char **answers, int noOfLines) {
    FILE *file;
    file = fopen(filename, "r");
    char c;
    char line[255];
    char *question;
    char *answer;
    for (int i=0; i<noOfLines; i++) {
        fgets(line, 255, file);
        question = strtok(line, "_");
        answer = strtok(NULL, "\n");
        if (answer == NULL) {
            break;
        }
        questions[i] = (char *)malloc(sizeof(char) *(strlen(question)));
        answers[i] = (char *)malloc(sizeof(char) *(strlen(answer)));
        strcpy(questions[i], question);
        strcpy(answers[i], answer);
    }
}

void showFirstAndLast(char *answer, char *blankAnswer) {
    blankAnswer[0] = answer[0];
    blankAnswer[strlen(blankAnswer)-1] = answer[strlen(answer)-1];
}

void showTwoRandom(char *answer, char *blankAnswer) {
    int randomIndex1 = (rand() % ((strlen(answer)-1) - 0 + 1)) + 1;
    while (blankAnswer[randomIndex1] != '-') {
        randomIndex1 = (rand() % ((strlen(answer)-1) - 0 + 1)) + 1;
    }
    blankAnswer[randomIndex1] = answer[randomIndex1];

    int randomIndex2 = (rand() % ((strlen(answer)-1) - 0 + 1)) + 1;
    while (blankAnswer[randomIndex2] != '-') {
        randomIndex2 = (rand() % ((strlen(answer)-1) - 0 + 1)) + 1;
    }
    blankAnswer[randomIndex2] = answer[randomIndex2];
}

int startQuizGame(char **questions, char **answers, int noOfQuestions, int difficultyLevel) {
    srand(time(NULL));
    int questionsRead = 0;
    int score = 0;
    int guesses;
    int randomIndex;
    int randomAnswerIndex;
    int randomDifficulty = 0;
    int count;
    char choice;
    char questionsWrong[noOfQuestions];
    char questionsRemaining[noOfQuestions];
    for (int o=0; o<noOfQuestions; o++) {
        questionsRemaining[o] = '-';
        questionsWrong[o] = '-';
    }
    while (questionsRead < noOfQuestions) {
            guesses = 0;
            randomIndex = (rand() % ((noOfQuestions-1) - 0 + 1)) + 0;
            while (questionsRemaining[randomIndex] == '0') {
                randomIndex = (rand() % ((noOfQuestions-1) - 0 + 1)) + 0;
            }
            questionsRemaining[randomIndex] = '0';
            char answer[strlen(answers[randomIndex])];
            char blankAnswer[strlen(answers[randomIndex])];
            char answerCopy[strlen(answers[randomIndex])];
            char guess[strlen(answers[randomIndex])];
            for (int o=0; answers[randomIndex][o] != '\0'; o++) {
                answer[o] = toupper(answers[randomIndex][o]);
                answerCopy[o] = toupper(answers[randomIndex][o]);
                blankAnswer[o] = '-';
            }
            answer[strlen(answers[randomIndex])-1] = '\0';
            blankAnswer[strlen(answers[randomIndex])-1] = '\0';
            printf("%s\n", questions[randomIndex]);

            if (difficultyLevel == 6) {
                randomDifficulty = (rand() % (5 - 1 + 1)) + 1;
            }
            
            if (difficultyLevel == 1 || randomDifficulty == 1) {
                printf("? ");
            } else if (difficultyLevel == 2|| randomDifficulty == 2) {
                for (int o=0; blankAnswer[o] != '\0'; o++) {
                    printf("%c ", blankAnswer[o]);
                }
            } else if (difficultyLevel == 3 || randomDifficulty == 3) {
                showFirstAndLast(answer, blankAnswer);
                for (int o=0; blankAnswer[o] != '\0'; o++) {
                    printf("%c ", blankAnswer[o]);
                }
            } else if (difficultyLevel == 4 || randomDifficulty == 4) {
                showTwoRandom(answer, blankAnswer);
                for (int o=0; blankAnswer[o] != '\0'; o++) {
                    printf("%c ", blankAnswer[o]);
                }
            } else if (difficultyLevel == 5 || randomDifficulty == 5) {
                count = 0;
                while (count < strlen(answer)) {
                    randomAnswerIndex = (rand() % ((strlen(answer)-1) - 0 + 1)) + 0;
                    while (answerCopy[randomAnswerIndex] == '0') {
                        randomAnswerIndex = (rand() % ((strlen(answer)-1) - 0 + 1)) + 0;
                    }
                    printf("%c ", answer[randomAnswerIndex]);
                    answerCopy[randomAnswerIndex] = '0';
                    count++;
                } 
            } else {
                showTwoRandom(answer, blankAnswer);
                for (int o=0; o<strlen(blankAnswer); o++) {
                    printf("%c ", blankAnswer[o]);
                }
            }

            printf("\n::");
            scanf("%s", guess);
            for (int o=0; o<strlen(guess); o++) {
                guess[o] = toupper(guess[o]);
            }

            if (strcmp(guess, answer) == 0) {
                score++;
                printf("\nCorrect! %d/%d\n", score, noOfQuestions);
            } else {
                questionsWrong[randomIndex] = '0';
                printf("\nWrong! %d/%d\n", score, noOfQuestions);
            }
        questionsRead++;
    } 
    fflush(stdin);
    printf("\n\nWould you like to see the answers for the questions you guessed incorrectly? (y/n):");
    scanf(" %c", &choice);
    choice = tolower(choice);
    printf("\n");
    if (choice == 'y') {
        for (int i=0; i<strlen(questionsWrong); i++) {
            if (questionsWrong[i] == '0') {
                printf("%s\nCorrect Answer: %s\n", questions[i], answers[i]);
            }
        }
    }
    return score;
}

void main( int argc, char *argv[] )  {
   if (argc > 3) {
      printf("You entered too many arguments.\n");
      exit(0);
   } else if (argc < 3) {
      printf("You must supply the [filename] and [difficulty] in that order.\n");
      exit(0);
   }
    FILE *File;
    char filename[strlen(argv[1])];
    for (int i=0; i<strlen(argv[1]); i++) {
        filename[i] = argv[1][i];
    }
    filename[strlen(argv[1])] = '\0';
    int difficulty = atoi(argv[2]);
    int noOfLines = getNumberOfLinesInFile(filename);
    if (noOfLines == -1) {
        exit(0);
    }
    if (difficulty >= 10 || difficulty <= 0) {
        printf("Difficulty must be between 1 and 9!\n");
        exit(0);
    }
    char *questions[noOfLines];
    char *answers[noOfLines];
    loadQnA(filename, questions, answers , noOfLines);
    printf("[There are %d questions in this file]\n", noOfLines);
    int score = startQuizGame(questions, answers, noOfLines, difficulty);
    File = fopen ("quiz_history.txt","w");
    fprintf(File, "%s,  -  %d answered correctly  -  %d questions  -  %d difficulty", filename, score, noOfLines, difficulty);
}
