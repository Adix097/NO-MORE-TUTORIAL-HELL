Random random = new();

/// <summary>
/// prompt's the user for guess until a valid guess is entered
/// </summary>
/// <param name="lowerBound">lower bound of the range</param>
/// <param name="upperBound">upper bound of the range</param>
/// <returns>the guess of the user as integer</returns>
int TakeGuess(int lowerBound, int upperBound) {
    int guess;
    Console.Write($"Guess any number between {lowerBound} and {upperBound}: ");
    while (!int.TryParse(Console.ReadLine(), out guess)) {
        Console.WriteLine("You did not enter a number!");
    }

    return guess;
}

/// <summary>
/// helper function to read user commands
/// </summary>
/// <returns>lowercased version of the command entered</returns>
char ReadCmd() {
    char cmd;
    while (!char.TryParse(Console.ReadLine(), out cmd)) {
        Console.WriteLine("Enter a valid letter.");
    }

    return char.ToLower(cmd);
}

/// <summary>
/// helper function to read the desired level of difficulty of user
/// </summary>
/// <returns>valid character for desired difficult, e -> easy, m -> medium, h -> hard</returns>
char ReadDifficulty() {
    Console.WriteLine("Select a difficulty: 'e' for easy, 'm' for medium and 'h' for hard");
    char difficultyInput = ReadCmd();

    while (difficultyInput != 'e' && difficultyInput != 'm' && difficultyInput != 'h') {
        System.Console.WriteLine("Not a valid difficulty");
        difficultyInput = ReadCmd();
    }

    return difficultyInput;
}

/// <summary>
/// game menu to display welcome msg and provide initial instructions
/// </summary>
/// <returns>returns the upper bound for guess according to the difficulty selected by user</returns>
int Menu() {
    Console.WriteLine("--- Welcome to Number Guessing Game ---");
    Console.WriteLine("Press 'p' to play or 'e' to exit!");

    if (ReadCmd() == 'p') {
        char difficulty = ReadDifficulty();

        if (difficulty == 'e') return 10;
        else if (difficulty == 'm') return 100;
        else if (difficulty == 'h') return 1000;
    }

    return 0;
}

/// <summary>
/// basic game logic, ask for guess if correct declare win else provide hints accordingly
/// </summary>
void Game() {
    int difficultyLevel = Menu();

    if (difficultyLevel == 0) Environment.Exit(0);

    int lowerBound = 1;
    int upperBound = difficultyLevel;

    int answer = random.Next(lowerBound, upperBound + 1);
    int userInput;
    int count = 0;

    do {
        userInput = TakeGuess(lowerBound, upperBound);
        count++;

        if (userInput == answer) Console.WriteLine($"Correct! You took {count} attempts!");
        else if (userInput < answer) Console.WriteLine("Guess higher!");
        else Console.WriteLine("Guess lower!");

    } while (userInput != answer);
}

/// <summary>
/// game loop for replay mechanic
/// </summary>
while (true) {
    Game();
    Console.WriteLine("Press 'r' to restart or anything else to exit");
    if (ReadCmd() != 'r') break;
}

