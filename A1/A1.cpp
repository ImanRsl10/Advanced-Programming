#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

const string START_DAY = "start_day";
const string SHOW_DAY = "show_day";
const string SHOW_THE_LONGEST_DAY = "show_the_longest_day";
const string SHOW_THE_BEST_DAY = "show_the_best_day";
const int SUMMERY_MAX_LEN = 20, BEGIN = 0;

struct Mem 
{
    string date;
    vector <string> Notes;
    vector <string> fragNote;
    int NotesLen;
    int SentimentFactor;
};

void lineDecode(string cmdOrNote, string& cmd, string& date)
{
    stringstream piecedCON(cmdOrNote);
    piecedCON >> cmd >> date;
}

void getNote(vector <string>& Notes)
{
    string newNote;
    getline(cin, newNote);
    Notes.push_back(newNote);
}

void noteShow(Mem Memories)
{
    for(int j = 0; j < Memories.Notes.size(); j++)
    {
        cout << Memories.Notes[j] << endl;
    }
}

void showDay(vector <Mem> Memories, string date)
{
    for(int i = 0; i < Memories.size(); i++)
    {
        if(date == Memories[i].date)
        {
            noteShow(Memories[i]);
            break;
        }
    }
}

int notesLenCalcMax(vector <Mem>& Memories)
{
    vector <int> notesLen;
    for(int i = 0; i < Memories.size(); i++)
    {
        for(int j = 0; j < Memories[i].Notes.size(); j++)
        {
            Memories[i].NotesLen += Memories[i].Notes[j].size();
        }
        notesLen.push_back(Memories[i].NotesLen);
    }
    return *max_element(notesLen.begin(), notesLen.end());
}

void summaryShow(Mem Memories)
{
    cout << Memories.date << endl;
    if (Memories.Notes[BEGIN].size() > SUMMERY_MAX_LEN)
    {
        cout << Memories.Notes[BEGIN].substr(BEGIN, SUMMERY_MAX_LEN) << "..." << endl;
    }
    else
    {
        cout << Memories.Notes[BEGIN] << endl;
    }
}

void longestDay(vector <Mem> Memories)
{
    int maxNoteLen = notesLenCalcMax(Memories);
    for(int i = 0; i < Memories.size(); i++)
    {
        if(maxNoteLen == Memories[i].NotesLen)
        {
            summaryShow(Memories[i]);
            break;
        }
    }
}

int sentimentsCalcMax(vector <Mem>& Memories, vector <string> positiveWords)
{
    vector <int> sentiFact;
    for(int k = 0; k < Memories.size(); k++)
	{
		for(int j = 0; j < Memories[k].fragNote.size(); j++)
		{
			for(int i = 0; i < positiveWords.size(); i++)
			{
                if(positiveWords[i] == Memories[k].fragNote[j])
                {
                    ++ Memories[k].SentimentFactor;
                }
			}
	    }
        sentiFact.push_back(Memories[k].SentimentFactor);
    }
    return *max_element(sentiFact.begin(), sentiFact.end());
}

void lineToWord(vector <Mem>& Memories)
{
    string notePiece;
    for (int i = 0; i < Memories.size(); i++)
    {
        for(int j = 0; j < Memories[i].Notes.size(); j++)
        {
            stringstream lineNote(Memories[i].Notes[j]);
            while (lineNote >> notePiece)
            {
                Memories[i].fragNote.push_back(notePiece);
            }
        }
    }
}

void bestNote(vector <Mem> Memories, vector <string> positiveWords)
{
    int mostSentiFact = sentimentsCalcMax(Memories, positiveWords);
    for(int i = 0; i < Memories.size(); i++)
    {
        if(mostSentiFact == Memories[i].SentimentFactor)
        {
            summaryShow(Memories[i]);
            break;
        }
    }
}

void bestDay(vector <Mem>& Memories, vector <string> positiveWords)
{
    lineToWord(Memories);
    bestNote(Memories, positiveWords);
}

void cmdProcess(vector <Mem>& Memories, vector <string> positiveWords)
{   //How can be optimized? --> if else --> cmdFlag?
    string cmdOrNote, command, date;
    int MemPage = -1;
    while(getline(cin, cmdOrNote))
    {
        lineDecode(cmdOrNote, command, date);
        if (command == START_DAY)
        {
            MemPage += 1; 
            Memories.push_back({"", });
            Memories[MemPage].date = date;
            getNote(Memories[MemPage].Notes); 
        } 
        else if (command == SHOW_DAY)
        {
            showDay(Memories, date);
        }
        else if (command == SHOW_THE_LONGEST_DAY)
        {
            longestDay(Memories);
        }
        else if (command == SHOW_THE_BEST_DAY)
        {
            bestDay(Memories, positiveWords);
        }
        else
        {
            Memories[MemPage].Notes.push_back(cmdOrNote);
        }
    }
}

void readFile(vector <string>& words)
{
    fstream wordsF;
    string word;
    wordsF.open("positive-words.txt");
    while(wordsF)
    {
        wordsF >> word;
        words.push_back(word);
    }
}

int main()
{
    vector <Mem> Memories;
    vector <string> posWords;
    readFile(posWords);
    cmdProcess(Memories, posWords);
    return 0;
}