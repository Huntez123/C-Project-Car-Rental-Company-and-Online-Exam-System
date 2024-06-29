#include <iostream>
#include <string>
#include <memory>     
#include <stdexcept>  
#include <cstdlib>    
#include <ctime>      

using namespace std;

class InvalidExamDurationException : public exception 
{
public:
    const char* what() const noexcept override 
    {
        return "Invalid exam duration. Duration must be a positive number.";
    }
};

class GradingErrorException : public exception 
{
public:
    const char* what() const noexcept override 
    {
        return "Error occurred during grading.";
    }
};

class Exam 
{
protected:
    string examID;
    string subject;
    int duration; 

public:
        Exam(const string& examID, const string& subject, int duration)
        : examID(examID), subject(subject), duration(duration) 
    {
        if (duration <= 0)
        {
            throw InvalidExamDurationException();
        }
    }

        virtual void gradeExam() const = 0;

    string getExamID() const 
    { 
        return examID; 
    }
    string getSubject() const 
    { 
        return subject; 
    }
    int getDuration() const 
    { 
        return duration; 
    }

    virtual ~Exam() {}
};

class MultipleChoiceExam : public Exam 
{
private:
    int numQuestions;
    int numCorrectAnswers;

public:
        MultipleChoiceExam(const string& examID, const string& subject, int duration, int numQuestions)
        : Exam(examID, subject, duration), numQuestions(numQuestions), numCorrectAnswers(0) {}

        void gradeExam() const override 
    {
                cout << "Grading Multiple Choice Exam..." << endl;

        if (numQuestions <= 0) 
        {
            throw GradingErrorException();
        }

        cout << "Number of Correct Answers: " << numCorrectAnswers << endl;
        
        double score = (double)numCorrectAnswers / numQuestions * 100; 
        cout << "Score: " << score << "/100" << endl;
    }

    void setNumCorrectAnswers(int correct) 
    {
        if (correct < 0 || correct > numQuestions) 
        {
            throw GradingErrorException();
        }
        numCorrectAnswers = correct;
    }

    ~MultipleChoiceExam() {}
};

class EssayExam : public Exam 
{
private:
    string topic;
    int numQuestions;
    int score;

public:
    EssayExam(const string& examID, const string& subject, int duration, const string& topic, int numQuestions)
    : Exam(examID, subject, duration), topic(topic), numQuestions(numQuestions), score(0) {}

    void gradeExam() const override 
    {
        cout << "Grading Essay Exam..." << endl;

        if (numQuestions <= 0) 
        {
            throw GradingErrorException();
        }

        cout << "Topic: " << topic << endl;
        cout << "Number of Essay Questions: " << numQuestions << endl;
        
        cout << "Score: " << score << "/" << numQuestions << endl;
    }
    
    void setScore(int newScore) 
    {
        if (newScore < 0 || newScore > numQuestions) 
            {
                throw GradingErrorException();
            }
        score = newScore;
    }

    ~EssayExam() {}
};

unique_ptr<Exam> createExam(const string& category) 
{
    string examID, subject;
    int duration;

    cout << "Enter Exam ID: ";
    getline(cin, examID);

    cout << "Enter Subject: ";
    getline(cin, subject);

    cout << "Enter Duration (in minutes): ";
    cin >> duration;
    cin.ignore(); 
    if (duration <= 0) 
    {
        throw InvalidExamDurationException();
    }

    if (category == "MCQ") 
    {
        int numQuestions, numCorrectAnswers;
        
        cout << "Enter Number of Questions: ";
        cin >> numQuestions;

        cout << "Enter Number of Correct Answers: ";
        cin >> numCorrectAnswers;
        
        cin.ignore(); 

        if (numQuestions <= 0 || numCorrectAnswers < 0 || numCorrectAnswers > numQuestions) 
        {
            throw GradingErrorException();
        }

        auto mcqExam = make_unique<MultipleChoiceExam>(examID, subject, duration, numQuestions);
        mcqExam->setNumCorrectAnswers(numCorrectAnswers);
        return mcqExam;
    } else if (category == "Essay") 
    {
        int numQuestions, score;
        string topic;

        cout << "Enter Essay Topic: ";
        getline(cin >> ws, topic); 

        cout << "Enter Number of Essay Questions: ";
        cin >> numQuestions;

        cout << "Enter Score Assigned (out of " << numQuestions << "): ";
        cin >> score;
        
        cin.ignore(); 

        if (numQuestions <= 0 || score < 0 || score > numQuestions)  
        {
            throw GradingErrorException();
        }                      
            
        auto essayExam = make_unique<EssayExam>(examID, subject, duration, topic, numQuestions);
        essayExam->setScore(score);
        return essayExam;
    } else 
    {
        throw invalid_argument("Invalid exam category. Please choose MCQ or Essay.");
    }
}

void takeExam(const Exam& exam) 
{
    cout << "Taking exam with ID: " << exam.getExamID() << endl;
    cout << "Subject: " << exam.getSubject() << endl;
    cout << "Duration: " << exam.getDuration() << " minutes" << endl;

    exam.gradeExam();

    cout << "Exam grading completed." << endl;
}

int main() 
{
    srand(time(0));

    string category;

    try 
    {
        cout << "Enter Exam Category (MCQ or Essay): ";
        getline(cin, category);

        auto exam = createExam(category);

        takeExam(*exam);
    } catch (const InvalidExamDurationException& ex) 
    {
        cerr << "Error: " << ex.what() << endl;
        return 1; 
    } 
    catch (const GradingErrorException& ex) 
    {
        cerr << "Error: " << ex.what() << endl;
        return 1; 
    } 
    catch (const exception& ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1; 
    }

    return 0;
}
