/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 *
 * Overview:
 *   The Account class aims to encapsulate a university student's account.
 * Its primary responsibility is to hold data such as the student's name,
 * account number, email, the courses they've enrolled in or completed, and
 * their graduation status. The class also furnishes functions that allow
 * course enrollment and completion, offer information about the enrolled
 * and completed courses, present the student's full name and email, verify
 * the graduation status, and update the graduation status of the student.
 * An important note is that the student's email address is constructed
 * within this class using their name and university suffix.
 *   Notably, the class performs a check to confirm whether the student
 * has graduated before they can enroll in a new course. The information
 * regarding enrolled and completed courses is kept in a vector, with
 * provided methods for accessing it. The Course class is employed as an
 * argument in the course enrollment and completion functions.
 *
 * Name: Aynur Rahman Talukdar
 * Student number: 150189473
 * UserID: qkayta
 * E-Mail: aynurrahman.talukdar@tuni.fi
 *
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>
#include <memory>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief sign_course
     * @return successful signing or not
     */
    bool sign_course(Course* course);

    /**
     * @brief complete_course
     * @return successful completion or not
     */
    bool complete_course(Course* course);

    /**
     * @brief get_completed_courses
     * @return vector with all completed courses
     */
    std::vector<std::shared_ptr<Course>> get_completed_courses() const;

    /**
     * @brief get_signed_courses
     * @return vector with all signed courses
     */
    std::vector<std::shared_ptr<Course>> get_signed_courses() const;

    /**
     * @brief Graduates the account by changing courses from signed to completed
     */
    void graduate();

    /**
     * @brief get_graduation_status
     * @return true if already graduated
     */
    bool get_graduation_status() const;


private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    std::vector<Course*> signed_courses_;
    std::vector<Course*> completed_courses_;
    bool graduated_;

};

#endif // ACCOUNT_HH
