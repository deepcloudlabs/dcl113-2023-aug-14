#pragma once

#include <string>

using namespace std;

class person {

public:
    enum gender_t {
        female, male
    };
    enum output_format {
        name_only, full_details
    };

    person() : m_name("jack"), m_surname("bauer"), m_gender(male), m_age(56) {}

    person(const string &mName, const string &mSurname, gender_t mGender, int mAge,double mSalary) : m_name(mName),
                                                                                      m_surname(mSurname),
                                                                                      m_gender(mGender),
                                                                                      m_age(mAge),
                                                                                      m_salary(mSalary) {}

    const string name() const {
        return m_name;
    }

    const string surname() const {
        return m_surname;
    }

    gender_t gender() const {
        return m_gender;
    }

    int age() const {
        return m_age;
    }

    double salary() const {
        return m_salary;
    }

private:
    string m_name;
    string m_surname;
    gender_t m_gender;
    double m_salary;
    int m_age;
};