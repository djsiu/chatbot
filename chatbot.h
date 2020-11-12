// chatbot.h
//
// CMPT125 assignment 4 - chatbot
//
// this file can be run through the file chatbot_driver.cpp
//
// created by Denise Siu
// created in july 2020


#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Chatbot class
class Chatbot {

	private:

		string botName; 
		vector<string> userInput; // input obtained from the user
		vector<string> words; // contains the userInput, but with each word as a seperate element
		vector<string> newPhrase; // the phrase that will be used in the bot's response
		string userName; // store the user's name

		//scores for rock paper scissors
		int userScore = 0;
		int botScore = 0;

	public:

		// parameterized constructor, obtains the bot's name from main
		Chatbot(string name){

			botName = name;
		}

		// deconstructor
		~Chatbot() {
		}

		// the bot's name
		string get_name() const {

			return botName;
		}

		// obtain the user's input and turn it into a vector
		void tell(string input) {

			userInput.push_back(input); // stores input into userInput
		}

		// this function stores each word from a string as an element in an vector
		void separateWords(vector<string> &input, 
							vector<string> &words) {

			string temp;
			for(int i = 0; i < input[0].length(); i++) {

				if(input[0][i] != ' ') {
					temp += input[0][i];
				}

				else {
					words.push_back(temp);
					temp = "";
				}
			}

			words.push_back(temp);
		}

		// this function combines seperated words into a single string
		void combineWords(vector<string> &words, 
							vector<string> &newPhrase) {
			string temp;
			for (int i = 0; i < words.size(); i++) {
				temp += words[i] + " ";
			}

			newPhrase.push_back(temp);
		}


		// this function searches the user's input for keywords
		int findKeyword(vector<string> &input, 
						vector<string> &words, 
						vector<string> &newPhrase) const {

			string phrase = input[0];

			if (phrase.find("sorry") != string::npos) {

				return 1;
			}

			else if (phrase.find("i like") != string::npos) {

				words.erase(words.begin(), words.begin() + 2);

				return 2;
			}

			else if (phrase.find("my name is") != string::npos) {

				words.erase(words.begin(), words.begin() + 3);

				return 3;
			}

			else if (phrase.find("sad") != string::npos
					|| phrase.find("depressed") != string::npos
					|| phrase.find("angry") != string::npos) {

				newPhrase.clear();
				newPhrase.push_back("sad");

				return 4;
			}

			else if (phrase.find("hello") != string::npos 
					|| phrase.find("hi") != string::npos 
					|| phrase.find("bonjour") != string::npos) {

				return 5;
			} 

			else if (phrase.find("happy") != string::npos
					|| phrase.find("excited") != string::npos
					|| phrase.find("glad") != string::npos) {

				newPhrase.clear();
				newPhrase.push_back("happy");

				return 6;
			}

			else if (phrase.find("i am") != string::npos) {

				words.erase(words.begin(), words.begin() + 2);

				return 7;
			}

			else if (phrase.find("you are") != string::npos) {

				words.erase(words.begin(), words.begin() + 2);

				return 8;
			}

			else if (phrase.find("i saw") != string::npos) {

				words.erase(words.begin(), words.begin() + 2);

				return 9;
			}

			else if (phrase.find("rock") != string::npos
					|| phrase.find("paper") != string::npos
					|| phrase.find("scissors") != string::npos) {

				return 10;
			}

			else if (phrase.find("score") != string::npos) {

				return 11;
			}

			else if (phrase.find("flip") != string::npos
					&& phrase.find("coin") != string::npos) {

				return 12;

			}

			else if (phrase.find("?") != string::npos) {

				return 13;
			}

			return 0;

		} // find keywords

		//this funtion turns all the letters in a string lowercase
		void lowercase (vector<string> &input) {

			string temp;

			for (int i = 0; i < input[0].length(); i++) {
				temp += tolower(input[0][i]);
			}

			input[0] = temp;
		}

		//generates a random number from 100 - 102
		int getRandNum () {
			int res = (100 + rand() % 3);
			return res;
		}

		// the bot's response
		string get_reply() {

			string reply;
			string input = userInput[0];

			if (input == "") {
				reply = "Sorry, couldn't hear you there, what was that again?";
			}

			else {
				// processing the user's input
				lowercase(userInput);
				separateWords(userInput, words);
				int key = findKeyword(userInput, words, newPhrase);
				combineWords(words, newPhrase);

				// getting random number to choose the set of responses to use
				int set = getRandNum();

				//possible responses from the bot
				switch (set) {

					case 100:

						switch (key) {

							case 1: 
								reply = "No worries";
								break;

							case 2:
								reply = "That's so cool, I like " + newPhrase[0] + " too!";
								break;

							case 3:
								reply = "Nice to meet you " + newPhrase[0] + "!";
								userName = newPhrase[0]; // saving the user's name for future use
								break;

							case 4:
								if (userName.empty()) {
									reply = "Sorry to hear that, why are you feeling " 
											+ newPhrase[0] + "?";
								}
								else {
									reply = "I'm sorry to hear that " + userName + 
											"why are you feeling " + newPhrase[0] + "?";
								}
								break;

							case 5:
								if (userName.empty()) {
									reply = "Hi, how are you doing today?";
								}
								else {
									reply = "Hi, " + userName + "how are you today?";
								}
								break;

							case 6:
								reply = "Yay :) why are you feeling " + newPhrase[0] + "?";
								break;

							case 7:
								reply = "When did you become " + newPhrase[0] + "?";
								break;

							case 8:
								reply = "Why do you think I am " + newPhrase[0] + "?";
								break;

							case 9:
								reply = "How does seeing " + newPhrase[0] 
										+ "make you feel?";
								break;

							case 10: //rock
								if (userInput[0] == "rock") {
									reply = "ROCK! ... hmm its a tie.";
								}
								if (userInput[0] == "paper") {
									reply = "ROCK! ... you win :(";
									userScore++;
								}
								if (userInput[0] == "scissors") {
									reply = "ROCK! ... yay I win :)";
									botScore++;
								}
								break;

							case 11:
								if (botScore > userScore) {
									reply = "The score is: " + to_string(userScore) 
											+ " vs " + to_string(botScore) + "\n\t" 
											+ "I'm winning!";
								}
								if (userScore > botScore) {
									reply = "The score is: " + to_string(userScore) 
											+ " vs " + to_string(botScore) + "\n\t" 
											+ "You are winning!";
								}
								if (userScore == botScore) {
									reply = "The score is: " + to_string(userScore) 
											+ " vs " + to_string(botScore) + "\n\t" 
											+ "It's a tie!";
								}
								break;

							case 12: 
							{
								int res = (rand() % 2);
								if (res == 0) {
									reply = "Heads!";
								}
								else {
									reply = "tails!";
								}
								break;
							}

							case 13:
								reply = "Sorry I don't know.";
								break;
								
							default:
								reply = "Okay!";
						} //switch (key)
						break;

					case 101: 
						switch (key) {

							case 1: 
								reply = "That's ok I forgive you!";
								break;

							case 2:
								reply = "Why do you like " + newPhrase[0] + "?";
								break;

							case 3:
								reply = newPhrase[0] + ", that's a cool name.";
								userName = newPhrase[0]; // saving the user's name for future use
								break;

							case 4:
								if (userName.empty()) {
									reply = "That sucks, why are you feeling " 
											+ newPhrase[0] + "?";
								}
								else {
									reply = "That sucks " + userName + 
											", why are you feeling " + newPhrase[0] + "?";
								}
								break;

							case 5:
								if (userName.empty()) {
									reply = "Hi, what's up?";
								}
								else {
									reply = "Hi, " + userName + "what's up?";
								}
								break;

							case 6:
								reply = "That's good! Why are you " + newPhrase[0] + "?";
								break;

							case 7:
								reply = "How did you become " + newPhrase[0] + "?";
								break;

							case 8:
								reply = "no u.";
								break;

							case 9:
								reply = "Wow I've never seen " + newPhrase[0] 
										+ "what does it look like?";
								break;

							case 10: //paper
								if (userInput[0] == "rock") {
									reply = "PAPER! ... I WON HAHA!";
									botScore++;
								}
								if (userInput[0] == "paper") {
									reply = "PAPER! ... tie!";
								}
								if (userInput[0] == "scissors") {
									reply = "PAPER! ... congrats, you won!";
									userScore++;
								}
								break;

							case 11:
								if (botScore > userScore) {
									reply = "You have: " + to_string(userScore) 
											+ ", I have: " + to_string(botScore) + "\n\t" 
											+ "I'm winning!";
								}
								if (userScore > botScore) {
									reply = "You have: " + to_string(userScore) 
											+ ", I have: " + to_string(botScore) + "\n\t" 
											+ "You are winning!";
								}
								if (userScore == botScore) {
									reply = "You have: " + to_string(userScore) 
											+ ", I have: " + to_string(botScore) + "\n\t" 
											+ "It's a tie!";
								}
								break;

							case 12:
							{
								int res = (rand() % 2);
								if (res == 0) {
									reply = "It's heads.";
								}
								else {
									reply = "It's tails.";
								}
								break;
							}

							case 13:
								reply = "I'm not sure, maybe try Google?";
								break;
								
							default:
								reply = "Cool!";
						} //switch (key)
						break;

					case 102:
						switch (key) {

							case 1: 
								reply = "No need to apologize!";
								break;

							case 2:
								reply = "What about " + newPhrase[0] + " do you like?";
								break;

							case 3:
								reply = "Hi " + newPhrase[0] + ", my name is " + botName;
								userName = newPhrase[0]; // saving the user's name for future use
								break;

							case 4:
								if (userName.empty()) {
									reply = "Aww :( why are you" 
											+ newPhrase[0] + "?";
								}
								else {
									reply = "Aww " + userName + 
											" :( why are you " + newPhrase[0] + "?";
								}
								break;

							case 5:
								if (userName.empty()) {
									reply = "Hello my friend!";
								}
								else {
									reply = "Greetings " + userName + "!";
								}
								break;

							case 6:
								reply = "If you're " + newPhrase[0] + " I'm " + newPhrase[0];
								break;

							case 7:
								reply = "How long have you been " + newPhrase[0] + "?";
								break;

							case 8:
								reply = "Maybe I am " + newPhrase[0] 
										+ ", maybe I'm not.";
								break;

							case 9:
								reply = "Cool! Where did you see " + newPhrase[0] + "?";
								break;

							case 10: //scissors
								if (userInput[0] == "rock") {
									reply = "SCISSORS! ... woah, you won!";
									userScore++;
								}
								if (userInput[0] == "paper") {
									reply = "SCISSORS! ... haha I got you!";
									botScore++;
								}
								if (userInput[0] == "scissors") {
									reply = "SCISSORS! ... it's a tie.";
								}
								break;

							case 11:
								if (userName.empty()) {
									if (botScore > userScore) {
										reply = "You have: " + to_string(userScore) 
												+ ", I have: " + to_string(botScore) + "\n\t" 
												+ "I'm winning!";
									}
									if (userScore > botScore) {
										reply = "You have: " + to_string(userScore) 
												+ ", I have: " + to_string(botScore) + "\n\t" 
												+ "You are winning!";
									}
									if (userScore == botScore) {
										reply = "You have: " + to_string(userScore) 
												+ ", I have: " + to_string(botScore) + "\n\t" 
												+ "It's a tie!";
									}
								}
								else {
									if (botScore > userScore) {
										reply = userName+ ": " + to_string(userScore) 
												+ ", " + botName + ": " + to_string(botScore) + "\n\t" 
												+ "I'm winning!";
									}
									if (userScore > botScore) {
										reply = userName+ ": " + to_string(userScore) 
												+ ", " + botName + ": " + to_string(botScore) + "\n\t" 
												+ "You are winning!";
									}
									if (userScore == botScore) {
										reply = userName+ ": " + to_string(userScore) 
												+ ", " + botName + ": " + to_string(botScore) + "\n\t" 
												+ "It's a tie!";
									}
								}
								break;

							case 12: 
							{
								int res = (rand() % 2);
								if (res == 0) {
									reply = "HEEEADDDDSSS!!!";
								}
								else {
									reply = "TAAIILLLLLLSS!!!";
								}
								break;
							}
							case 13:
								reply = "*shrug*";
								break;
								
							default:
								reply = "That's interesting.";
						} //switch (key)
						break;

					default:
						reply = "beep boop, did not compute!";

				} //switch (set)

			}//else
		

			userInput.clear(); //clear so the next input will be at index 0 
			words.clear();
			newPhrase.clear();

			return reply;
		} //get reply
};//class
